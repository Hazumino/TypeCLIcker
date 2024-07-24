#include "../include/main_menu.h"
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <sqlite3.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int menu(WINDOW *win)
{
  int pointer;

  char title[40] = "Typing Practice CLI";
  int titlelength = strlen(title);

  // title screen
  mvwprintw(win, 3, 40-(strlen(title)/2), title );

  pointer = 6;

  mvwprintw(win, pointer, 20, ">" );
  mvwprintw(win, 6, 40-(strlen(title)/2), "words practice" );
  mvwprintw(win, 8, 40-(strlen(title)/2), "sentence practice" );
  mvwprintw(win, 10, 40-(strlen(title)/2), "time attack" );
  mvwprintw(win, 12, 40-(strlen(title)/2), "settings" );
  mvwprintw(win, 14, 40-(strlen(title)/2),"exit" );
  wrefresh(win);

  while(1)
  {
    char arrow = getch();
    switch(arrow)
    {
      case 27:
        pointer = movepointer(win,pointer,14,6);
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
        else if (pointer == 12 )
        {
          return 3;
        }
        else if (pointer == 14 )
        {
          return 4;
        }
    }
  }
}

int movepointer (WINDOW *win, int currPos, int maxVal, int minVal)
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
