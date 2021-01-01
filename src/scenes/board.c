#include "board.h"
#include "../../config.h"
#include <stdlib.h>
#ifdef PONG_DEBUG
#include <stdio.h>
#endif

// declaration static functions.
static void drawDivider(void);
static bool checkCollisionLimit(const Ball *const ball, const Rectangle limit);
static void checkCollisions(Board *const board);
static void drawPoints(const int32_t ptoPlayer, const int32_t ptoEnemy);

// implementation public functions.
Board *initBoard(void) {
  Board *board = malloc(sizeof(Board));
  if (board == NULL) {
    return NULL;
  }

  board->ptoEnemy = 0;
  board->ptoPlayer = 0;
  board->limitRecLeft = (Rectangle) {
    0,
    0,
    15,
    GetScreenHeight()
  };
  board->limitRecRight = (Rectangle) {
    GetScreenWidth() - 15,
    0,
    15,
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
  updatePalette(board->player);
  updatePalette(board->enemy);
  updateBall(board->ball, board->player, board->enemy);
  checkCollisions(board);
}

void drawBoard(const Board *const board) {
  drawPalette(board->player);
  drawPalette(board->enemy);
  drawDivider();
  drawBall(board->ball);

  DrawRectangleRec(board->limitRecLeft, PONG_COLOR_2);
  DrawRectangleRec(board->limitRecRight, PONG_COLOR_2);
  drawPoints(board->ptoPlayer, board->ptoEnemy);
}

void freeBoard(Board **board) {
  if (*board != NULL) {
    freePalette(&(*board)->player);
    freePalette(&(*board)->enemy);
    freeBall(&(*board)->ball);
    free(*board);
    *board = NULL;
    #ifdef PONG_DEBUG
    printf("deleted Board.\n");
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
    PONG_COLOR_2
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
  }

  if (checkCollisionLimit(board->ball, board->limitRecRight)) {
    board->ptoPlayer += 1;
    resetBall(board->ball);
  }
}

static void drawPoints(const int32_t ptoPlayer, const int32_t ptoEnemy) {
  const int32_t middleWidth = GetScreenWidth() / 2; 
  const int32_t posY = 10;
  const int32_t fontSize = 32;
  const char *strPtoPlayer= TextFormat("pl1: %d", ptoPlayer);
  const char *strPtoEnemy = TextFormat("pl2: %d", ptoEnemy);
  const int32_t lenStrPlayer = (TextLength(strPtoPlayer) * (fontSize / 2)) / 2;
  const int32_t lenStrEnemy = (middleWidth / 2) - (TextLength(strPtoEnemy) * (fontSize / 2) / 2);
  DrawText(
    strPtoPlayer,
    (middleWidth / 2) - lenStrPlayer,
    posY,
    fontSize,
    PONG_COLOR_2
  );

  DrawText(
    strPtoEnemy,
    middleWidth + lenStrEnemy,
    posY,
    fontSize,
    PONG_COLOR_2
  );
}
