#include "palette.h"
#include "../config.h"
#include "pivot.h"
#include "global.h"
#include <stdlib.h>
#include <stdint.h>

extern Global globalData;

// constants and variables.
static const int32_t PALETTE_WIDTH = 15.0;
static const int32_t PALETTE_HEIGHT = 100.0;
static const float SPEED = 5.2;


// declaration of static methods.
static bool canGetDown(Palette *palette);
static bool canGetUp(Palette *palette);
static void getEvent(Palette *palette);
static void showShapeArea(const Palette *const palette);

// implementation of public methods.
Palette *initPalette(Vector2 position, bool isEnemy) {
  Palette *palette = malloc(sizeof(Palette));
  if (palette == NULL) {
    return NULL;
  }
  palette->position = position;
  palette->size = (Vector2){ PALETTE_WIDTH, PALETTE_HEIGHT };
  palette->color = globalData.colors.color3;
  palette->isEnemy = isEnemy;
  palette->velocity = (Vector2) { 0.0f, 0.0f };

  return palette;
}

void drawPalette(const Palette *const palette) {
  if (globalData.showCollisionShape) {
    drawPivot(palette->position);
    showShapeArea(palette);
  } else {
    DrawRectangle(
      palette->position.x,
      palette->position.y,
      palette->size.x,
      palette->size.y,
      palette->color
    );
  }
}

void updatePalette(Palette *palette) {
  getEvent(palette);
}

void freePalette(Palette **palette) {
  if (*palette != NULL) {
    free(*palette);
    *palette = NULL;
    #ifdef PONG_DEBUG
    TraceLog(LOG_INFO, PONG_PALETTE_DELETED);
    #endif
  }
}


// implementation of static methods.
static bool canGetDown(Palette *palette) {
  const float currentPosY = palette->position.y + palette->size.y;
  const int32_t maxPosY = GetScreenHeight();
  return !(currentPosY > maxPosY);
}

static bool canGetUp(Palette *palette) {
  const int32_t minPosY = 0;
  return !(palette->position.y < minPosY);
}

static void getEvent(Palette *palette) {
  bool moveUp = false;
  bool moveDown = false;

  if (palette->isEnemy) {
    moveUp = canGetUp(palette) && IsKeyDown(KEY_UP);
    moveDown = canGetDown(palette) && IsKeyDown(KEY_DOWN);
  } else {
    moveUp = canGetUp(palette) && IsKeyDown(KEY_W);
    moveDown = canGetDown(palette) && IsKeyDown(KEY_S);
  }

  if (moveUp) {
    palette->velocity.y = -1;
  } else if (moveDown) {
    palette->velocity.y = 1;
  } else {
    palette->velocity.y = 0;
  }

  palette->position.y += palette->velocity.y * SPEED;
}

static void showShapeArea(const Palette *const palette) {
  DrawRectangleLines(
    palette->position.x,
    palette->position.y,
    palette->size.x,
    palette->size.y,
    PONG_COLOR_SHAPE
  );
}
