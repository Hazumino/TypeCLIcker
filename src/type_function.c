#include"../include/type_function.h"
#include "sqlConnection.c"

#define WORDXLINE 10
#define XCENTERING 30
#define TOTWORD 40

// Keyboard practice functions

void kbPractice()
{

  int random, count, row, col;
  int y ;
  int x ;
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

  char **wordList = getList(TOTWORD, 1, 0) ;
  int wordLength = strlen(wordList);     

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

    currChar = word[lineNum][charIndex];
  for(;;)
  {
    mvwprintw(stdscr,5,10,"Word Count: ");
    mvwprintw(stdscr,5,22, "%.0f", wordCount);
    mvwprintw(stdscr,5,27,"Accuracy: ");
    for (int i = 0; i < groupCount; i++) 
    {
        mvwprintw(stdscr,y/4+i,XCENTERING,word[i]);
    }


    while (!wordFinished)
    {
      mvwprintw(stdscr,5,37,"%.2f", (charcount/errors)*100);
      char inputChar = getch();
      if (inputChar == currChar )
      {
        errors++;
        charcount++;
        mvaddch(y/4+yPos,XCENTERING+xPos,currChar | COLOR_PAIR(1));
        charIndex++;
        currChar = word[lineNum][charIndex];
        xPos++;
        mvaddch(y/4+yPos,XCENTERING+xPos,currChar | COLOR_PAIR(4));
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

              // refreshing the window
              wrefresh(win);
              exit(1);
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
        mvaddch(y/4+yPos,XCENTERING+xPos,currChar | COLOR_PAIR(3));
        errors++;
      }
      refresh();
    }
  }
}


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
char** groupWords(const char *words[], int num_words, int words_per_chunk, int *num_chunks) {
    // Calculate the number of chunks needed
    *num_chunks = (num_words + words_per_chunk - 1) / words_per_chunk;

    // Allocate memory for the array of chunk strings
    char **chunks = malloc(*num_chunks * sizeof(char*));
    if (chunks == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *num_chunks; i++) {
        // Allocate memory for each chunk string
        chunks[i] = malloc(1024 * sizeof(char)); // Allocate large enough memory for each chunk
        if (chunks[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        // Initialize the chunk string
        chunks[i][0] = '\0'; // Ensure it's an empty string

        // Concatenate words into the current chunk
        for (int j = 0; j < words_per_chunk && i * words_per_chunk + j < num_words; j++) {
            if (j > 0) {
                strcat(chunks[i], " "); // Add a space between words
            }
            strcat(chunks[i], words[i * words_per_chunk + j]);
        }
        strcat(chunks[i], "\n"); // Add a space between words
    }

    return chunks;
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
