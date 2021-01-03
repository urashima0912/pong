#ifndef PONG_CONFIG_H
#define PONG_CONFIG_H

#include <raylib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PONG_SCREEN_WIDTH 480
#define PONG_SCREEN_HEIGHT 360
#define PONG_SCREEN_TITLE "Pong!"

#define PONG_COLOR_SHAPE BLUE

#define PONG_MSG_WINNER "Winner!!"
#define PONG_MSG_START "start"
#define PONG_MSG_OPTIONS "options"
#define PONG_MSG_EXIT "exit"
#define PONG_DEVELOPED_BY "developed by kenshin urashima 2021"

#define PONG_SCENE_OPTIONS_DELETED "-->\t Options DELETED."
#define PONG_SCENE_MENU_DELETED "-->\t Menu DELETED."
#define PONG_BOARD_DELETED "-->\t Board DELETED."
#define PONG_SCENE_HANDLER_DELETED "-->\t SceneHandler DELETED."
#define PONG_PALETTE_DELETED "-->\t Palette DELETED."
#define PONG_BALL_DELETED "-->\t Ball DELETED."
#define PONG_APP_DELETED "-->\t App DELETED."

#define PONG_DEBUG 1

#ifdef __cplusplus
}
#endif

#endif //PONG_CONFIG_H
