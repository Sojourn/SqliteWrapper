#ifndef SQLITE_STATEMENT_H
#define SQLITE_STATEMENT_H

#include "SqliteCommon.h"

namespace sqlite
{
	class Connection;
	class Row;

	class Statement : public NoCopy
	{
	public:
		virtual ~Statement();
		
		virtual bool Step(Row **row) = 0;
		virtual bool Reset() = 0;
		virtual bool ClearBindings() = 0;

	protected:
		Statement();
	};
}

#endif // SQLITE_STATEMENT_H