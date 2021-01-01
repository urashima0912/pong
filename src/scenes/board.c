#include "board.h"
#include "../../config.h"
#include <stdlib.h>
#include <stdint.h>
#ifdef PONG_DEBUG
#include <stdio.h>
#endif

// declaration static functions.
static void drawDivider(void);


// implementation public functions.
Board *initBoard(void) {
  Board *board = malloc(sizeof(Board));
  if (board == NULL) {
    return NULL;
  }

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
}

void drawBoard(const Board *const board) {
  drawPalette(board->player);
  drawPalette(board->enemy);
  drawDivider();
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
    printf("deleted Board.\n");
    #endif
  }
}


// implementation static functions.
static void drawDivider(void) {
  const int32_t size = 5;
  DrawRectangle(
    (GetScreenWidth() / 2) - size,
    0,
    size,
    GetScreenHeight(),
    PONG_COLOR_2
  );
}
