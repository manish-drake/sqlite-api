#ifndef DB_H
#define DB_H
#include <sqlite3.h>
#include <memory>
#include <vector>
#include <string>
#include "datadefinition.h"

using namespace std;

struct sqlite3_deleter
{
    void operator()(sqlite3* db)
    {
        sqlite3_close_v2(db);
    }
};
struct sqlite3_stmt_deleter
{
    void operator()(sqlite3_stmt* stmt)
    {
        sqlite3_finalize(stmt);
    }
};

using sqldb = std::unique_ptr<sqlite3, sqlite3_deleter>;
using sqlstmt = std::unique_ptr<sqlite3_stmt, sqlite3_stmt_deleter>;
using sqlResult = std::vector<std::vector<SqlValue> >;
/**
 * All database related operations are performed in this class only.
*/
class DB
{
  public:
    DB(const char* name);
    static int callback(void *data, int argc, char **argv, char **azColName);
    /**
     * The create function returns a sqlite3 db held in a
     * unique_ptr, ensuring safety from memory leakage.
    */
    sqldb create() const;
    /**
     * This function can be used for executing queries that
     * are not run for any direct data. It can be used for
     * Insert, Update, Delete. It returns if the operation
     * executed successfully.
    */
    int execScalar(const char* sql) const;
    /**
     * The function can be used to find how many rows of
     * data exist for a query or if a record exists in
     * the table at all. It can be helpful for queries
     * where we need to check if table exists.
    */
    int selectCountScalar(const char* sql) const;
    /**
     * The function helps getting one single value from
     * any one column or the first column depending on the query.
    */
    int selectScalar(const char* sql, SqlValue& sqlValue) const;
    /**
     * The function most helpful with select statements.
     * It returns a vector of a vector of a SqlValue
     * (representing one column). The return value returns
     * the number of rows present in the table against the
     * query.
    */
    int select(const char* sql, sqlResult& result) const;
  private:
    const char* m_name;
};

#endif //DB_H