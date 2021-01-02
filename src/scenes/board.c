#include "board.h"
#include "../../config.h"
#include "../global.h"
#include <stdlib.h>

extern Global globalData;

// declaration static functions.
static void drawDivider(void);
static bool checkCollisionLimit(const Ball *const ball, const Rectangle limit);
static void checkCollisions(Board *const board);
static void drawPoints(const int32_t ptoPlayer, const int32_t ptoEnemy);
static void drawCounter(void);
static void drawLimits(const Board *const board);
static void drawWinner(const Board *const board);

static bool showCounter = false;
static const int32_t MAX_COUNTER = 4;
static int32_t counter = MAX_COUNTER;
static int32_t prevCounter = 0;
static bool someoneWon = false;

// implementation public functions.
Board *initBoard(void) {
  Board *board = malloc(sizeof(Board));
  if (board == NULL) {
    return NULL;
  }

  board->ptoEnemy = 0;
  board->ptoPlayer = 0;
  const int32_t sizeLimit = 15;
  board->limitRecLeft = (Rectangle) {
    0,
    0,
    sizeLimit,
    GetScreenHeight()
  };
  board->limitRecRight = (Rectangle) {
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
      updatePalette(board->player);
      updatePalette(board->enemy);
      updateBall(board->ball, board->player, board->enemy);
      checkCollisions(board);
    } else {
      drawCounter();
    }
  }
}

void drawBoard(const Board *const board) {
  drawPalette(board->player);
  drawPalette(board->enemy);
  drawDivider();
  drawBall(board->ball);
  drawLimits(board);
  drawPoints(board->ptoPlayer, board->ptoEnemy);

  if (showCounter) {
    const int32_t fontSize = 128;
    const int32_t posX = GetScreenWidth() / 2 - (fontSize / 3);
    const int32_t posY = GetScreenHeight() / 2 - (fontSize / 2);
    DrawText(TextFormat("%d", counter), posX, posY, fontSize, globalData.colors.color1);
  }

  if (someoneWon) {
    drawWinner(board);
  }
}

void freeBoard(Board **board) {
  if (*board != NULL) {
    freePalette(&(*board)->player);
    freePalette(&(*board)->enemy);
    freeBall(&(*board)->ball);
    free(*board);
    *board = NULL;
    #ifdef PONG_DEBUG
    TraceLog(LOG_INFO, "xxx Board DELETED.");
    #endif
  }
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
  if (checkCollisionLimit(board->ball, board->limitRecLeft)) {
    board->ptoEnemy += 1;
    resetBall(board->ball);
    showCounter = true;
  }

  if (checkCollisionLimit(board->ball, board->limitRecRight)) {
    board->ptoPlayer += 1;
    resetBall(board->ball);
    showCounter = true;
  }

  if (board->ptoPlayer >= globalData.maxPtos || board->ptoEnemy >= globalData.maxPtos) {
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
    globalData.colors.color3
  );

  DrawText(
    strPtoEnemy,
    middleWidth + lenStrEnemy,
    posY,
    fontSize,
    globalData.colors.color3
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
      board->limitRecLeft.x,
      board->limitRecLeft.y,
      board->limitRecLeft.width,
      board->limitRecLeft.height,
      PONG_COLOR_SHAPE
    );
    DrawRectangleLines(
      board->limitRecRight.x,
      board->limitRecRight.y,
      board->limitRecRight.width,
      board->limitRecRight.height,
      PONG_COLOR_SHAPE
    );
  } else {
    // DrawRectangleRec(board->limitRecLeft, globalData.colors.color2);
    // DrawRectangleRec(board->limitRecRight, globalData.colors.color2);
  }
}

static void drawWinner(const Board *const board) {
  Rectangle rec = (Rectangle){ 0 };
  int32_t middleScreen = GetScreenWidth() / 4;

  if (board->ptoPlayer >= globalData.maxPtos) {
    rec.x = 0;
    rec.y = 0;
    rec.width = GetScreenWidth() / 2;
    rec.height = GetScreenHeight();

  } else if (board->ptoEnemy >= globalData.maxPtos) {
    rec.x = GetScreenWidth() / 2;
    rec.y = 0;
    rec.width = GetScreenWidth() / 2;
    rec.height = GetScreenHeight();
    middleScreen = GetScreenWidth() / 2 + middleScreen;
  }

  DrawRectangleRec(rec, globalData.colors.color1);

  const char *msg = "Winner!!";
  const int32_t fontSize = 32;
  const int32_t posX = middleScreen - (TextLength(msg) * (fontSize / 2)) / 2;
  const int32_t posY = GetScreenHeight() / 2;
  DrawText(msg, posX, posY, fontSize, globalData.colors.color3);
}
