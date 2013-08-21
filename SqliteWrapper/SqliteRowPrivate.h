#ifndef SQLITE_ROW_PRIVATE_H
#define SQLITE_ROW_PRIVATE_H

#include "sqlite3.h"
#include "SqliteRow.h"

namespace sqlite
{
	class RowPrivate : public Row
	{
	public:
		RowPrivate();
		bool Init(sqlite3_stmt *statement);

		virtual size_t ColumnCount() const override;
		virtual bool ColumnType(size_t index, ValueType_t *type) const override;
		virtual bool GetNull(const size_t index, nullptr_t *value) const override;
		virtual bool GetInteger(const size_t index, int64_t *value) const override;
		virtual bool GetFloat(const size_t index, double *value) const override;
		virtual bool GetText(const size_t index, std::string *value) const override;
		virtual bool GetBlob(const size_t index, std::vector<uint8_t> *value) const override;

	private:
		sqlite3_stmt *_statement;
	};
}

#endif // SQLITE_ROW_PRIVATE_H