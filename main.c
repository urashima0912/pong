#include <raylib.h>
#include "src/palette.h"
#include "config.h"

int main(void) {
  InitWindow(PONG_SCREEN_WIDTH, PONG_SCREEN_HEIGHT, PONG_SCREEN_TITLE);

  HideCursor();
  Vector2 pos = (Vector2){ 10.0, 10.0 };
  Palette *palette = initPalette(pos);

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    // here we are updating objects.
    updatePalette(palette);
    // here we are drawing objects.
    BeginDrawing();
    ClearBackground(PONG_COLOR_0);

    drawPalette(palette);

    EndDrawing();
  }
  freePalette(&palette); // freeing palette's memory
  CloseWindow();

  return 0;
}