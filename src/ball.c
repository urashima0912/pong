#include "ball.h"
#include "../config.h"
#include "pivot.h"
#include "global.h"
#include <stdlib.h>
#include <math.h>

extern Global globalData;

// declarations constants
static const float SPEED = 6.3;
static const int32_t SIZE = 10;

// declaration static functions.
static void showShapeBall(const Ball *const ball);
static bool collisionPalette(const Ball *const ball, const Palette *const palette);
static void changeBallVelocity(Ball *const ball, const Palette *const palette);

// implementation public functions.
Ball* initBall(void) {
  Ball *ball = malloc(sizeof(Ball));
  if (ball == NULL) {
    return NULL;
  }
  ball->size = (Vector2){ SIZE, SIZE };
  resetBall(ball);

  return ball;
}

void drawBall(const Ball *const ball) {
  if (globalData.showCollisionShape) {
    showShapeBall(ball);
    drawPivot(ball->position);
  } else {
    DrawRectangle(
      ball->position.x,
      ball->position.y,
      ball->size.x,
      ball->size.y,
      globalData.colors.color3
    );
  }
}

void updateBall(Ball *ball, const Palette *const player, const Palette *const enemy) {
  ball->position.x += ball->velocity.x * SPEED;
  ball->position.y += ball->velocity.y * SPEED;

  // detect collision with player
  if (collisionPalette(ball, player)) {
    PlaySound(globalData.leftSound);
    changeBallVelocity(ball, player);
  }

  if (collisionPalette(ball, enemy)) {
    PlaySound(globalData.rightSound);
    changeBallVelocity(ball, enemy);
  }

  if (ball->position.y < 0 || ball->position.y > GetScreenHeight() - SIZE) {
    ball->velocity.y *= -1;
  }
}

void freeBall(Ball **ball) {
  if (*ball != NULL) {
    free(*ball);
    *ball = NULL;
    #ifdef PONG_DEBUG
    TraceLog(LOG_INFO, PONG_BALL_DELETED);
    #endif
  }
}

void resetBall(Ball *const ball) {
  ball->position.x = GetScreenWidth() / 2;
  ball->position.y = GetScreenHeight() / 2;
  ball->velocity = (Vector2) { 0, 0 };
  
  const int32_t isLeft = GetRandomValue(0, 1);
  ball->velocity.x = (isLeft) ? -1 : 1;
}


// implementation static functions.
static void showShapeBall(const Ball *const ball) {
  DrawRectangleLines(
    ball->position.x,
    ball->position.y,
    ball->size.x,
    ball->size.y,
    PONG_COLOR_SHAPE
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
    const int32_t value = GetRandomValue(30, 60);
    const float angle = DEG2RAD * value;
    ball->velocity.y = sin(angle * palette->velocity.y);
  } else {
    const int32_t value = GetRandomValue(0, 5);
    if (value > 4) {
      ball->velocity.y = 0;
    }
  }
}
