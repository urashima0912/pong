#ifndef PONG_BALL_H
#define PONG_BALL_H

#include <raylib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Ball {
  Vector2 position;
  Vector2 size;

} Ball;

Ball* initBall(Vector2 position);

void drawBall(const Ball *const ball);

void updateBall(Ball *ball);

void freeBall(Ball **ball);

#ifdef __cplusplus
}
#endif

#endif //PONG_BAL_H
