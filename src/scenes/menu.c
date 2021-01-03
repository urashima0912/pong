#include "menu.h"
#include "../../config.h"
#include <stdlib.h>

Menu *initMenu(void) {
  Menu *menu = malloc(sizeof(Menu));
  if (menu == NULL) {
    return NULL;
  }
  return menu;
}

void updateMenu(Menu *const menu) {
  // to do.
}

void drawMenu(const Menu *const menu) {
  // to do.
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