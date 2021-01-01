#ifndef PONG_BALL_H
#define PONG_BALL_H

#include <raylib.h>
#include "palette.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Ball {
  Vector2 position;
  Vector2 size;
  Vector2 velocity;
} Ball;

Ball* initBall(void);

void drawBall(const Ball *const ball);

void updateBall(Ball *ball, const Palette *const player, const Palette *const enemy);

void freeBall(Ball **ball);

void resetBall(Ball *const ball);

#ifdef __cplusplus
}
#endif

#endif //PONG_BAL_H
