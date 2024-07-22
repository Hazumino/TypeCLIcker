#include <stdio.h>
#include <sqlite3.h>

char** getWordList();

// Callback function for SQLite INSERT operation
int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int main()
{
  sqlite3 *db;

  int openDB = sqlite3_open("example.db", &db);
  if (openDB)
  {
    printf("Error opening db \n %s", sqlite3_errmsg(db));
  }


    char *wordCommnad = "CREATE TABLE IF NOT EXISTS words (word TEXT, language TEXT);";
    openDB = sqlite3_exec(db, wordCommnad, callback, 0,0);

    char *sentenceCommand = "CREATE TABLE IF NOT EXISTS sentence (sentence TEXT, length INT, language TEXT);";
    openDB = sqlite3_exec(db, sentenceCommand, callback, 0,0);

    const char *sentences[] = {
        "The C programming language is powerful and versatile.",
        "Pointers in C can be complex but are essential for dynamic memory management.",
        "Arrays in C are used to store multiple values of the same type.",
        "C supports both local and global variables.",
        "Functions in C help to organize and reuse code.",
        "The 'printf' function is used for output in C.",
        "The 'scanf' function is used for input in C.",
        "C allows for the creation of custom data types using 'struct' and 'union'.",
        "Memory management in C is done using 'malloc', 'calloc', and 'free'.",
        "C supports conditional statements like 'if', 'else if', and 'else'.",
        "Loops in C include 'for', 'while', and 'do-while'.",
        "Switch-case statements are used for multiple branching in C.",
        "C uses the 'main' function as the entry point for program execution.",
        "Header files in C contain declarations of functions and macros.",
        "C uses pointers to reference memory locations directly.",
        "The 'typedef' keyword in C is used to create alias names for existing data types.",
        "File operations in C are performed using 'fopen', 'fclose', 'fread', and 'fwrite'.",
        "Command-line arguments are accessed in C using 'argc' and 'argv'.",
        "The 'sizeof' operator in C is used to determine the size of a data type or variable.",
        "Preprocessor directives in C start with the '#' symbol.",
        "Macros in C are defined using the '#define' directive.",
        "C supports bitwise operators for manipulating individual bits.",
        "Comments in C can be single-line or multi-line.",
        "The 'enum' keyword in C is used to define enumerated types.",
        "Dynamic memory allocation allows for flexible memory usage in C programs.",
        "C uses the 'const' keyword to define constant variables.",
        "Recursive functions in C call themselves within their definition.",
        "The 'static' keyword in C gives variables internal linkage or persistent storage duration.",
        "C supports both signed and unsigned integers.",
        "The 'volatile' keyword in C tells the compiler not to optimize the variable.",
        "Arrays in C are zero-indexed, meaning the first element is at index 0.",
        "Pointers and arrays in C are closely related and often used together.",
        "C supports multi-dimensional arrays for more complex data structures.",
        "The 'goto' statement in C allows for unconditional jumps in code.",
        "Function pointers in C can store addresses of functions.",
        "C has a rich set of standard library functions for various tasks.",
        "The 'exit' function in C terminates program execution.",
        "C programs can be compiled using various compilers like GCC, Clang, and MSVC.",
        "C supports integer, floating-point, and character data types.",
        "String manipulation in C is done using functions like 'strcpy', 'strlen', and 'strcmp'.",
        "Memory leaks in C can be prevented by properly freeing allocated memory.",
        "The 'assert' macro in C is used for debugging purposes.",
        "Function overloading is not supported in C, unlike C++.",
        "The 'register' keyword in C hints to the compiler to use CPU registers for a variable.",
        "C does not have built-in support for object-oriented programming.",
        "The 'restrict' keyword in C is used to indicate that a pointer is the only reference to the object it points to.",
        "In C, integer division truncates the decimal part.",
        "Type casting in C allows for conversion between different data types.",
        "Buffer overflows in C can lead to security vulnerabilities.",
        "The 'time' library in C provides functions for handling date and time."
    };

   char* wordList[] = { "apple", "banana", "cherry", "date", "grape", "lemon", "lime", "orange", "pear", "strawberry",
    "blueberry", "blackberry", "raspberry", "kiwi", "pineapple",
    "watermelon", "melon", "peach", "apricot", "plum",
    "mango", "pomegranate", "fig", "coconut", "avocado",
    "potato", "carrot", "broccoli", "lettuce", "spinach",
    "cucumber", "pepper", "onion", "garlic", "tomato",
    "eggplant", "zucchini", "squash", "pea", "bean",
    "corn", "rice", "wheat", "oat", "barley",
    "milk", "cheese", "yogurt", "butter", "cream",
    "chicken", "beef", "pork", "lamb", "fish",
    "shrimp", "lobster", "crab", "clam", "oyster",
    "bread", "cake", "cookie", "pie", "pasta",
    "rice", "soup", "salad", "sandwich", "pizza",
    "coffee", "tea", "juice", "soda", "water",
    "wine", "beer", "whiskey", "vodka", "rum",
    "book", "pen", "paper", "computer", "phone",
    "table", "chair", "bed", "couch", "lamp",
    "car", "bike", "bus", "train", "plane",
    "dog", "cat", "bird", "fish", "rabbit",
    "sun", "moon", "star", "cloud", "rain",
    "snow", "wind", "storm", "fire", "earth"
  };
  
  for (int i = 0; i < 100; i++)
  {
    char insert_sql[256];
    sprintf(insert_sql, "INSERT INTO words (word, language) VALUES ('%s', '%s');", wordList[i], "english");
    openDB = sqlite3_exec(db, insert_sql, callback, 0, 0);
  }

  for (int i = 0; i < 50; i++)
  {
    char insert_sql[256];
    sprintf(insert_sql, "INSERT INTO sentence (sentence, language) VALUES ('%s', '%s');", sentences[i], "english");
    openDB = sqlite3_exec(db, insert_sql, callback, 0, 0);
  }

  return 1;

}
