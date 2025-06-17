#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "main_menu.h"
#include "settings.h"
#include "type_function.h"
#include "type_function_sentence.h"
#include "time_attack.h"



int main()
{
    for(;;)
    {
        int terminalRows, terminalCols;
        srand(time(NULL));

        initscr();
        cbreak();
        noecho();

        getmaxyx(stdscr, terminalRows, terminalCols);
        WINDOW *win = newwin(terminalRows, terminalCols, 0, 0);
        refresh();

        box(win, 0, 0);

        switch (menu(win))
        {
            case 0:
                kbPractice(1, 1);
                break;

            case 1:
                kbPractice_sentence();
                break;

            case 2:
                timeAttack();
                break;

            case 3:
                settings();
                break;

            case 4:
                exit(0);
                break;
        }

        endwin();
    }
    return 0;
}
