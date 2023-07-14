class JsonData
{
private:
  /* data */
  const char *changeStatusTypeToFileName(const char *status_type);
public:
  JsonData(/* args */);
  ~JsonData();
  const char *getJsonData(const char *status_type, const char *object_name);
};