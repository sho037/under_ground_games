#include <stdio.h>
#include "../include/CheckScreenSize.h"
#include "../include/EndProcess.h"

void printStatus(int status_code)
{
  if (status_code == 0)
  {
    printf("Success.\n");
  }
  else
  {
    printf("Failed.\n");
  }
}

int main(int argc, char const *argv[])
{
  /* code */
  int status_code;
  status_code = checkScreenSize();
  if (status_code != 0)
  {
    printStatus(status_code);
  }
  endProcess();
  return 0;
}
