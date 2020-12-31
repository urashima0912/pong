#include "board.h"
#include <stdlib.h>

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
  // to do.
}

void freeBoard(Board **board) {
  if (*board != NULL) {
    free(*board);
    *board = NULL;
  }
}