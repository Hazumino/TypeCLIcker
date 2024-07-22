// WARNING: Unfinished

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "../include/sqlConnection.h"

#define MAX_NAME_LENGTH 256 


char** getList (int numOfItems, int mode, _Bool random)
{
  sqlite3 *db;
  char sql[256]; // SQL query string
  int openDB = sqlite3_open("example.db", &db);
  char *instructions;
  char ** names;
    int num_rows = 0;   // Number of rows (names) retrieved
  sqlite3_stmt *stmt;
    int rc;

  if (openDB)
  {
    printf("Error opening db \n %s", sqlite3_errmsg(db));
  }

  switch (mode)
  {
  case (1):
    snprintf(sql, sizeof(sql), "SELECT word FROM words WHERE language = \"english\" ORDER BY RANDOM() LIMIT %d;", numOfItems);
    break;

  case 2:
    snprintf(sql, sizeof(sql), "SELECT word FROM words WHERE language = \"english\" ORDER BY RANDOM() LIMIT %d;", numOfItems);
    break;

  default:
    exit(1);
  }

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char *name = sqlite3_column_text(stmt, 0);
        // Allocate memory for the new name and store it
        names = realloc(names, sizeof(char *) * (num_rows + 1));
        if (names == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return SQLITE_NOMEM;
        }
        names[num_rows] = malloc(MAX_NAME_LENGTH);
        if (names[num_rows] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return SQLITE_NOMEM;
        }
        strncpy(names[num_rows], (const char *)name, MAX_NAME_LENGTH - 1);
        names[num_rows][MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination
        num_rows++;
    }

  return names;

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

