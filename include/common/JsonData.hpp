#include <vector>
#include <string>

class JsonData
{
private:
  /* data */
  const char *changeDataTypeToFileName(const char *status_type);

public:
  JsonData(/* args */);
  ~JsonData();
  const char *getStrFromJsonData(const char *data_type, const std::vector<std::string> &objects);
  struct question_data getRandomQuestionData(const char *data_type);
  std::vector<struct score_data> getScoreData(const char *data_type);
};

struct question_data
{
  std::string id;
  std::string output;
  std::string question;
};

struct score_data
{
  int id;
  std::string name;
  int score;
};