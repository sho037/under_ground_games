#include <stdio.h>
#include <jansson.h>
#include <ncurses.h>
#include <unistd.h>
#include "../include/PrintStatus.hpp"
#include "../include/UGGames.hpp"
#include "../include/common/CommonProcess.hpp"
#include "../include/common/CheckScreen.hpp"

int status_code;

typedef struct
{
  int width;
  int height;
} ScreenSize;

ScreenSize getScreenSizeFromConfig()
{
  ScreenSize ScreenSize;

  ScreenSize.width = 0;
  ScreenSize.height = 0;

  // JSONファイルからスクリーンサイズを取得
  json_error_t jerror;
  json_t* root;

  FILE *file = fopen("data/ConfigData.json", "r");
  if (!file){
    fclose(file);
    status_code = -111;
    return ScreenSize;
  }

  root = json_loadf(file, 0, &jerror);
  if (!root) {
    fprintf(stderr, "%d: %s\n", jerror.line, jerror.text);
    fclose(file);
    status_code = -210;
    return ScreenSize;
  }

  // "ScreenSize"オブジェクトを取得
  json_t* screen_size = json_object_get(root, "ScreenSize");
  if (!json_is_object(screen_size)){
    fclose(file);
    status_code = -211;
    return ScreenSize;
  }

  // "width"を取得
  json_t* width = json_object_get(screen_size, "width");
  if (!json_is_integer(width)){
    fclose(file);
    status_code = -212;
    return ScreenSize;
  }

  // "height"を取得
  json_t* height = json_object_get(screen_size, "height");
  if (!json_is_integer(height)){
    fclose(file);
    status_code = -213;
    return ScreenSize;
  }

  ScreenSize.width = json_integer_value(width);
  ScreenSize.height = json_integer_value(height);

  return ScreenSize;
}

int checkScreenSize()
{
  ScreenSize ScreenSize = getScreenSizeFromConfig();

  initscr();

  int max_x, max_y;

  getmaxyx(stdscr, max_y, max_x);

  if (max_x < ScreenSize.width || max_y < ScreenSize.height)
  {
    status_code = -500;
    return status_code;
  }

  return status_code;
}

void printStatusProcess()
{
  if (status_code == 0)
  {
    printf("バイバイ！\n");
  }
  else
  {
    printStatus(status_code);
  }
}

void process(){
  if (isOkScreenSize() == false){
    return;
  }

  sleep(10);
}

int main(int argc, char const *argv[])
{
  CommonProcess commonProcess;

  process();
  
  commonProcess.endProcess();

  printStatusProcess();

  return status_code;
}
