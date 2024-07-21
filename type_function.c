#include"type_function.h"

#define WORDXLINE 10

// Keyboard practice functions

void kbPractice()
{

  int random, count, row, col;
  int y ;
  int x ;
  int wordLength = strlen(wordList);     
  int groupCount;
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

  char wordList[] = "apple" ;
  char** word = groupWords(wordList, WORDXLINE, &groupCount);
  char currChar;

  // Clear previous screen
  clear();


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


  // Store Clock Values
  clock_t begin = time(NULL);

  for(;;)
  {
    mvwprintw(stdscr,5,10,"Word Count: ");
    mvwprintw(stdscr,5,22, "%.0f", wordCount);
    mvwprintw(stdscr,5,27,"Accuracy: ");
    for (int i = 0; i < groupCount; i++) 
    {
        mvwprintw(stdscr,y/4+i,10,word[i]);
    }


    while (!wordFinished)
    {
      mvwprintw(stdscr,5,37,"%.2f", (charcount/errors)*100);
      currChar = word[lineNum][charIndex];
      char inputChar = getch();
      if (inputChar == currChar)
      {
        errors++;
        charcount++;
        mvaddch(y/4+yPos,10+xPos,currChar | COLOR_PAIR(1));
        charIndex++;
        currChar = word[lineNum][charIndex];
        xPos++;
        mvaddch(y/4+yPos,10+xPos,currChar | COLOR_PAIR(4));
        if (inputChar == ' ')
          {
            wordCount++;
            mvwprintw(stdscr,5,22, "%.0f", wordCount);
          }
        if (currChar == '\0' && lineNum == groupCount+1)
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
          exit(0);
        }
        if (currChar == '\0' && lineNum != groupCount+1)
        {
          lineNum++;
          charcount++;
          charIndex = 0;
          currChar = word[lineNum][charIndex];
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

char* concatenateWord(char )

// Function to concatenate n words into a single string
char* concatenateWords(char **words, int start, int count) {
    int length = 0;
    for (int i = 0; i < count; i++) {
        length += strlen(words[start + i]) + 1; // +1 for space or null terminator
    }

    char *result = (char *)malloc(length * sizeof(char));
    if (!result) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    result[0] = '\0'; // Initialize the result string

    for (int i = 0; i < count; i++) {
        strcat(result, words[start + i]);
        if (i < count-1) {
            strcat(result, " ");
        }
        else{ 
            strcat(result, "\n");
        }
    }

    return result;
}

// Function to split input string into words and group them into strings of n words
char** groupWords(const char *input, int n, int *groupCount) {
    // First, split the input string into words
    char **words = NULL;
    int wordCount = 0;

    const char *ptr = input;
    const char *start;
    int wordLength;

    while (*ptr != '\0') {
        // Skip leading spaces
        while (*ptr == ' ') {
            ptr++;
        }
        if (*ptr == '\0') break;

        // Find the end of the current word
        start = ptr;
        while (*ptr != ' ' && *ptr != '\0') {
            ptr++;
        }
        wordLength = ptr - start;

        // Allocate memory for the word and copy it
        words = (char **)realloc(words, (wordCount + 1) * sizeof(char *));
        words[wordCount] = (char *)malloc((wordLength + 1) * sizeof(char));
        strncpy(words[wordCount], start, wordLength);
        words[wordCount][wordLength] = '\0'; // Null-terminate the word

        wordCount++;
    }

    // Calculate the number of groups needed
    *groupCount = (wordCount + n - 1) / n; // Ceiling of wordCount / n

    // Allocate memory for the groups of words
    char **groups = (char **)malloc(*groupCount * sizeof(char *));
    if (!groups) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Group the words into strings of n words each
    for (int i = 0; i < *groupCount; i++) {
        int count = (i * n + n <= wordCount) ? n : wordCount - i * n;
        groups[i] = concatenateWords(words, i * n, count);
    }

    // Free the words array
    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }
    free(words);

    return groups;
}

void freeWords(char ***groups, int groupCount, int n) {
    for (int i = 0; i < groupCount; i++) {
        for (int j = 0; j < n && groups[i][j] != NULL; j++) {
            free(groups[i][j]);
        }
        free(groups[i]);
    }
    free(groups);
}
