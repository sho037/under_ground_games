#include <stdio.h> // 後で削除
#include "../include/ScreenSetting.h"

ScreenSize getScreenSize()
{
  ScreenSize ScreenSize;
  ScreenSize.width = 800;
  ScreenSize.height = 600;
  return ScreenSize;
}

int setScreenSize() {
  ScreenSize ScreenSize = getScreenSize();
  
  return 0;
}
