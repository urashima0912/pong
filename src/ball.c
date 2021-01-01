#include "ball.h"
#include "../config.h"
#include <stdlib.h>
#ifdef PONG_DEBUG
#include <stdio.h>
#endif

// declaration static functions.
static void showShapeBall(const Ball *const ball);


// implementation public functions.
Ball* initBall(Vector2 position) {
  Ball *ball = malloc(sizeof(Ball));
  if (ball == NULL) {
    return NULL;
  }
  ball->position = position;
  ball->size = (Vector2){10.0, 10.0};
  return ball;
}

void drawBall(const Ball *const ball) {
  DrawRectangle(
    ball->position.x,
    ball->position.y,
    ball->size.x,
    ball->size.y,
    PONG_COLOR_3
  );

  #ifdef PONG_PIVOT
  showShapeBall(ball);
  #endif
}

void updateBall(Ball *ball) {
  //I need to do it.
}

void freeBall(Ball **ball) {
  if (*ball != NULL) {
    free(*ball);
    *ball = NULL;
    #ifdef PONG_DEBUG
    printf("ball deleted.\n");
    #endif
  }
}


// implementation static functions.
static void showShapeBall(const Ball *const ball) {
  DrawRectangleLines(
    ball->position.x,
    ball->position.y,
    ball->size.x,
    ball->size.y,
    BLUE
  );
}
