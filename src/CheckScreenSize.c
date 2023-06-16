#include <ncurses.h>
#include <unistd.h>
#include "../include/CheckScreenSize.h"

ScreenSize getScreenSizeFromConfig()
{
  ScreenSize ScreenSize;
  ScreenSize.width = 800;
  ScreenSize.height = 600;
  return ScreenSize;
}

int checkScreenSize()
{
  ScreenSize ScreenSize = getScreenSizeFromConfig();
  initscr();

  return 0;
}
