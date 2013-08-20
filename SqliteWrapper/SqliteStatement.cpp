#include "SqliteStatement.h"
#include "SqliteStatementPrivate.h"

sqlite::Statement::Statement() {}
sqlite::StatementPrivate::StatementPrivate() :
	_connection(nullptr),
	_statement(nullptr)
{
}

bool sqlite::StatementPrivate::Init(std::shared_ptr<ConnectionPrivate> connection, const std::string &sql)
{
	return false;
}

sqlite::Statement::~Statement() {}
sqlite::StatementPrivate::~StatementPrivate()
{
	sqlite3_finalize(_statement);
	_statement = nullptr;
}

bool sqlite::StatementPrivate::Step(Row **row)
{
	return false;
}

bool sqlite::StatementPrivate::Reset()
{
	return false;
}

bool sqlite::StatementPrivate::ClearBindings()
{
	return false;
}