#include <vector>
#include <algorithm>
#include "../../include/common/StatusData.hpp"

/**
 * ステータスデータを追加する
 * @param status_code ステータスコード
 * @param message メッセージ
 * @return なし
 */
void addStatusData(int status_code, char *message)
{
  StatusData status_data;
  status_data.status_code = status_code;
  status_data.message = message;
  status_data_list.push_back(status_data);
}

/**
 * エラーステータスがstatus_data_listに存在するかどうかを返す
 * エラーステータスはマイナスの値をとる
 */
bool hasErrorStatus()
{
  for (auto status_data : status_data_list)
  {
    if (status_data.status_code < 0)
    {
      return true;
    }
  }
  return false;
}