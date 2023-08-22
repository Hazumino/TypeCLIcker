// TODO: Fix clock accuracy and make it into seconds
// TODO: Make sure that you have the sentences aligned in the center of the screen.
// TODO: Add /n where appropriate to make sure no overflow happens
// TODO: Enter to exit program once finished

// WARNING: Think how to translate the JSON file into an SQLlite 3 DB.
// WARNING: Think on methods to randomly select words from the DB to then add onto a big string.

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

int menu(WINDOW *win)
{
  int pointer;

  char title[40] = "Typing Practice CLI";
  int titleLength = strlen(title);

  // Title screen
  mvwprintw(win, 3, 40-(strlen(title)/2), title );

  pointer = 6;

  mvwprintw(win, pointer, 20, ">" );
  mvwprintw(win, 6, 40-(strlen(title)/2), "Sentence Practice" );
  mvwprintw(win, 8, 40-(strlen(title)/2), "Settings" );
  mvwprintw(win, 10, 40-(strlen(title)/2),"Exit" );
  wrefresh(win);

  while(1)
  {
    char arrow = getch();
    switch(arrow)
    {
      case 27:
        pointer = movePointer(win,pointer,10,6);
        break;
      case 10:
        if (pointer == 6 )
        {
          return 0;
        }
        else if (pointer == 8 )
        {
          return 1;
        }
        else if (pointer == 10 )
        {
          return 2;
        }
    }
  }
}

int movePointer (WINDOW *win, int currPos, int maxVal, int minVal)
{
  if(getch() == 91)
  {
    // Clear Arrow
    mvwprintw(win, currPos, 20, " " );

    int arrow = getch();

    if (arrow == 66)
    {
      if (currPos == maxVal)
      {
        currPos = minVal;
      }
      else 
      {
        currPos++;
        currPos++;
      }
      mvwprintw(win, currPos, 20, ">" );
      wrefresh(win);
    }

    else if (arrow == 65)
    {
      if (currPos == minVal)
      {
        currPos = maxVal;
      }
      else 
      {
        currPos--;
        currPos--;
      }
      mvwprintw(win, currPos, 20, ">" );
      wrefresh(win);
    }
  }
  return currPos;
}

// Keyboard practice functions

void kbPractice()
{
  // Clear previous screen
  clear();

  int random, count, row, col;
  int y ;
  int x ;

  // Seed random number generator
  srand(time(NULL));

  initscr();
  curs_set(0);

  // SIZE SETTINGS
  getmaxyx(stdscr, y,x);
  box(stdscr, 0, 0);
  noecho();
  
  // COLOR SETTINGS
  start_color();
  // Enable transparency
  assume_default_colors(-1, -1);
  // Green Color for text
  init_pair(1, COLOR_GREEN, -1);
  // White text for front of the line of chars
  init_pair(2, COLOR_WHITE, -1);
  // Red text for front of the line of chars
  init_pair(3, COLOR_RED, -1);
  // Red text for front of the line of chars
  init_pair(4, COLOR_BLUE, -1);



  refresh();
  char word[] = "The Legend\nThe Legend" ;
  int wordLength = strlen(word); 
  int maxX = 10+x;

  int charIndex = 0;
  int yPos = 0;
  int xPos = 0;
  bool wordFinished = false;
  char currChar;
  float wordCount = 0;
  float errors = 1;
  float charcount = 1;
  float accuracy = 0;
  clock_t begin = time(NULL);

  while(1)
  {
    mvwprintw(stdscr,5,10,"Word Count: ");
    mvwprintw(stdscr,5,22, "%.0f", wordCount);
    mvwprintw(stdscr,5,27,"Accuracy: ");
    mvwprintw(stdscr,y/4,10,word);

    while (!wordFinished)
    {
      mvwprintw(stdscr,5,37,"%.2f", (charcount/errors)*100);
      currChar = word[charIndex];
      char inputChar = getch();
      if (inputChar == currChar)
      {
        errors++;
        charcount++;
        mvaddch(y/4+yPos,10+xPos,currChar | COLOR_PAIR(1));
        charIndex++;
        currChar = word[charIndex];
        xPos++;
        mvaddch(y/4+yPos,10+xPos,currChar | COLOR_PAIR(4));
        if (inputChar == ' ')
          {
            wordCount++;
            mvwprintw(stdscr,5,22, "%.0f", wordCount);
          }
        if (currChar == '\0')
        {
              wordCount++;
              mvwprintw(stdscr,5,22, "%.0f", wordCount);

              clock_t end = time(NULL);
              WINDOW *win = newwin(y/2, x/2,y/5, x/4);
              refresh();

              // making box border with default border styles
              box(win, 0, 0);

              // move and print in window
              float totTime =  difftime(end,begin);
              mvwprintw(win, 5, 10, "Words Count: %.0f", wordCount);
              mvwprintw(win, 7, 10, "Time: %.2f", totTime);
              mvwprintw(win, 9, 10, "Words per Minute: %.2lf", wordCount/(totTime/60.0));
              mvwprintw(win, 11, 10,"Accuracy: %.2f\%", (charcount/errors)*100);

              // refreshing the window
              wrefresh(win);
        }
        else if (currChar == '\n')
        {
          charcount++;
          currChar = word[charIndex];
          yPos++;
          xPos = 0;
        }
      }
      else
      {
        mvaddch(y/4+yPos,10+xPos,currChar | COLOR_PAIR(3));
        errors++;
      }
      refresh();
    }
  }
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
