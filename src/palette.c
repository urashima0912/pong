#include "palette.h"
#include "../config.h"
#include "pivot.h"
#include <stdlib.h>
#include <stdint.h>
#ifdef PONG_DEBUG
#include <stdio.h>
#endif

// constants and variables.
static const Color COLOR_PALETTE = PONG_COLOR_3;
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
  palette->color = COLOR_PALETTE;
  palette->isEnemy = isEnemy;

  return palette;
}

void drawPalette(const Palette *const palette) {
  DrawRectangle(
    palette->position.x,
    palette->position.y,
    palette->size.x,
    palette->size.y,
    palette->color
  );
  #ifdef PONG_PIVOT
    drawPivot(palette->position);
    showShapeArea(palette);
  #endif
}

void updatePalette(Palette *palette) {
  getEvent(palette);
}

void freePalette(Palette **palette) {
  if (*palette != NULL) {
    free(*palette);
    *palette = NULL;
    #ifdef PONG_DEBUG
    printf("palette deleted \n");
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
    palette->position.y -= SPEED;
  } else if (moveDown) {
    palette->position.y += SPEED;
  }
}

static void showShapeArea(const Palette *const palette) {
  DrawRectangleLines(
    palette->position.x,
    palette->position.y,
    palette->size.x,
    palette->size.y,
    BLUE
  );
}
