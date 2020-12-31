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
  return board;
}

void updateBoard(Board *const board) {
  // to do.
}

void drawBoard(const Board *const board) {
  DrawText("Board", 10, 10, 24, PONG_COLOR_3);
}

void freeBoard(Board **board) {
  if (*board != NULL) {
    free(*board);
    *board = NULL;
    #ifdef PONG_DEBUG
    printf("deleted Board.\n");
    #endif
  }
}