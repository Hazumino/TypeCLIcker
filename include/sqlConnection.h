#ifndef SQLCONNH
#define SQLCONNH

#typedef int Bool;

// Function used to obtain a number of random words
char* getList (sqlite3 *db, int numOfItems, int mode, Bool random);

// Function used to insert json into the database of words
void insertJson(sqlite3 *db);

void openDbConn();

void closeDbConn(sqlite3 *db);


#endif /* ifndef  */
