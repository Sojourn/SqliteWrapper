#include "SqliteStatement.h"
#include "SqliteStatementPrivate.h"
#include "sqlite3.h"

sqlite::Statement::Statement() {}
sqlite::StatementPrivate::StatementPrivate() :
	_connection(nullptr),
	_statement(nullptr)
{
}

bool sqlite::StatementPrivate::Init(std::shared_ptr<ConnectionPrivate> connection, const std::string &sql)
{
	int ret = sqlite3_prepare_v2(*connection, sql.c_str(), sql.length(), &_statement, nullptr);
	return (ret == SQLITE_OK) ? _row.Init(_statement) : false;
}

sqlite::Statement::~Statement() {}
sqlite::StatementPrivate::~StatementPrivate()
{
	sqlite3_finalize(_statement);
	_statement = nullptr;
}

bool sqlite::StatementPrivate::Step(Row **row)
{
	int ret = sqlite3_step(_statement);

	*row = (ret == SQLITE_ROW) ? &_row : nullptr;
	return ret == SQLITE_ROW;
}

bool sqlite::StatementPrivate::Reset()
{
	int ret = sqlite3_reset(_statement);
	return ret == SQLITE_OK;
}

bool sqlite::StatementPrivate::ClearBindings()
{
	int ret = sqlite3_clear_bindings(_statement);
	return ret == SQLITE_OK;
}