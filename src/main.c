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
const char *getStatusData(){
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

  // "StatusData"配列を取得
  json_t* status_data = json_object_get(root, "StatusData");
  if (!json_is_array(status_data)){
    fprintf(stderr, "error: in getStatusData: JSONパースエラー: StatusDataが配列ではないもしくは見つかりません\n");
    fclose(file);
    endProcess();
    exit(1);
  }

  size_t index;
  json_t* value;
  // status_codeによって返す内容を変更する
  json_array_foreach(status_data, index, value){
    // StatusCodeを取得
    json_t* status_code_json = json_object_get(value, "StatusCode");
    if (!json_is_integer(status_code_json)){
      fprintf(stderr, "error: in getStatusData: JSONパースエラー: StatusCodeが整数ではありません\n");
      fclose(file);
      endProcess();
      exit(1);
    }

    // status_codeが一致した場合、その内容を返す
    if (json_integer_value(status_code_json) == status_code){
      json_t* status_message_json = json_object_get(value, "Message");
      if (!json_is_string(status_message_json)){
        fprintf(stderr, "error: in getStatusData: JSONパースエラー: Messageが文字列ではありません\n");
        fclose(file);
        endProcess();
        exit(1);
      }

      fclose(file);

      const char *status_message = json_string_value(status_message_json);
      return status_message;
    }
  }

  fclose(file);

  return "test";
}

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

  return status_code;
}

void printStatus()
{
  if (status_code == 0)
  {
    printf("バイバイ！\n");
  }
  else
  {
    fprintf(stderr, "%s\n", getStatusData());
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
  
  endProcess();

  printStatus();

  return status_code;
}
