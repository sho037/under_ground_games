class JsonData
{
private:
  /* data */
  const char *changeDataTypeToFileName(const char *status_type);

public:
  JsonData(/* args */);
  ~JsonData();
  const char *getStrFromJsonData(const char *data_type, const std::vector<std::string> &objects);
};