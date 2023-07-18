/**
 * @file StatusData.hpp
 * @brief ステータスデータを管理するクラス
 * @details status_codeとmessageを管理する
 */

#include <vector>

class StatusData
{
private:
  /**
   * ステータスデータの構造体
   */
  struct StatusData
  {
    int status_code;
    char *message;
  };

  /**
   * ステータスデータを格納する配列
   */
  std::vector<StatusData> status_data_list;

public:
  StatusData(/* args */);
  ~StatusData();
  void addStatusData(const char *status_code, const char *message);
  bool hasErrorStatus();
};
