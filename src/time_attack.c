#include  "../include/time_attack.h"

#define WORDXLINE 15
#define XCENTERING 0
#define TOTWORD 200

// Keyboard practice functions

void timeAttack()
{

  int random, count, row, col, y, x, groupCount;
  int maxX = 10+x;
  int charIndex = 0;
  int yPos = 3;
  int xPos = 1;
  int lineNum = 0;

  int wordCount = 1;
  float errors = 1;
  float charcount = 1;
  float accuracy = 0;

  bool wordFinished = false;

  char **wordList = getList(TOTWORD, 1, 0) ;

  char** word = groupWords(wordList, TOTWORD, 15, &groupCount);
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
  char inputChar;
  currChar = word[lineNum][charIndex];
  int start_col = (x - longestString(word,groupCount)) / 2.2;
  int corrX;
  int corrY = 1;
  int average;
  _Bool inputMade = 0;
  int difficultyVal[] = {0, 100000, 97000, 94000, 91000, 87000};
  int difficulty = 1;
  _Bool difficultyChange = 1;
  WINDOW *gameWindow = newwin(y/4+groupCount,longestString(word,groupCount)+3 , y/4+2, start_col);
  WINDOW *gameBorder = newwin(y/4+groupCount+2,longestString(word,groupCount)+5 , y/4+2-1, start_col-1);
    box(stdscr, 0, 0);
    scrollok(gameWindow, TRUE);

    box(gameBorder, 0, 0);
    wrefresh(stdscr);
    wrefresh(gameBorder);
  for(;;)
  {
    mvwprintw(stdscr,5,10,"Word Count: ");
    mvwprintw(stdscr,5,22, "%d", wordCount);
    mvwprintw(stdscr,5,27,"Accuracy: ");
    mvwprintw(stdscr,7,10,"Difficulty: %d", difficulty);
    for (int i = 0; i < groupCount; i++) 
    {
        mvwprintw(gameWindow,i+3,1,word[i]);
    }
    corrX = 1;
    // TO prettify the screen
    wrefresh(gameBorder);
    wrefresh(gameWindow);

    while (!wordFinished)
    {
    long corruption = get_current_time_us();
    if (difftime(corruption, corruption_begin) > difficultyVal[difficulty])
    {
      corruption_begin = get_current_time_us();
      if (corrX == longestString(word, groupCount)+2)
      {
        corrY++;
        corrX = 1;
      }
      if (corrX == xPos && corrY == yPos)
      {
            nodelay(stdscr, FALSE); // Non-blocking input
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
      if (wordCount % 10 == 0 && difficultyChange) 
      {
          difficultyChange = 0;
          mvwprintw(stdscr,7,10,"Difficulty: %d", difficulty);
          difficulty++;

      }
      else {
          if (difficulty < 6)
          {
            difficultyChange = 1;
          }
        }
      wattron(gameWindow, COLOR_PAIR(7));
      mvwprintw(gameWindow,corrY,corrX++,"%c", ('a' + rand() % 26));
      wattroff(gameWindow, COLOR_PAIR(7));
    }
      mvwprintw(stdscr,5,37,"%.2f", (charcount/errors)*100);
      inputChar = keyboardChange(1,getch());
      if (inputChar != ERR)
      {
        if (inputChar == currChar )
        {
          errors++;
          charcount++;
          wattron(gameWindow, COLOR_PAIR(1));
          mvwprintw(gameWindow,yPos,xPos,"%c", currChar);
          wattroff(gameWindow, COLOR_PAIR(1));
          currChar = word[lineNum][++charIndex];
          xPos++;
          if(currChar==' '|| currChar=='\n')
          {
            wattron(gameWindow, COLOR_PAIR(5));
            mvwprintw(gameWindow,yPos,xPos,"%c", ' ');
            wattroff(gameWindow, COLOR_PAIR(5));
          }
          else
          {
            wattron(gameWindow,COLOR_PAIR(4));
            mvwprintw(gameWindow,yPos,xPos,"%c", currChar);
            wattroff(gameWindow,COLOR_PAIR(4));
          }
          if (currChar == '\0' && lineNum == groupCount-1)
          {
                wordCount++;

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
            corrY -= 1;
            xPos = 1;
            charIndex = 0;
            lineNum++;
            currChar = word[lineNum][charIndex];
            scroll(gameWindow);
            wattron(gameWindow,COLOR_PAIR(4));
            mvwprintw(gameWindow,yPos,xPos,"%c", currChar);
            wattroff(gameWindow, COLOR_PAIR(4));
            box(gameBorder, 0,0);
          }
          if (inputChar == ' ')
            {
              wordCount++;
              mvwprintw(stdscr,5,22, "%d", wordCount);
            }
        }
        else
        {
          if(currChar==' '|| currChar=='\n')
          {
            wattron(gameWindow,COLOR_PAIR(6));
            mvwprintw(gameWindow,yPos,xPos,"%c", currChar);
            wattroff(gameWindow, COLOR_PAIR(6));

          }
          else
          {
            wattron(gameWindow,COLOR_PAIR(3));
            mvwprintw(gameWindow,yPos,xPos,"%c", currChar);
            wattroff(gameWindow, COLOR_PAIR(3));
          }
          errors++;
        }
        inputChar = ERR;
      }

    refresh();
    wrefresh(gameBorder);
    wrefresh(gameWindow);
    }
  }
}

// Function to get the current time in microseconds
long get_current_time_us() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}

int longestString(char **words, int max_string)
{
  int largest = 0;
  for (int i = 0; i < max_string; i++)
  {
    if (largest < strlen(words[i]))
    {
      largest = strlen(words[i]);
    }
  }
  return largest;
}
