#include "global.h"
#include "../config.h"

Colors getPocketGB(void) {
  Colors colors = {0};
  colors.color0 = (Color){ 43, 43, 38, 255 };
  colors.color1 = (Color){ 112, 107, 102, 255 };
  colors.color2 = (Color){ 168, 159, 148, 255 };
  colors.color3 = (Color){ 224, 219, 205, 255 };
  return colors;
}

Colors getRusticGB(void) {
  Colors colors = {0};
  colors.color0 = (Color){ 44, 33, 55, 255 };
  colors.color1 = (Color){ 118, 68, 98, 255 };
  colors.color2 = (Color){ 169, 104, 104, 255 };
  colors.color3 = (Color){ 237, 180, 161, 255 };
  return colors;
}

Colors getMistGB(void) {
  Colors colors = {0};
  colors.color0 = (Color){ 45, 27, 0, 255 };
  colors.color1 = (Color){ 30, 96, 110, 255 };
  colors.color2 = (Color){ 90, 185, 168, 255 };
  colors.color3 = (Color){ 196, 240, 194, 255 };
  return colors;
}

Colors getCrimsonGB(void) {
  Colors colors = {0};
  colors.color0 = (Color){ 27, 3, 38, 255 };
  colors.color1 = (Color){ 122, 28, 75, 255 };
  colors.color2 = (Color){ 186, 80, 68, 255 };
  colors.color3 = (Color){ 239, 249, 214, 255 };
  return colors;
}

void initGlobal(Global *const globalData) {
    globalData->theme = THEME_MIST_GB;
    globalData->mode = MODE_CPU;
    globalData->ptos = 5;
    globalData->fullScreen = false;
    globalData->leftSound = LoadSound("./assets/sound/left.wav");
    globalData->rightSound = LoadSound("./assets/sound/right.wav");
    SetSoundVolume(globalData->leftSound, 1.0);
    SetSoundVolume(globalData->rightSound, 1.0);
}

void freeGlobal(Global *const globalData) {
  UnloadSound(globalData->leftSound);
  UnloadSound(globalData->rightSound);
}


void drawMenuInfo(Global globalData) {
  const int32_t fontSize = 14;
  const int32_t middleWidth = GetScreenWidth() / 2;
  const int32_t posX = middleWidth - MeasureText(PONG_DEVELOPED_BY, fontSize) / 2;
  const int32_t posY = GetScreenHeight() - 20;
  DrawText(PONG_DEVELOPED_BY, posX, posY, fontSize, globalData.colors.color3);
}