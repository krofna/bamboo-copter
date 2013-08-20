#ifndef DATABASE_H
#define DATABASE_H

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <boost/format.hpp>
#include <memory>

typedef std::unique_ptr<sql::ResultSet> QueryResult;
typedef std::unique_ptr<sql::Connection> ConnectionPtr;
typedef std::unique_ptr<sql::Statement> StatementPtr;
typedef std::unique_ptr<sql::PreparedStatement> PStatementPtr;

class Database
{
public:
    Database();
    ~Database();

    void Connect();

    QueryResult Query(const char* sql);
    void Execute(const char* sql);

    template<typename... Values>
    void PExecute(std::string const& toFormat, Values... values);

    template<typename... Values>
    QueryResult PQuery(std::string const& toFormat, Values... values);

private:
    sql::Driver* Driver;
    ConnectionPtr Connection;
    StatementPtr Statement;
    PStatementPtr PStatement;
};

inline std::string Format(boost::format& formater)
{
    return formater.str();
}

inline std::string Format(std::string const& ToFormat)
{
    return ToFormat;
}

template<typename T, typename... Values>
inline std::string Format(boost::format& formater, T const& Val, Values... Vals)
{
    return Format(formater % Val, std::forward<Values>(Vals)...);
}

template<typename T, typename... Values>
inline std::string Format(std::string const& ToFormat, T const& Val, Values... Vals)
{
    return Format(boost::format(ToFormat) % Val, std::forward<Values>(Vals)...);
}

template<typename... Values>
void Database::PExecute(std::string const& sql, Values... values)
{
    Execute(Format(sql, values...).c_str());
}

template<typename... Values>
QueryResult Database::PQuery(std::string const& sql, Values... values)
{
    return Query(Format(sql, values...).c_str());
}

extern Database sDatabase;

#endif
