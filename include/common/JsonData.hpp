class JsonData
{
private:
  /* data */
  const char *changeDataTypeToFileName(const char *status_type);

public:
  JsonData(/* args */);
  ~JsonData();
  const char *getStrFromJsonData(const char *data_type, const std::vector<std::string> &objects);
  struct question_data getRondomQuestionData(const char *data_type);
};

struct question_data
{
  std::string id;
  std::string output;
  std::string question;
};