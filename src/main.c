#include <stdio.h>
#include <jansson.h>
#include <ncurses.h>
#include <unistd.h>

int status_code;

typedef struct
{
  int width;
  int height;
} ScreenSize;

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

/*
  このプログラムが終了する際の処理を記述する
*/
void endProcess(){
  endwin();
  return;
}

void printStatus()
{
  if (status_code == 0)
  {
    printf("Success.\n");
  }
  else
  {
    printf("Failed.\n");
  }
}

void process(){
  if (checkScreenSize() != 0){
    return;
  }
}

int main(int argc, char const *argv[])
{
  process();

  printStatus();

  endProcess();
  return status_code;
}
