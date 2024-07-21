// WARNING: Unfinished

#include <stdio.h>
#include <sqlite3.h>
#include "sqlConnection.h"

char* getList (sqlite3 *db, int numOfItems, int mode, Bool random)
{
  int openDB = sqlite3_open("example.db", &db);

  if (openDB)
  {
    printf("Error opening db \n %s", sqlite3_errmsg(db));
  }

  switch(mode)
  {
  case 1:
    char *instructions = "SELECT * FROM words ORDER BY RANDOM() LIMIT %d;", ;
    break;

  case 2:
    char *instructions = "SELECT * FROM sentences ORDER BY RANDOM() LIMIT %d;";
    break;

  default:
    exit(1);
  }

  openDB = sqlite3_exec(db, instructions, callback, 0,0);

  return 1;

}

void openDbConn()
{
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  rc = sqlite3_open("test.db", &db);
}

void closeDbConn(sqlite3 *db)
{
  sqlite3_close(db);
}
