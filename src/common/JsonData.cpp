#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <jansson.h>
#include "../../include/common/JsonData.hpp"

// JSONオブジェクトを入れる変数
json_error_t jerror;
json_t *root;

// ファイル名を取得
const char *file_name;

FILE *file;

JsonData::JsonData(/* args */)
{
}

JsonData::~JsonData()
{
}

/**
 *
 */
void openFile()
{
  // ファイルを開く
  file = fopen(file_name, "r");
  if (!file)
  {
    fprintf(stderr, "error: in getStrFromJsonData: ファイル読み込み失敗\nfile_name: %s\n", file_name);
    exit(1);
  }
}

/**
 *
 */
void closeFile()
{
  // ファイルを閉じる
  fclose(file);
}

/**
 *
 */
void loadJson()
{
  // JSONファイルを読み込む
  root = json_loadf(file, 0, &jerror);
  if (!root)
  {
    fprintf(stderr, "error: in getStrFromJsonData: JSONパースエラー: 行 %d: %s\n", jerror.line, jerror.text);
    fclose(file);
    exit(1);
  }
}

/**
 * data_typeをファイル名に変更し返却
 */
const char *JsonData::changeDataTypeToFileName(const char *data_type)
{
  // data_typeをファイル名に変更
  if (strcmp(data_type, "StatusData") == 0)
  {
    return "data/StatusData.json";
  }
  else if (strcmp(data_type, "ConfigData") == 0)
  {
    return "data/ConfigData.json";
  }
  else
  {
    fprintf(stderr, "program error: in changeDataTypeToFileName: status_typeが不正\n");
    exit(1);
  }
}

/**
 * 引数として与えられたオブジェクトの内容を返す(配列は未対応)
 * data_typeには読み込むJSONファイルの種類を、objectsには読み込むJSONファイルのオブジェクト名を指定する
 * @param data_type 読み込むJSONファイルの種類
 * @param objects 読み込むJSONファイルのオブジェクト名のリスト
 * @return 読み込んだJSONファイルのオブジェクトの内容 (const char *)
 */
const char *JsonData::getStrFromJsonData(const char *data_type, const std::vector<std::string> &objects)
{
  file_name = changeDataTypeToFileName(data_type);

  // ファイルを開く
  openFile();

  // JSONファイルを読み込む
  loadJson();

  // オブジェクトの数を取得
  int numArgs = objects.size();

  // オブジェクトの内容を取得
  json_t *object = root;
  for (int i = 0; i < numArgs; i++)
  {
    object = json_object_get(object, objects[i].c_str());
  }

  // オブジェクトの内容を返す
  return json_string_value(object);
}