#ifndef PONG_BOARD_H
#define PONG_BOARD_H

#include "../palette.h"
#include "../ball.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Board {
  Palette *player;
  Palette *enemy;
  Ball *ball;

  int32_t ptoEnemy;
  int32_t ptoPlayer;

  Rectangle recLeft;
  Rectangle recRight;

} Board;

Board *initBoard(void);

void updateBoard(Board *const board);

void drawBoard(const Board *const board);

void freeBoard(Board **board);

bool finishBoard(void);

#ifdef __cplusplus
}
#endif

#endif /* PONG_BOARD_H */