#include "sqlite3.h"
#include <stdio.h>
#include <stddef.h>

int main(int argc, char *argv[]) {
    sqlite3 *db;
    char *unused;
    int returnCode;
    int code = sqlite3_open("main.db", &db);

    printf("Opening database: Return code %d\n\n", code);
    sqlite3_stmt *createTable;
    sqlite3_stmt *tableExists; 
    sqlite3_prepare_v2(db, "SELECT name FROM sqlite_schema WHERE type='table' AND name=?;", 128, &tableExists, &unused);
    sqlite3_bind_text(tableExists, 1, "main", -1, SQLITE_STATIC);

    returnCode = sqlite3_step(tableExists);
    
    if (returnCode == SQLITE_ROW) {
        printf("Table found!\n");
    }
    else if (returnCode == SQLITE_DONE) {
        printf("Table not found. :(\n");
        sqlite3_prepare_v2(db, "create table main ( id INTEGER PRIMARY KEY, name TEXT, details TEXT, date TEXT );", 128, &createTable, &unused);
        returnCode = sqlite3_step(createTable);
        if (returnCode == SQLITE_DONE) {
            printf("Table created!\n");
        }
        sqlite3_finalize(createTable);
    }
    sqlite3_finalize(tableExists);

    printf("\nNumber of arguments: %d\n", argc);

    sqlite3_close(db);
    printf("Database closed\n");
    return 0;
}