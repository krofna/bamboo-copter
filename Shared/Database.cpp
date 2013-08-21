#include "Shared/Database.hpp"
#include "Shared/Utils.hpp"
#include <fstream>
#include <cstdarg>
#include <sstream>
#include <algorithm>
#include <cctype>

Database sDatabase;

Database::Database() : Driver(nullptr)
{
}

Database::~Database()
{
}

void Database::Connect()
{
    std::ifstream CfgFile("WorldServerConfig.conf");

    if(!CfgFile)
        throw std::runtime_error("Cannot open WorldServerConfig.conf");

    std::string Data[4], Buffer;
    int i = 0;

    while(std::getline(CfgFile, Buffer))
    {
        Buffer.erase(Buffer.begin(), find_if(Buffer.begin(), Buffer.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));

        if(Buffer.empty())
            continue;

        if(!std::isalnum(Buffer[0]))
            continue;

        std::stringstream(Buffer) >> Data[i];
        ++i;
    }

    Driver = get_driver_instance();
    Connection.reset(Driver->connect(Data[0], Data[1], Data[2]));
    Connection->setSchema(Data[3]);
    Statement.reset(Connection->createStatement());
}

void Database::Execute(const char* sql)
{
    Statement->execute(sql);
}

QueryResult Database::Query(const char* sql)
{
    PStatement.reset(Connection->prepareStatement(sql));
    return QueryResult(PStatement->executeQuery());
}

#ifdef _MSC_VER
void Database::PExecute(std::string const& toFormat, ...)
{
	const char* c_str = toFormat.c_str();

	va_list ap;
	va_start(ap, c_str);

	char* sql = Format(c_str, &ap);

	Execute(sql);

	delete[] sql;
}

QueryResult Database::PQuery(std::string const& toFormat, ...)
{
	const char* c_str = toFormat.c_str();

	va_list ap;
	va_start(ap, c_str);

	char* bufSQL = Format(c_str, &ap);
	QueryResult q = Query(bufSQL);
	delete[] bufSQL;

	return q;
}

#endif