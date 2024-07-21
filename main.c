// TODO: Fix clock accuracy and make it into seconds
// TODO: Make sure that you have the sentences aligned in the center of the screen.
// TODO: Enter to exit program once finished

// WARNING: Think how to translate the JSON file into an SQLlite 3 DB.
// WARNING: Think on methods to randomly select words from the DB to then add onto a big string.


#include "menu.c"
#include "type_function.c"
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <sqlite3.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


struct User
{
  int wpm;
};

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
      kbPractice();
      break;

    case 1:
      break;

    case 2:
      exit(0);
      break;
  }

  endwin();
  return 1;
}



// DB Functions
void jsonToDb()
{

}


void openDbConn()
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  rc = sqlite3_open("test.db", &db);
}

void closeDbConn(sqlite3 *db)
{
  sqlite3_close(db);
}
