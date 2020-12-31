#include "palette.h"
#include "../config.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

// constants and variables.
static const int32_t PALETTE_WIDTH = 15.0;
static const int32_t PALETTE_HEIGHT = 100.0;
static const float SPEED = 4.2;
static const Color colorPalette = COLOR_3;


// declaration of static methods.
static void getEvent(Palette *palette);
static bool canGetUp(Palette *palette);
static bool canGetDown(Palette *palette);

// implementation of public methods.
Palette *initPalette(Vector2 position) {
  Palette *palette = malloc(sizeof(Palette));
  if (palette == NULL) {
    return NULL;
  }
  palette->position = position;
  palette->size = (Vector2){ PALETTE_WIDTH, PALETTE_HEIGHT };
  palette->color = colorPalette;
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

  // x pivot.
  DrawLine(
    palette->position.x - 10,
    palette->position.y,
    palette->position.x + 10,
    palette->position.y,
    RED
  );
  DrawLine(
    palette->position.x,
    palette->position.y - 10,
    palette->position.x,
    palette->position.y + 10,
    GREEN
  );
}

void updatePalette(Palette *palette) {
  getEvent(palette);
}

void freePalette(Palette **palette) {
  if (*palette != NULL) {
    free(*palette);
    *palette = NULL;
  }
}

// implementation of static methods.
static void getEvent(Palette *palette) {
  if (canGetUp(palette) && (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))) {
    palette->position.y -= SPEED;
  } else if (canGetDown(palette) && (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))) {
    palette->position.y += SPEED;
  }
}

static bool canGetUp(Palette *palette) {
  const int32_t minPosY = 0;
  return !(palette->position.y < minPosY);
}

static bool canGetDown(Palette *palette) {
  const float currentPosY = palette->position.y + palette->size.y;
  const int32_t maxPosY = GetScreenHeight();
  return !(currentPosY > maxPosY);
}