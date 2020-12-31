#ifndef PONG_BOARD_H
#define PONG_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Board {
  // to do.
} Board;

Board *initBoard(void);

void updateBoard(Board *const board);

void drawBoard(const Board *const board);

void freeBoard(Board **board);

#ifdef __cplusplus
}
#endif

#endif /* PONG_BOARD_H */