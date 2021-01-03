#include "menu.h"
#include "../../config.h"

#include <stdlib.h>
#include <stdint.h>

extern Global globalData;

static OptionEvent onOptionEvent = OPT_EMPTY;
static void updateMenuOptions(Menu *const menu);
static void drawMenuOptions(const Menu *const menu);
static void drawMenuInfo(void);

Menu *initMenu(void) {
  onOptionEvent = OPT_EMPTY;
  Menu *menu = malloc(sizeof(Menu));
  if (menu == NULL) {
    return NULL;
  }

  menu->option = OPT_START;

  return menu;
}

void updateMenu(Menu *const menu) {
  updateMenuOptions(menu);

  if (IsKeyPressed(KEY_ENTER)) {
    if (menu->option == OPT_START) {
      onOptionEvent = OPT_START;
    }
    else if (menu->option == OPT_OPTIONS) {
      onOptionEvent = OPT_OPTIONS;
    }
    else if (menu->option == OPT_EXIT) {
      onOptionEvent = OPT_EXIT;
    }
  }
}

void drawMenu(const Menu *const menu) {
  drawMenuOptions(menu);
  drawMenuInfo();
}

void freeMenu(Menu **menu) {
  if (*menu != NULL) {
    free(*menu);
    *menu = NULL;
    #ifdef PONG_DEBUG
    TraceLog(LOG_INFO, PONG_SCENE_MENU_DELETED);
    #endif
  }
}

OptionEvent finishMenu(void) {
  return onOptionEvent;
}

static void drawMenuOptions(const Menu *const menu) {
  const int32_t middleWidth = GetScreenWidth() / 2;
  const int32_t middleHeight = GetScreenHeight() / 2;
  const int32_t fontSize = 24;
  const int32_t posY = middleHeight + 30;
  const int32_t posXStart = middleWidth - (TextLength(PONG_MSG_START) * (fontSize / 2)) / 2;
  const int32_t posXOptions = middleWidth - (TextLength(PONG_MSG_OPTIONS) * (fontSize / 2)) / 2;
  const int32_t posXExit = middleWidth - (TextLength(PONG_MSG_EXIT) * (fontSize / 2)) / 2;

  const Color startColor = (menu->option == OPT_START) ? globalData.colors.color3 : globalData.colors.color1;
  const Color optionsColor = (menu->option == OPT_OPTIONS) ? globalData.colors.color3 : globalData.colors.color1;
  const Color endColor = (menu->option == OPT_EXIT) ? globalData.colors.color3 : globalData.colors.color1;

  DrawText(PONG_MSG_START, posXStart, posY, fontSize, startColor);
  DrawText(PONG_MSG_OPTIONS, posXOptions, posY + fontSize, fontSize, optionsColor);
  DrawText(PONG_MSG_EXIT, posXExit, posY + (fontSize * 2), fontSize, endColor);
}

static void updateMenuOptions(Menu *const menu) {
  const int32_t min = (int32_t) OPT_START;
  const int32_t max = (int32_t) OPT_EXIT;
  if (IsKeyPressed(KEY_UP)) {
    const int32_t value = menu->option - 1;
    if (value >= min) {
      menu->option--;
    } else {
      menu->option = OPT_EXIT;
    }
  } else if (IsKeyPressed(KEY_DOWN)) {
    const int32_t value = menu->option + 1;
    if (value <= max) {
      menu->option++;
    } else {
      menu->option = OPT_START;
    }
  }
}

static void drawMenuInfo(void) {
  const int32_t fontSize = 14;
  const int32_t middleWidth = GetScreenWidth() / 2;
  const int32_t posX = middleWidth - TextLength(PONG_DEVELOPED_BY) * (fontSize / 2) / 2;
  const int32_t posY = GetScreenHeight() - 20;
  DrawText(PONG_DEVELOPED_BY, posX, posY, fontSize, globalData.colors.color3);
}

