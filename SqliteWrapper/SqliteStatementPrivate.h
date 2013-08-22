#ifndef SQLITE_STATEMENT_PRIVATE_H
#define SQLITE_STATEMENT_PRIVATE_H

#include <string>
#include <memory>

#include "sqlite3.h"
#include "SqliteCommon.h"
#include "SqliteStatement.h"
#include "SqliteConnectionPrivate.h"
#include "SqliteRowPrivate.h"

namespace sqlite
{
	class StatementPrivate : public Statement
	{
	public:
		StatementPrivate();
		bool Init(std::shared_ptr<ConnectionPrivate> connection, const std::string &sql);
		virtual ~StatementPrivate();
		
		virtual bool Step(Row **row) override;
		virtual bool Reset() override;
		virtual bool ClearBindings() override;

		virtual bool BindParameterName(const size_t index, std::string *name) const override;
		virtual bool BindParameterIndex(const std::string &name, size_t *index) const override;
		virtual size_t BindParameterCount() const override;

		virtual bool BindNull(const size_t index, const nullptr_t &value) override;
		virtual bool BindInteger(const size_t index, const int64_t &value) override;
		virtual bool BindFloat(const size_t index, const double &value) override;
		virtual bool BindText(const size_t index, const std::string &value) override;
		virtual bool BindBlob(const size_t index, const std::vector<uint8_t> &value) override;

	private:
		RowPrivate _row;
		sqlite3_stmt *_statement;
		std::shared_ptr<ConnectionPrivate> _connection;
	};
}

#endif // SQLITE_STATEMENT_PRIVATE_H