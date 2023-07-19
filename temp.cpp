#include <ncurses.h>
#include <locale.h>
#include <unistd.h>

int main(void)
{
    setlocale(LC_ALL, "");
    initscr();
    addstr("ほげほげ");
    refresh();
    sleep(10);
    endwin();

    return 0;
}
