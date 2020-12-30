#ifndef PONG_PALETTE_H
#define PONG_PALETTE_H

#include <raylib.h>

typedef struct Palette {
  Vector2 position;
  Vector2 size;

} Palette;

Palette *initPalette(Vector2 position);

void drawPalette(const Palette *const palette);

void updatePalette(Palette *palette);

void freePalette(Palette **palette);

#endif //PONG_PALETTE_H
