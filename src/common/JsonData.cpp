#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <jansson.h>
#include <unistd.h>
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
void openFile(const char *open_mode)
{
  // ファイルを開く
  file = fopen(file_name, open_mode);
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
  else if (strcmp(data_type, "HTTPer") == 0)
  {
    return "data/HTTPer.json";
  }
  else if (strcmp(data_type, "Ubuntur") == 0)
  {
    return "data/Ubuntur.json";
  }
  else if (strcmp(data_type, "ScoreData") == 0)
  {
    return "data/ScoreData.json";
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
  openFile("r");

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

/**
 * JSONファイルからランダムに一つ問題データを取得する
 * @param data_type 読み込むJSONファイルの種類
 * @return 読み込んだJSONファイルのオブジェクトの内容 (struct question_data)
 */
struct question_data JsonData::getRandomQuestionData(const char *data_type)
{
  struct question_data question_data;

  file_name = changeDataTypeToFileName(data_type);

  // ファイルを開く
  openFile("r");

  // JSONファイルを読み込む
  loadJson();

  // オブジェクトの内容を取得
  json_t *object_array = json_object_get(root, data_type);
  if (!json_is_array(object_array))
  {
    fprintf(stderr, "error: in getRondomQuestionData: JSONファイルのオブジェクトが配列ではありません\n");
    json_decref(root);
    closeFile();
    exit(1);
  }

  // オブジェクトの数を取得
  int numArgs = json_array_size(object_array);

  // オブジェクトの内容をランダムに一つ取得
  json_t *object = json_array_get(object_array, rand() % numArgs);

  // オブジェクトの内容を返す
  question_data.id = json_string_value(json_object_get(object, "id"));
  question_data.output = json_string_value(json_object_get(object, "Output"));
  question_data.question = json_string_value(json_object_get(object, "Question"));

  // ファイルを閉じる
  closeFile();

  return question_data;
};

/**
 * JSONファイルから上位10件のスコアデータを取得する
 * データ形式は以下の通り
 * {
 * "ScoreData": [
 *    {
 *       "id": 0,
 *      "name": "Player",
 *     "score": 0
 *   }
 * ]
 * }
 * @param data_type 読み込むJSONファイルの種類
 * @return 読み込んだJSONファイルのオブジェクトの内容 (struct score_dataの配列)
 */
std::vector<struct score_data> JsonData::getScoreData(const char *data_type)
{
  std::vector<struct score_data> score_data;

  file_name = changeDataTypeToFileName(data_type);

  // ファイルを開く
  openFile("r");

  // JSONファイルを読み込む
  loadJson();

  // オブジェクトの内容を取得
  json_t *object_array = json_object_get(root, data_type);
  if (!json_is_array(object_array))
  {
    fprintf(stderr, "error: in getScoreData: JSONファイルのオブジェクトが配列ではありません\n");
    json_decref(root);
    closeFile();
    exit(1);
  }

  // オブジェクトの数を取得
  int numArgs = json_array_size(object_array);

  // オブジェクトの内容を取得
  for (int i = 0; i < numArgs; i++)
  {
    json_t *object = json_array_get(object_array, i);
    struct score_data score;
    score.id = json_integer_value(json_object_get(object, "id"));
    score.name = json_string_value(json_object_get(object, "name"));
    score.score = json_integer_value(json_object_get(object, "score"));
    score_data.push_back(score);
  }

  // ファイルを閉じる
  closeFile();

  return score_data;
};

/**
 * スコアデータをJSONファイルに書き込む
 * @param data_type 読み込むJSONファイルの種類
 * @param name プレイヤー名
 * @param score スコア
 */
void JsonData::writeScoreData(const char *data_type, const char *name, int score)
{
  file_name = changeDataTypeToFileName(data_type);

  // ファイルを開く
  openFile("r+");

  // JSONファイルを読み込む
  loadJson();

  // オブジェクトの内容を取得
  json_t *object_array = json_object_get(root, data_type);
  if (!json_is_array(object_array))
  {
    fprintf(stderr, "error: in writeScoreData: JSONファイルのオブジェクトが配列ではありません\n");
    json_decref(root);
    closeFile();
    exit(1);
  }

  // オブジェクトの数を取得
  int numArgs = json_array_size(object_array);

  // オブジェクトの内容を取得
  json_t *object = json_object();
  json_object_set_new(object, "id", json_integer(numArgs));
  json_object_set_new(object, "name", json_string(name));
  json_object_set_new(object, "score", json_integer(score));

  // オブジェクトを配列に追加
  json_array_append(object_array, object);

  // ファイルを閉じる
  closeFile();

  // ファイルを開く
  openFile("w");

  // JSONファイルを書き込む
  json_dumpf(root, file, JSON_INDENT(2));

  // ファイルを閉じる
  closeFile();

  return;
};