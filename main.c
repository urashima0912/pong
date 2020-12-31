#include <raylib.h>
#include <stdlib.h>
#include "src/app.h"

int main(void) {
  App *app = initApp();
  if (app == NULL) {
    return 1;
  }
  runApp(app);
  freeApp(&app);

  return 0;
}
