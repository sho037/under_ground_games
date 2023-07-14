#include <jansson.h>
#include "../../include/common/JsonData.hpp"

JsonData::JsonData(/* args */)
{
}

JsonData::~JsonData()
{
}

/**
 * status_typeをファイル名に変更し返却
*/
const char *JsonData::changeStatusTypeToFileName(const char *status_type)
{
  // status_typeをファイル名に変更
  if (strcmp(status_type, "StatusData") == 0)
  {
    return "data/StatusData.json";
  }
  else if (strcmp(status_type, "ConfigData") == 0)
  {
    return "data/ConfigData.json";
  }
  else
  {
    fprintf(stderr, "program error: in changeStatusTypeToFileName: status_typeが不正\n");
    exit(1);
  }
}

// JSONファイルを読み込み、その中身を返す
const char *JsonData::getJsonData(const char *status_type, const char *object_name)
{
  // statu_typeをファイル名に変更
  const char *file_name = changeStatusTypeToFileName(status_type);

  // JSONオブジェクトを入れる変数
  json_error_t jerror;
  json_t *root;

  FILE *file = fopen(file_name, "r");
  if (!file)
  {
    fprintf(stderr, "error: in getJsonData: ファイル読み込み失敗\n");
    exit(1);
  }

  root = json_loadf(file, 0, &jerror);
  if (!root)
  {
    fprintf(stderr, "error: in getJsonData: JSONパースエラー: 行 %d: %s\n", jerror.line, jerror.text);
    fclose(file);
    exit(1);
  }

  // object_name配列を取得
  json_t *object_data = json_object_get(root, object_name);
  if (!json_is_array(object_data))
  {
    fprintf(stderr, "error: in getJsonData: JSONパースエラー: %sが配列ではないもしくは見つかりません\n", object_name);
    fclose(file);
    exit(1);
  }

  fclose(file);

  return json_dumps(object_data, JSON_INDENT(2));
}