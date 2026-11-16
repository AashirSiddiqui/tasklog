#include "sqlite3.h"
#include <stdio.h>

int main() {
    sqlite3 *db;
    int code = sqlite3_open("main.db", &db);
    printf("Opening database: Return code %d\n", code);
    sqlite3_close(db);
    printf("Database closed\n");
    return 0;
}