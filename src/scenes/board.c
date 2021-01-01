#include "board.h"
#include "../../config.h"
#include <stdlib.h>
#ifdef PONG_DEBUG
#include <stdio.h>
#endif

Board *initBoard(void) {
  Board *board = malloc(sizeof(Board));
  if (board == NULL) {
    return NULL;
  }

  const Vector2 playerPos = (Vector2){ 15, GetScreenHeight() / 2 };
  board->player = initPalette(playerPos, false);

  const Vector2 playerEnemy = (Vector2){ GetScreenWidth() - 30, GetScreenHeight() / 2 };
  board->enemy = initPalette(playerEnemy, true);

  return board;
}

void updateBoard(Board *const board) {
  updatePalette(board->player);
  updatePalette(board->enemy);
}

void drawBoard(const Board *const board) {
  drawPalette(board->player);
  drawPalette(board->enemy);
}

void freeBoard(Board **board) {
  if (*board != NULL) {
    freePalette(&(*board)->player);
    freePalette(&(*board)->enemy);
    free(*board);
    *board = NULL;
    #ifdef PONG_DEBUG
    printf("deleted Board.\n");
    #endif
  }
}