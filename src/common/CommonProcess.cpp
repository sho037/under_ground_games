#include <ncurses.h>
#include "../../include/common/CommonProcess.hpp"

CommonProcess::CommonProcess(/* args */)
{
}

CommonProcess::~CommonProcess()
{
}

/**
 * プログラムが終了する際の処理
*/
void CommonProcess::endProcess()
{
  // printStatusProcess();
  endwin();
}