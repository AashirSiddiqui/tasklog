#include "sqlite3.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>

// void remove_leading_spaces(char* string) {
//     int i = 0;
//     int leadingSpace = 1;
//     int spacesToRemove = 0;
//     while (string[i] != '\0') {
//         if (string[i] == ' ' && leadingSpace) {
//             spacesToRemove++;
//         }
//         if (string[i] != ' ') {
//             leadingSpace = 0;
//         }
//         i++;
//     }
//     strlcpy(string, &string[i-spacesToRemove + 1], sizeof(char[i-spacesToRemove]));
// }

int add(sqlite3* db, char* taskName) {
    sqlite3_stmt *addRow;
    sqlite3_prepare_v2(db, "INSERT INTO main ( name ) VALUES ( ? );", 256, &addRow, NULL);
    sqlite3_bind_text(addRow, 1, taskName, -1, SQLITE_STATIC);

    int returnCode = sqlite3_step(addRow);

    sqlite3_finalize(addRow);
    
    return returnCode;
}

int view_all(sqlite3* db) {
    sqlite3_stmt *view;
    sqlite3_prepare_v2(db, "SELECT * from main;", 32, &view, NULL);

    printf(" ID | Name | Details | Date\n");
    int returnCode;
    while ((returnCode = sqlite3_step(view)) == SQLITE_ROW) {
        int id = sqlite3_column_int(view, 0);
        char* name = sqlite3_column_text(view, 1);
        char* details = sqlite3_column_text(view, 2);
        char* date = sqlite3_column_text(view, 3);
        printf(" %d | %s | %s | %s \n", id, name, details, date);
    }
    printf("All tasks listed.\n");

    sqlite3_finalize(view);

    return returnCode;
}

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

    if (argc > 1) {
        char* operation = argv[1];
        if (strcmp(operation, "add") == 0) {
            printf("Add operation\n");
            char longStr[256] = "";
            char* toAdd[256] = {0};
            int nextIndex = 0;
            for (int i = 2; i < argc; i++) {
                if (i > 2) {
                    strlcat(longStr, " ", sizeof(longStr));
                }
                strlcat(longStr, argv[i], sizeof(longStr));
            }
// do chem hw, math hw
            int last = 0;
            char* comma = "_";
            while (*comma != '\0') {
                comma = strchrnul(&longStr[last], ',');
                int size = comma - longStr;
                printf("%d\n", size);
                
                char next[size+1];
                strlcpy(next, &longStr[last], sizeof(next));
                last = last+ size + 1;
                // remove_leading_spaces(next);
                printf("Adding: %s\n", next);
                printf("Add return code: %d\n", add(db, next));
                nextIndex++;
                // printf("Finished while cycle 3: %s, %d.\n", longStr, last);
                // // strlcpy(longStr, &longStr[last], sizeof(longStr));
                // printf("Finished while cycle 2.\n");
                // printf("Finished while cycle 1, %d.\n", *comma);
            }
            // for (int i = 0; i < (argc-2); i++) {
            //     if (compstr(longStr[i], ",") == 0) {
                    
            //     }
            // }
        }
        if (strcmp(operation, "view") == 0) {
            view_all(db);
        }
        if (strcmp(operation, "complete") == 0) {}
    }

    sqlite3_close(db);
    printf("Database closed\n");
    return 0;
}