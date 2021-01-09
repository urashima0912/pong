#include "board.h"
#include "../../config.h"
#include "../global.h"
#include <stdlib.h>

extern Global globalData;

// declaration static functions.
static bool finished = false;

static void drawDivider(void);
static bool checkCollisionLimit(const Ball *const ball, const Rectangle limit);
static void checkCollisions(Board *const board);
static void drawPoints(const int32_t ptoPlayer, const int32_t ptoEnemy);
static void drawCounter(void);
static void drawLimits(const Board *const board);
static void drawWinner(const Board *const board);
static void resetValues(void);
static void drawCounterScreen(void);
static GameObject getGameObjectFromBall(const Board *const board);
static void initLimit(void);

static bool showCounter = false;
static const int32_t MAX_COUNTER = 4;
static int32_t counter = MAX_COUNTER;
static int32_t prevCounter = 0;
static bool someoneWon = false;

static Rectangle limitLeft = (Rectangle){ 0 };
static Rectangle limitRight = (Rectangle){ 0 };
static const int32_t widthLimit = 25;

// implementation public functions.
Board *initBoard(void) {
  resetValues();
  Board *board = malloc(sizeof(Board));
  if (board == NULL) {
    return NULL;
  }

  initLimit();
  board->ptoEnemy = 0;
  board->ptoPlayer = 0;
  const int32_t sizeLimit = 15;
  board->recLeft = (Rectangle) {
    0,
    0,
    sizeLimit,
    GetScreenHeight()
  };
  board->recRight = (Rectangle) {
    GetScreenWidth() - sizeLimit,
    0,
    sizeLimit,
    GetScreenHeight()
  };

  const int32_t screenHeight = GetScreenHeight();
  const int32_t screenWidth = GetScreenWidth();

  const Vector2 playerPos = (Vector2){ 15, (screenHeight / 2) - 50 };
  board->player = initPalette(playerPos, false);

  const Vector2 playerEnemy = (Vector2){ screenWidth - 30, (screenHeight / 2) - 50 };
  board->enemy = initPalette(playerEnemy, true);

  board->ball = initBall();

  return board;
}

void updateBoard(Board *const board) {
  if (!someoneWon) {
    if (!showCounter) {
      const GameObject gameObject = getGameObjectFromBall(board);
      updatePalette(board->player, gameObject);
      updatePalette(board->enemy, gameObject);
      updateBall(board->ball, board->player, board->enemy);
      checkCollisions(board);
    } else {
      drawCounter();
    }
  }

  if (IsKeyPressed(KEY_ESCAPE)) {
    finished = true;
  }
}

void drawBoard(const Board *const board) {
  drawPalette(board->player);
  drawPalette(board->enemy);
  drawDivider();
  drawLimits(board);
  drawPoints(board->ptoPlayer, board->ptoEnemy);

  if (showCounter)
    drawCounterScreen();
  else if (someoneWon)
    drawWinner(board);
  else
    drawBall(board->ball);
}

void freeBoard(Board **board) {
  if (*board != NULL) {
    freePalette(&(*board)->player);
    freePalette(&(*board)->enemy);
    freeBall(&(*board)->ball);
    free(*board);
    *board = NULL;
    #ifdef PONG_DEBUG
    TraceLog(LOG_INFO, PONG_BOARD_DELETED);
    #endif
  }
}

bool finishBoard(void) {
  return finished;
}

// implementation static functions.
static void drawDivider(void) {
  const int32_t size = 5;
  const int32_t posX = (GetScreenWidth() / 2) - size;
  const int32_t posY = 0;
  DrawRectangle(
    posX,
    posY,
    size,
    GetScreenHeight(),
    globalData.colors.color2
  );
}

static bool checkCollisionLimit(const Ball *const ball, const Rectangle limit) {
  Rectangle recBall = (Rectangle) {
    ball->position.x,
    ball->position.y,
    ball->size.x,
    ball->size.y
  };
  return CheckCollisionRecs(recBall, limit);
}

static void checkCollisions(Board *const board) {
  if (checkCollisionLimit(board->ball, limitLeft)) {
    board->ptoEnemy += 1;
    resetBall(board->ball);
    showCounter = true;
  }

  if (checkCollisionLimit(board->ball, limitLeft)) {
    board->ptoPlayer += 1;
    resetBall(board->ball);
    showCounter = true;
  }

  if (board->ptoPlayer >= globalData.ptos || board->ptoEnemy >= globalData.ptos) {
    someoneWon = true;
    showCounter = false;
  }
}

static void drawPoints(const int32_t ptoPlayer, const int32_t ptoEnemy) {
  const int32_t middleWidth = GetScreenWidth() / 2; 
  const int32_t posY = 10;
  const int32_t fontSize = 32;
  const char *strPtoPlayer= TextFormat("%d", ptoPlayer);
  const char *strPtoEnemy = TextFormat("%d", ptoEnemy);
  const int32_t lenStrPlayer = (TextLength(strPtoPlayer) * (fontSize / 2)) / 2;
  const int32_t lenStrEnemy = (middleWidth / 2) - (TextLength(strPtoEnemy) * (fontSize / 2) / 2);
  DrawText(
    strPtoPlayer,
    (middleWidth / 2) - lenStrPlayer,
    posY,
    fontSize,
    globalData.colors.color2
  );

  DrawText(
    strPtoEnemy,
    middleWidth + lenStrEnemy,
    posY,
    fontSize,
    globalData.colors.color2
  );
}

static void drawCounter (void) {
  if (counter > 0) {
    const int32_t time = (int32_t) GetTime();
    if (time != prevCounter) {
      prevCounter = time;
      counter--;
    }
  } else {
    showCounter = false;
    counter = MAX_COUNTER;
    prevCounter = 0;
  }
}

static void drawLimits(const Board *const board) {
  if (globalData.showCollisionShape) {
    DrawRectangleLines(
      limitLeft.x,
      limitLeft.y,
      limitLeft.width,
      limitLeft.height,
      RED
    );
    DrawRectangleLines(
      limitRight.x,
      limitRight.y,
      limitRight.width,
      limitRight.height,
      RED
    );
  } else {
    DrawRectangleRec(board->recLeft, globalData.colors.color2);
    DrawRectangleRec(board->recRight, globalData.colors.color2);
  }
}

static void drawWinner(const Board *const board) {
  Rectangle rec = (Rectangle){ 0 };
  int32_t middleScreen = GetScreenWidth() / 4;

  if (board->ptoPlayer >= globalData.ptos) {
    rec.x = 0;
    rec.y = 0;
    rec.width = GetScreenWidth() / 2;
    rec.height = GetScreenHeight();

  } else if (board->ptoEnemy >= globalData.ptos) {
    rec.x = GetScreenWidth() / 2;
    rec.y = 0;
    rec.width = GetScreenWidth() / 2;
    rec.height = GetScreenHeight();
    middleScreen = GetScreenWidth() / 2 + middleScreen;
  }

  DrawRectangleRec(rec, Fade(globalData.colors.color1, 0.95));

  const char *msg = PONG_MSG_WINNER;
  const int32_t fontSize = 32;
  const int32_t posX = middleScreen - MeasureText(msg, fontSize) / 2;
  const int32_t posY = GetScreenHeight() / 2 - fontSize / 2;
  DrawText(msg, posX, posY, fontSize, globalData.colors.color3);
}

static void resetValues(void) {
  finished = false;
  showCounter = false;
  counter = MAX_COUNTER;
  prevCounter = 0;
  someoneWon = false;
}

static void drawCounterScreen(void) {
  DrawRectangle(
    0,
    0,
    GetScreenWidth(),
    GetScreenHeight(),
    Fade(globalData.colors.color0, 0.6)
  );
  const int32_t fontSize = 128;
  const char *value = TextFormat("%d", counter);
  const int32_t posX = GetScreenWidth() / 2 - MeasureText(value, fontSize) / 2;
  const int32_t posY = GetScreenHeight() / 2 - (fontSize / 2);
  DrawText(value, posX, posY, fontSize, globalData.colors.color3);
}

static GameObject getGameObjectFromBall(const Board *const board) {
  return (GameObject){
    board->ball->position,
    board->ball->size,
    board->ball->velocity
  };
}

static void initLimit(void) {
  limitLeft = (Rectangle){
    0,
    0,
    widthLimit,
    GetScreenHeight()
  };

  limitRight = (Rectangle) {
    GetScreenWidth() - widthLimit,
    0,
    widthLimit,
    GetScreenHeight()
  };
}
