#include "SqliteRow.h"
#include "SqliteRowPrivate.h"
#include "sqlite3.h"

static_assert(sqlite::Row::ValueType_t::INTEGER_TYPE == SQLITE_INTEGER, "Invalid type value");
static_assert(sqlite::Row::ValueType_t::FLOAT_TYPE == SQLITE_FLOAT, "Invalid type value");
static_assert(sqlite::Row::ValueType_t::TEXT_TYPE == SQLITE_TEXT, "Invalid type value");
static_assert(sqlite::Row::ValueType_t::BLOB_TYPE == SQLITE_BLOB, "Invalid type value");
static_assert(sqlite::Row::ValueType_t::NULL_TYPE == SQLITE_NULL, "Invalid type value");

sqlite::Row::Row() {}
sqlite::RowPrivate::RowPrivate() :
	_statement(nullptr)
{
}

bool sqlite::RowPrivate::Init(sqlite3_stmt *statement)
{
	_statement = statement;
	return true;
}

size_t sqlite::RowPrivate::ColumnCount() const
{
	return 0;
}

sqlite::Row::ValueType_t sqlite::RowPrivate::ColumnType(size_t index) const
{
	return NULL_TYPE;
}
		
bool sqlite::RowPrivate::GetNull(const size_t index, nullptr_t *value) const
{
	return false;
}

bool sqlite::RowPrivate::GetInteger(const size_t index, int64_t *value) const
{
	return false;
}

bool sqlite::RowPrivate::GetFloat(const size_t index, double *value) const
{
	return false;
}

bool sqlite::RowPrivate::GetText(const size_t index, std::string *value) const
{
	return false;
}

bool sqlite::RowPrivate::GetBlob(const size_t index, std::vector<uint8_t> *value) const
{
	return false;
}