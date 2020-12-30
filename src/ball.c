#include "ball.h"
#include <stdlib.h>

Ball* initBall(Vector2 position) {
  Ball *ball = malloc(sizeof(Ball));
  if (ball == NULL) {
    return NULL;
  }
  ball->position = position;
  ball->size = (Vector2){1.0, 1.0};
  return ball;
}

void drawBall(const Ball *const ball) {
  DrawRectangle(
    ball->position.x,
    ball->position.y,
    ball->size.x,
    ball->size.y,
    RAYWHITE
  );
}

void updateBall(Ball *ball) {
  //I need to do it.
}

void freeBall(Ball **ball) {
  if (*ball != NULL) {
    free(*ball);
    *ball = NULL;
  }
}