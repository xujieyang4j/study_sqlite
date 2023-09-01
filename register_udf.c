#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// // 自定义函数的回调函数
// void myAddFunction(sqlite3_context *context, int argc, sqlite3_value **argv) {
//     // 在此处实现自定义函数的逻辑
//     // 例如，计算两个整数的和
//     if (argc == 2 && sqlite3_value_type(argv[0]) == SQLITE_INTEGER && sqlite3_value_type(argv[1]) == SQLITE_INTEGER) {
//         int a = sqlite3_value_int(argv[0]);
//         int b = sqlite3_value_int(argv[1]);
//         int result = a + b;
//         sqlite3_result_int(context, result);
//     } else {
//         sqlite3_result_error(context, "Invalid arguments", -1);
//     }
// }

int main(int argc, char const *argv[])
{
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db); // 打开内存数据库
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    char *sql = "SELECT SQLITE_VERSION()";
    sqlite3_stmt *pre_stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &pre_stmt, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return rc;
    }

    rc = sqlite3_step(pre_stmt);
    if (rc == SQLITE_ROW)
    {
        printf("%s\n", sqlite3_column_text(pre_stmt, 0));
    }

    sqlite3_finalize(pre_stmt);
    sqlite3_close(db);

    return 0;
}
