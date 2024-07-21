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

  char *wordList = "CREATE TABLE IF NOT EXISTS words (word TEXT, language TEXT);";
  char *sentenceList = "CREATE TABLE IF NOT EXISTS sentence (sentence TEXT, length INT, language TEXT);";

  openDB = sqlite3_exec(db, wordList, callback, 0,0);

  char** words = getWordList();
  
  for (int i = 0; i < 100; i++)
  {
    char insert_sql[256];
    sprintf(insert_sql, "INSERT INTO words (word, language) VALUES ('%s', '%s');", words[i], "english");
    openDB = sqlite3_exec(db, insert_sql, callback, 0, 0);
  }

  return 1;

}

char** getWordList()
{
  const char* wordList[] = {
    "apple", "banana", "cherry", "date", "grape",
    "lemon", "lime", "orange", "pear", "strawberry",
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
  return wordList;
}
