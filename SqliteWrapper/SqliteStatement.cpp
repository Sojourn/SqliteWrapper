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

	if(row != nullptr)
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

bool sqlite::StatementPrivate::BindParameterName(const size_t index, std::string *name) const
{
	const char *tmp = sqlite3_bind_parameter_name(_statement, index);
	*name = tmp ? tmp : "";
	return tmp != nullptr;
}

bool sqlite::StatementPrivate::BindParameterIndex(const std::string &name, size_t *index) const
{
	*index = sqlite3_bind_parameter_index(_statement, name.c_str());
	return *index != 0;
}

size_t sqlite::StatementPrivate::BindParameterCount() const
{
	return sqlite3_bind_parameter_count(_statement);
}

bool sqlite::StatementPrivate::BindNull(const size_t index, const nullptr_t &)
{
	int ret = sqlite3_bind_null(_statement, index);
	return ret == SQLITE_OK;
}

bool sqlite::StatementPrivate::BindInteger(const size_t index, const int64_t &value)
{
	int ret = sqlite3_bind_int64(_statement, index, value);
	return ret == SQLITE_OK;
}

bool sqlite::StatementPrivate::BindFloat(const size_t index, const double &value)
{
	int ret = sqlite3_bind_double(_statement, index, value);
	return ret == SQLITE_OK;
}

bool sqlite::StatementPrivate::BindText(const size_t index, const std::string &value)
{
	int ret = sqlite3_bind_text(
		_statement, index, value.c_str(), -1, SQLITE_TRANSIENT);
	return ret == SQLITE_OK;
}

bool sqlite::StatementPrivate::BindBlob(const size_t index, const std::vector<uint8_t> &value)
{
	const void *blob = (value.size() > 0) ?
		reinterpret_cast<const void*>(&value[0]) : nullptr;

	int ret = sqlite3_bind_blob(_statement, index, blob, value.size(), SQLITE_TRANSIENT);
	return ret == SQLITE_OK;
}