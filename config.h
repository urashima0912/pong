#ifndef PONG_CONFIG_H
#define PONG_CONFIG_H

#include <raylib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PONG_SCREEN_WIDTH 480
#define PONG_SCREEN_HEIGHT 360
#define PONG_SCREEN_TITLE "Pong!"
#define PONG_TITLE "PONG"
#define PONG_OPTIONS_TITLE "Options"
#define PONG_OPTION_THEME "THEME:"
#define PONG_OPTION_MAX_PTOS "MAX PTOS:"
#define PONG_OPTION_GAME_MODE "GAME MODE:"
#define PONG_FULLSCREEN "FULLSCREEN:"
#define PONG_OPTION_GAME_MODE_PVP "PvP"
#define PONG_OPTION_GAME_MODE_CPU "PvE"

#define PONG_THEME_POCKET_GB "PoscketGB"
#define PONG_THEME_RUSTIC_GB "RusticGB"
#define PONG_THEME_MIST_GB "MistGB"
#define PONG_THEME_CRIMSON_GB "CrimsonGB"

#define PONG_COLOR_SHAPE BLUE

#define PONG_MSG_WINNER "WINNER"
#define PONG_MSG_START "START"
#define PONG_MSG_OPTIONS "OPTIONS"
#define PONG_MSG_EXIT "EXIT"
#define PONG_DEVELOPED_BY "developed by kenshin urashima 2021"

#define PONG_SCENE_OPTIONS_DELETED "-->\t Options DELETED."
#define PONG_SCENE_MENU_DELETED "-->\t Menu DELETED."
#define PONG_BOARD_DELETED "-->\t Board DELETED."
#define PONG_SCENE_HANDLER_DELETED "-->\t SceneHandler DELETED."
#define PONG_PALETTE_DELETED "-->\t Palette DELETED."
#define PONG_BALL_DELETED "-->\t Ball DELETED."
#define PONG_APP_DELETED "-->\t App DELETED."

// #define PONG_DEBUG 1

#ifdef __cplusplus
}
#endif

#endif //PONG_CONFIG_H
