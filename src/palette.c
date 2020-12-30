#include "palette.h"
#include "../config.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

static const int32_t PALETTE_WIDTH = 15.0;
static const int32_t PALETTE_HEIGHT = 100.0;

static const float SPEED = 4.2;

Palette *initPalette(Vector2 position) {
  Palette *palette = malloc(sizeof(Palette));
  if (palette == NULL) {
    return NULL;
  }
  palette->position = position;
  palette->size = (Vector2){ PALETTE_WIDTH, PALETTE_HEIGHT };
  return palette;
}

void drawPalette(const Palette *const palette) {
  DrawRectangle(
    palette->position.x,
    palette->position.y,
    palette->size.x,
    palette->size.y,
    COLOR_2
  );
}

// this function handles the object update
void updatePalette(Palette *palette) {
  if (IsKeyDown(KEY_W)) {
    palette->position.y -= SPEED;
  } else if (IsKeyDown(KEY_S)) {
    palette->position.y += SPEED;
  }
}

void freePalette(Palette **palette) {
  if (*palette != NULL) {
    free(*palette);
    *palette = NULL;
  }
}