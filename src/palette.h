#ifndef PONG_PALETTE_H
#define PONG_PALETTE_H

#include <raylib.h>
#include "global.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Palette {
  Vector2 position;
  Vector2 size;
  Vector2 velocity;
  Color color;

  bool isEnemy;

} Palette;

Palette *initPalette(Vector2 position, bool isEnemy);

void drawPalette(const Palette *const palette);

void updatePalette(Palette *const palette, const GameObject gameObject);

void freePalette(Palette **palette);

#ifdef __cplusplus
}
#endif

#endif //PONG_PALETTE_H
