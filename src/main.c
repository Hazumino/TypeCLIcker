// TODO: Fix clock accuracy and make it into seconds
// TODO: Make sure that you have the sentences aligned in the center of the screen.
// TODO: Enter to exit program once finished

// WARNING: Think how to translate the JSON file into an SQLlite 3 DB.
// WARNING: Think on methods to randomly select words from the DB to then add onto a big string.


#include "menu.c"
#include "type_function.c"
#include <stdio.h>
#include <ncurses.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


void kbPractice();

// Struct representing one instance of line of code
int main()
{
  int x, y, pointer, terminalRows, terminalCols;
  // Seed random number generator
  srand(time(NULL));

  initscr();
  cbreak();
  noecho();

  getmaxyx(stdscr, terminalRows, terminalCols);
  WINDOW *win = newwin(terminalRows,terminalCols,0,0);
  refresh();

  box(win, 0,0);

  int sentence = 0;
  switch (menu(win))
  {
    case 0:
      //TODO: Add ability to allow user to decide if to work on sentences or on words
      kbPractice();
      break;

    case 1:
      //TODO: Add ability to allow user to decide if to work on sentences or on words
      kbPractice();
      break;

    case 2:
      //TODO: Settings function missing: allow user to select number of words, number of sentences;
      break;

    case 3:
      exit(0);
      break;
  }

  endwin();
  return 1;
}
