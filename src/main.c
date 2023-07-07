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

/*
  このプログラムが終了する際の処理を記述する
*/
void endProcess()
{
  endwin();
  return;
}

/*
  StatusData.jsonを読み込み、その中身を返す
  大域変数status_codeによって返す内容を変更する
*/
char *getStatusData(){
  // JSONオブジェクトを入れる変数
  json_error_t jerror;
  json_t* root;

  FILE *file = fopen("data/StatusData.json", "r");
  if (!file){
    fprintf(stderr, "error: in getStatusData: ファイル読み込み失敗\n");
    endProcess();
    exit(1);
  }

  root = json_loadf(file, 0, &jerror);
  if (!root) {
    fprintf(stderr, "error: in getStatusData: JSONパースエラー: 行 %d: %s\n", jerror.line, jerror.text);
    fclose(file);
    endProcess();
    exit(1);
  }

  int test = json_integer_value(json_object_get(root, "test"));

  fclose(file);

  return ;
}

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

void printStatus()
{
  if (status_code == 0)
  {
    printf("バイバイ！\n");
  }
  else
  {
    printf("%s\n", getStatusData());
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
