#include <ncurses.h>
#include "../../include/common/CommonProcess.hpp"

CommonProcess::CommonProcess(/* args */)
{
}

CommonProcess::~CommonProcess()
{
}

void CommonProcess::endProcess()
{
  // printStatusProcess();
  endwin();
}