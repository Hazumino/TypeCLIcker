#include"../include/type_function_sentence.h"

#define TOTSENTENCE 10

// Keyboard practice functions

void kbPractice_sentence()
{

  int random, count, row, col, y, x, groupCount;
  int maxX = 10+x;
  int charIndex = 0;
  int yPos = 0;
  int xPos = 0;
  int lineNum = 0;

  float wordCount = 0;
  float errors = 1;
  float charcount = 1;
  float accuracy = 0;

  bool wordFinished = false;

  char **word = getList(TOTSENTENCE, 2, 0) ;

  char currChar;

  // Clear previous screen
  clear();


  // Seed random number generator
  srand(time(NULL));

  initscr();
  curs_set(0);

  // SIZE SETTINGS
  getmaxyx(stdscr, y,x);
  noecho();
  
  // COLOR SETTINGS
  start_color();
  // Enable transparency
  assume_default_colors(-1, -1);
  //
  // Green Color for text
  init_pair(1, COLOR_GREEN, -1);
  //
  // White text for front of the line of chars
  init_pair(2, COLOR_WHITE, -1);
  //
  // Red text for front of the line of chars
  init_pair(3, COLOR_RED, -1);
  //
  // Red text for front of the line of chars
  init_pair(4, COLOR_BLUE, -1);
  //
  // Blue text for front of the line of chars
  init_pair(5, COLOR_BLUE, 4);
  //
  // Blue text for front of the line of chars
  init_pair(6, COLOR_RED, 1);

  refresh();


  // Store Clock Values
  clock_t begin = time(NULL);

  currChar = word[lineNum][charIndex];

  for(;;)
  {
    mvwprintw(stdscr,5,10,"Word Count: ");
    mvwprintw(stdscr,5,22, "%.0f", wordCount);
    mvwprintw(stdscr,5,27,"Accuracy: ");
    for (int i = 0; i < TOTSENTENCE; i++) 
    {
        mvwprintw(stdscr,y/4+i,XCENTERING,word[i]);
    }
    // TO prettify the screen
    box(stdscr, 0, 0);

    while (!wordFinished)
    {
      mvwprintw(stdscr,5,37,"%.2f", (charcount/errors)*100);
      char inputChar =keyboardChange(1,getch());
      if (inputChar == currChar )
      {
        errors++;
        charcount++;
        mvaddch(y/4+yPos,XCENTERING+xPos,currChar | COLOR_PAIR(1));
        currChar = word[lineNum][++charIndex];
        xPos++;
        if(currChar==' '|| currChar=='\n')
        {
          mvaddch(y/4+yPos,XCENTERING+xPos,' ' | COLOR_PAIR(5));
        }
        else
        {
          mvaddch(y/4+yPos,XCENTERING+xPos,currChar | COLOR_PAIR(4));
        }
        if (currChar == '\0' && lineNum == groupCount-1)
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
              mvwprintw(win, 20, 10,"Press any button to exit!", (charcount/errors)*100);

              // refreshing the window
              wrefresh(win);
          if(getch())
          {
              exit(1);

          }
        }
        else if (currChar == '\0' && lineNum < groupCount-1)
        {
          yPos++;
          xPos = 0;
          charIndex = 0;
          lineNum++;
          currChar = word[lineNum][charIndex];
        }
        if (inputChar == ' ')
          {
            wordCount++;
            mvwprintw(stdscr,5,22, "%.0f", wordCount);
          }
      }
      else
      {
        if(currChar==' '|| currChar=='\n')
        {
        mvaddch(y/4+yPos,XCENTERING+xPos,currChar | COLOR_PAIR(6));
        }
        else
        {
        mvaddch(y/4+yPos,XCENTERING+xPos,currChar | COLOR_PAIR(3));
        }
        errors++;
      }
      refresh();
    }
  }
}
