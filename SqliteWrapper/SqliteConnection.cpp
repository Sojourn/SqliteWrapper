#include "SqliteConnection.h"
#include "SqliteConnectionPrivate.h"
#include "SqliteStatement.h"
#include "SqliteStatementPrivate.h"
#include "SqliteRow.h"
#include "sqlite3.h"

static_assert(sqlite::Connection::OpenFlags_t::OPEN_READONLY == SQLITE_OPEN_READONLY, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_READWRITE == SQLITE_OPEN_READWRITE, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_CREATE == SQLITE_OPEN_CREATE, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_DELETEONCLOSE == SQLITE_OPEN_DELETEONCLOSE, "Invalid flag value");

static_assert(sqlite::Connection::OpenFlags_t::OPEN_EXCLUSIVE == SQLITE_OPEN_EXCLUSIVE, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_AUTOPROXY == SQLITE_OPEN_AUTOPROXY, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_URI == SQLITE_OPEN_URI, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_MEMORY == SQLITE_OPEN_MEMORY, "Invalid flag value");

static_assert(sqlite::Connection::OpenFlags_t::OPEN_MAIN_DB == SQLITE_OPEN_MAIN_DB, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_TEMP_DB == SQLITE_OPEN_TEMP_DB, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_TRANSIENT_DB == SQLITE_OPEN_TRANSIENT_DB, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_MAIN_JOURNAL == SQLITE_OPEN_MAIN_JOURNAL, "Invalid flag value");

static_assert(sqlite::Connection::OpenFlags_t::OPEN_TEMP_JOURNAL == SQLITE_OPEN_TEMP_JOURNAL, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_SUBJOURNAL == SQLITE_OPEN_SUBJOURNAL, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_MASTER_JOURNAL == SQLITE_OPEN_MASTER_JOURNAL, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_NOMUTEX == SQLITE_OPEN_NOMUTEX, "Invalid flag value");

static_assert(sqlite::Connection::OpenFlags_t::OPEN_FULLMUTEX == SQLITE_OPEN_FULLMUTEX, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_SHAREDCACHE == SQLITE_OPEN_SHAREDCACHE, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_PRIVATECACHE == SQLITE_OPEN_PRIVATECACHE, "Invalid flag value");
static_assert(sqlite::Connection::OpenFlags_t::OPEN_WAL == SQLITE_OPEN_WAL, "Invalid flag value");

std::shared_ptr<sqlite::Connection> sqlite::Connection::Create(const std::string &filename, const OpenFlags_t flags)
{
	auto connection = std::make_shared<ConnectionPrivate>();
	return connection->Init(filename, flags) ? connection : nullptr;
}

sqlite::Connection::Connection() {}
sqlite::ConnectionPrivate::ConnectionPrivate() :
	_database(nullptr)
{
}

bool sqlite::ConnectionPrivate::Init(const std::string &filename, const OpenFlags_t flags)
{
	int ret = sqlite3_open_v2(filename.c_str(), &_database, flags, nullptr);
	return ret == SQLITE_OK;
}

sqlite::Connection::~Connection() {}
sqlite::ConnectionPrivate::~ConnectionPrivate()
{
	if(_database != nullptr)
		sqlite3_close(_database);
	_database = nullptr;
}

bool sqlite::ConnectionPrivate::Exec(const std::string &sql)
{
	int ret = sqlite3_exec(_database, sql.c_str(), nullptr, nullptr, nullptr);
	return ret == SQLITE_OK;
}

static int ExecCallback(void *closure, int argc, char **argv, char **colv)
{
	auto callback = reinterpret_cast<std::function<bool (int,char**,char**)> *>(closure);
	return (*callback)(argc, argv, colv) ? SQLITE_OK : SQLITE_ABORT;
}

bool sqlite::ConnectionPrivate::Exec(const std::string &sql, std::function<bool (int,char**,char**)> callback)
{
	int ret = sqlite3_exec(_database, sql.c_str(), ExecCallback, &callback, nullptr);
	return ret == SQLITE_OK;
}

std::unique_ptr<sqlite::Statement> sqlite::ConnectionPrivate::Prepare(const std::string &sql)
{
	auto statement = std::unique_ptr<sqlite::StatementPrivate>(new sqlite::StatementPrivate);
	if(statement->Init(shared_from_this(), sql))
		return std::move(statement);
	else
		return nullptr;
}

sqlite::ConnectionPrivate::operator sqlite3*()
{
	return _database;
}