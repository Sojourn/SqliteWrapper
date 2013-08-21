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
	return _statement != nullptr;
}

size_t sqlite::RowPrivate::ColumnCount() const
{
	return sqlite3_column_count(_statement);
}

bool sqlite::RowPrivate::ColumnType(size_t index, ValueType_t *type) const
{
	if(index < ColumnCount())
	{
		*type = static_cast<ValueType_t>(sqlite3_column_type(_statement, index));
		return true;
	}
	else
	{
		*type = ValueType_t::NULL_TYPE;
		return false;
	}
}
		
bool sqlite::RowPrivate::GetNull(const size_t index, nullptr_t *value) const
{
	if(index < ColumnCount())
	{
		*value = nullptr;
		return true;
	}
	else
	{
		*value = nullptr;
		return false;
	}
}

bool sqlite::RowPrivate::GetInteger(const size_t index, int64_t *value) const
{
	if(index < ColumnCount())
	{
		*value = sqlite3_column_int64(_statement, index);
		return true;
	}
	else
	{
		*value = 0;
		return false;
	}
}

bool sqlite::RowPrivate::GetFloat(const size_t index, double *value) const
{
	if(index < ColumnCount())
	{
		*value = sqlite3_column_double(_statement, index);
		return true;
	}
	else
	{
		*value = 0.0;
		return false;
	}
}

bool sqlite::RowPrivate::GetText(const size_t index, std::string *value) const
{
	value->clear();

	if(index < ColumnCount())
	{
		const size_t length = sqlite3_column_bytes(_statement, index);
		if(length == 0)
			return true;

		const char *text = reinterpret_cast<const char*>(
			sqlite3_column_text(_statement, index));

		value->resize(length);
		std::copy(text, text + length, value->begin());
		return true;
	}
	else
	{
		return false;
	}
}

bool sqlite::RowPrivate::GetBlob(const size_t index, std::vector<uint8_t> *value) const
{
	value->clear();
	if(index < ColumnCount())
	{
		const size_t length = sqlite3_column_bytes(_statement, index);
		if(length == 0)
			return true;

		const uint8_t *blob = reinterpret_cast<const uint8_t*>(
			sqlite3_column_blob(_statement, index));

		value->resize(length);
		std::copy(blob, blob + length, value->begin());
		return true;
	}
	else
	{
	}

	return false;
}