#ifndef SQLITE_CONNECTION_PRIVATE_H
#define SQLITE_CONNECTION_PRIVATE_H

#include "sqlite3.h"
#include "SqliteCommon.h"
#include "SqliteConnection.h"

namespace sqlite
{
	class ConnectionPrivate : public Connection
	{
	public:
		ConnectionPrivate();
		bool Init(const std::string &filename, const OpenFlags_t flags);
		virtual ~ConnectionPrivate();

		virtual bool Exec(const std::string &sql) override;
		virtual bool Exec(const std::string &sql, std::function<bool (int,char**,char**)> callback) override;
		virtual std::unique_ptr<Statement> Prepare(const std::string &sql) override;

		operator sqlite3*();

	private:
		sqlite3 *_database;
	};
}

#endif // SQLITE_CONNECTION_PRIVATE_H