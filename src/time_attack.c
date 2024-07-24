#include  "../include/time_attack.h"

#define WORDXLINE 15
#define XCENTERING 10
#define TOTWORD 80

// Keyboard practice functions

void timeAttack()
{

  int random, count, row, col, y, x, groupCount;
  int maxX = 10+x;
  int charIndex = 0;
  int yPos = 0;
  int xPos = 0;
  int lineNum = 0;

  int wordCount = 1;
  float errors = 1;
  float charcount = 1;
  float accuracy = 0;

  bool wordFinished = false;

  char **wordList = getList(TOTWORD, 1, 0) ;

  char** word = groupWords(wordList, TOTWORD, WORDXLINE, &groupCount);
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
      nodelay(stdscr, TRUE); // Non-blocking input
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

  init_pair(7, COLOR_MAGENTA, -1);

  refresh();


  // Store Clock Values
  clock_t begin = time(NULL);
  long corruption_begin = get_current_time_us();

  currChar = word[lineNum][charIndex];
  int start_col = (x - strlen(word[0])) / 2;
  int corrX;
  int corrY = y/4-2;
  int average;
  int difficultyVal[] = {100000, 97000, 85000, 80000, 74000};
  int difficulty = 0;

  for(;;)
  {
    mvwprintw(stdscr,5,10,"Word Count: ");
    mvwprintw(stdscr,5,22, "%.0f", wordCount);
    mvwprintw(stdscr,5,27,"Accuracy: ");
    mvwprintw(stdscr,7,10,"Difficulty: %d", difficulty);
    for (int i = 0; i < groupCount; i++) 
    {
        average += strlen(word[i]);
        mvwprintw(stdscr,y/4+i,start_col,word[i]);
    }
    corrX = start_col;
    // TO prettify the screen
    box(stdscr, 0, 0);
    box(stdscr, 0, y/4-3);

    while (!wordFinished)
    {
    if (wordCount % 20 == 0) {
                    difficulty++; // Increase the difficulty every 20 words
                }
    long corruption = get_current_time_us();
    if (difftime(corruption, corruption_begin) > difficultyVal[difficulty])
    {
      corruption_begin = get_current_time_us();
      if (corrX > average/groupCount)
      {
        corrY++;
        corrX = start_col;
      }
        if (corrX ==  start_col+xPos && corrY == y/4+yPos)
        {
          exit(0);
        }
      mvaddch(corrY,corrX++,'a' + rand() % 26 | COLOR_PAIR(7));
      refresh();
    }
      mvwprintw(stdscr,5,37,"%.2f", (charcount/errors)*100);
      char inputChar =keyboardChange(1,getch());
      if (inputChar == currChar )
      {
        errors++;
        charcount++;
        mvaddch(y/4+yPos,start_col+xPos,currChar | COLOR_PAIR(1));
        currChar = word[lineNum][++charIndex];
        xPos++;
        if(currChar==' '|| currChar=='\n')
        {
          mvaddch(y/4+yPos,start_col+xPos,' ' | COLOR_PAIR(5));
        }
        else
        {
          mvaddch(y/4+yPos,start_col+xPos,currChar | COLOR_PAIR(4));
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
          scrl(1);
          mvaddch(y/4+yPos,start_col+xPos,currChar | COLOR_PAIR(4));
        }
        if (inputChar == ' ')
          {
            wordCount++;
            mvwprintw(stdscr,5,22, "%.0f", wordCount);
          }
      }
      refresh();
    }
  }
}

// Function to get the current time in microseconds
long get_current_time_us() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}
