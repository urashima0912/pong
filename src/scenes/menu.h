#ifndef PONG_MENU_H
#define PONG_MENU_H

#include "../global.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Menu {
  OptionEvent option;
} Menu;

Menu *initMenu(void);

void updateMenu(Menu *const menu);

void drawMenu(const Menu *const menu);

void freeMenu(Menu **menu);

OptionEvent finishMenu(void);

#ifdef __cplusplus
}
#endif

#endif /* PONG_MENU_H */
