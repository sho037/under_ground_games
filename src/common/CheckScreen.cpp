#include <ncurses.h>
#include <vector>
#include <string>
#include "../../include/common/JsonData.hpp"

/**
 * スクリーンサイズを取得し、判定する
 */
bool isOkScreenSize()
{
  JsonData json_data;
  struct CheckScreenSize
  {
    int width;
    int height;
  };
  int width, height;
  CheckScreenSize check_screen_size;
  std::vector<std::string> data_path_width;
  std::vector<std::string> data_path_height;
  data_path_width.push_back("ScreenSize");
  data_path_width.push_back("width");
  data_path_height.push_back("ScreenSize");
  data_path_height.push_back("height");

  // 判定
  getmaxyx(stdscr, height, width);
  check_screen_size.width = atoi(json_data.getStrFromJsonData("ConfigData", data_path_width));
  check_screen_size.height = atoi(json_data.getStrFromJsonData("ConfigData", data_path_height));

  if (width < check_screen_size.width || height < check_screen_size.height)
  {
    fprintf(stderr, "画面サイズが小さいです。\n現在のサイズ：width: %d, height: %d\n必要なサイズ：width: %d, height: %d\n", width, height, check_screen_size.width, check_screen_size.height);
    return false;
  }
  return true;
}