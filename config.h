#ifndef PONG_CONFIG_H
#define PONG_CONFIG_H

#include <raylib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_TITLE "Pong!"

#define GAMEBOY_POCKET_COLOR

#ifndef GAMEBOY_POCKET_COLOR
#define COLOR_0 (Color){ 13, 4, 5, 255 }
#define COLOR_1 (Color){ 94, 18, 16, 255 }
#define COLOR_2 (Color){ 211, 86, 0, 255 }
#define COLOR_3 (Color){ 254, 208, 24, 255 }
#else
#define COLOR_0 (Color){ 43, 43, 38, 255 }
#define COLOR_1 (Color){ 112, 107, 102, 255 }
#define COLOR_2 (Color){ 168, 159, 148, 255 }
#define COLOR_3 (Color){ 224, 219, 205, 255 }
#endif

#endif //PONG_CONFIG_H
