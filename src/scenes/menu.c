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
  DrawText("MENU", 10, 10, 24, PONG_COLOR_2);
}

void freeMenu(Menu **menu) {
  if (*menu != NULL) {
    free(*menu);
    *menu = NULL;
    #ifdef PONG_DEBUG
    TraceLog(LOG_INFO, "xxx Menu DELETED.");
    #endif
  }
}