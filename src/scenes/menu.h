#ifndef PONG_MENU_H
#define PONG_MENU_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Menu {
  /* to do */
} Menu;

Menu *initMenu(void);

void updateMenu(Menu *const menu);

void drawMenu(const Menu *const menu);

void freeMenu(Menu **menu);

#ifdef __cplusplus
}
#endif

#endif /* PONG_MENU_H */
