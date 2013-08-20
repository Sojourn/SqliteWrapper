#ifndef SQLITE_CONNECTION_H
#define SQLITE_CONNECTION_H

#include <string>
#include <memory>
#include <functional>
#include <cstdint>

#include "SqliteCommon.h"

namespace sqlite
{
	class Row;
	class Statement;

	class Connection : public NoCopy
	{
	public:
		enum OpenFlags_t : uint32_t
		{
			OPEN_READONLY       = (1 << 0),
			OPEN_READWRITE      = (1 << 1),
			OPEN_CREATE         = (1 << 2),
			OPEN_DELETEONCLOSE  = (1 << 3),
			OPEN_EXCLUSIVE      = (1 << 4),
			OPEN_AUTOPROXY      = (1 << 5),
			OPEN_URI            = (1 << 6),
			OPEN_MEMORY         = (1 << 7),
			OPEN_MAIN_DB        = (1 << 8),
			OPEN_TEMP_DB        = (1 << 9),
			OPEN_TRANSIENT_DB   = (1 << 10),
			OPEN_MAIN_JOURNAL   = (1 << 11),
			OPEN_TEMP_JOURNAL   = (1 << 12),
			OPEN_SUBJOURNAL     = (1 << 13),
			OPEN_MASTER_JOURNAL = (1 << 14),
			OPEN_NOMUTEX        = (1 << 15),
			OPEN_FULLMUTEX      = (1 << 16),
			OPEN_SHAREDCACHE    = (1 << 17),
			OPEN_PRIVATECACHE   = (1 << 18),
			OPEN_WAL            = (1 << 19)
		};

		static std::shared_ptr<Connection> Create(const std::string &filename, const OpenFlags_t flags);
		virtual ~Connection();

		virtual bool Exec(const std::string &sql) = 0;
		virtual bool Exec(const std::string &sql, std::function<bool (int,char**,char**)> callback) = 0;
		virtual std::unique_ptr<Statement> Prepare(const std::string &sql) = 0;

	protected:
		Connection();
	};
}

#endif // SQLITE_CONNECTION_H