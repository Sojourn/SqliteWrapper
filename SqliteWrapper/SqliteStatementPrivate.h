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
		
		virtual bool Step(Row **row) = 0;
		virtual bool Reset() = 0;
		virtual bool ClearBindings() = 0;

	private:
		RowPrivate _row;
		sqlite3_stmt *_statement;
		std::shared_ptr<ConnectionPrivate> _connection;
	};
}

#endif // SQLITE_STATEMENT_PRIVATE_H