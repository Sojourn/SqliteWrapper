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

		virtual bool BindParameterName(const size_t index, std::string *name) const = 0;
		virtual bool BindParameterIndex(const std::string &name, size_t *index) const = 0;
		virtual size_t BindParameterCount() const = 0;

		virtual bool BindNull(const size_t index, const nullptr_t &value) = 0;
		virtual bool BindInteger(const size_t index, const int64_t &value) = 0;
		virtual bool BindFloat(const size_t index, const double &value) = 0;
		virtual bool BindText(const size_t index, const std::string &value) = 0;
		virtual bool BindBlob(const size_t index, const std::vector<uint8_t> &value) = 0;

	protected:
		Statement();
	};
}

#endif // SQLITE_STATEMENT_H