#ifndef PONG_CONFIG_H
#define PONG_CONFIG_H

#include <raylib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PONG_SCREEN_WIDTH 640
#define PONG_SCREEN_HEIGHT 480
#define PONG_SCREEN_TITLE "Pong!"

#define PONG_DEBUG 1
#define PONG_PIVOT 1

// #define PONG_GAMEBOY_POCKET_COLOR 1
#ifndef PONG_GAMEBOY_POCKET_COLOR
#define PONG_COLOR_0 (Color){ 13, 4, 5, 255 }
#define PONG_COLOR_1 (Color){ 94, 18, 16, 255 }
#define PONG_COLOR_2 (Color){ 211, 86, 0, 255 }
#define PONG_COLOR_3 (Color){ 254, 208, 24, 255 }
#else
#define PONG_COLOR_0 (Color){ 43, 43, 38, 255 }
#define PONG_COLOR_1 (Color){ 112, 107, 102, 255 }
#define PONG_COLOR_2 (Color){ 168, 159, 148, 255 }
#define PONG_COLOR_3 (Color){ 224, 219, 205, 255 }
#endif

#ifdef __cplusplus
}
#endif

#endif //PONG_CONFIG_H
