#include "ball.h"
#include "../config.h"
#include <stdlib.h>
#include <math.h>
#ifdef PONG_DEBUG
#include <stdio.h>
#endif

// declarations constants
static const float SPEED = 3.3;

// declaration static functions.
static void showShapeBall(const Ball *const ball);
static bool collisionPalette(const Ball *const ball, const Palette *const palette);
static void changeBallVelocity(Ball *const ball, const Palette *const palette);

// implementation public functions.
Ball* initBall(Vector2 position) {
  Ball *ball = malloc(sizeof(Ball));
  if (ball == NULL) {
    return NULL;
  }
  ball->position = position;
  ball->size = (Vector2){10.0, 10.0};
  ball->velocity = (Vector2) { 0, 0 };
  
  const int32_t isLeft = GetRandomValue(0, 1);
  ball->velocity.x = (isLeft) ? -1 : 1;

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

void updateBall(Ball *ball, const Palette *const player, const Palette *const enemy) {
  ball->position.x += ball->velocity.x * SPEED;
  ball->position.y += ball->velocity.y * SPEED;

  // detect collision with player
  if (collisionPalette(ball, player)) {
    changeBallVelocity(ball, player);
  }

  if (collisionPalette(ball, enemy)) {
    changeBallVelocity(ball, enemy);
  }

  if (ball->position.y < 0 || ball->position.y > GetScreenHeight() - 10) {
    ball->velocity.y *= -1;
  } 
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

static bool collisionPalette(const Ball *const ball, const Palette *const palette) {
  const Rectangle recBall = (Rectangle) {
    ball->position.x,
    ball->position.y,
    ball->size.x,
    ball->size.y,
  };

  const Rectangle recPalette = (Rectangle) {
    palette->position.x,
    palette->position.y,
    palette->size.x,
    palette->size.y,
  };

  return CheckCollisionRecs(recBall, recPalette);
}

static void changeBallVelocity(Ball *const ball, const Palette *const palette) {
  ball->velocity.x *= -1;
  if (palette->velocity.y != 0) {
    const int32_t angle = GetRandomValue(25, 60);
    ball->velocity.y = sin(angle * palette->velocity.y);
  }
}
