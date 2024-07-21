#ifndef SQLCONNH
#define SQLCONNH

// Function used to obtain a number of random words
char** getList (sqlite3 *db, int numOfItems, int mode, _Bool random);

// Function used to insert json into the database of words
void insertJson(sqlite3 *db);

void openDbConn();

void closeDbConn(sqlite3 *db);

int callback(void *NotUsed, int argc, char **argv, char **azColName);


#endif /* ifndef  */
