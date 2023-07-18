#include <stdio.h>
#include <jansson.h>
#include <ncurses.h>
#include <unistd.h>
#include "../include/PrintStatus.hpp"
#include "../include/UGGames.hpp"
#include "../include/common/CommonProcess.hpp"
#include "../include/common/CheckScreen.hpp"

int status_code;

void printStatusProcess()
{
  if (status_code == 0)
  {
    printf("バイバイ！\n");
  }
  else
  {
    printStatus(status_code);
  }
}

void process()
{
  if (isOkScreenSize() == false)
  {
    status_code = -500;
    return;
  }

  status_code = UGGames();
}

int main(int argc, char const *argv[])
{
  CommonProcess commonProcess;

  initscr();
  process();

  commonProcess.endProcess();

  printStatusProcess();

  return status_code;
}
