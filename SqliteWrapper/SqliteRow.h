#ifndef SQLITE_ROW_H
#define SQLITE_ROW_H

#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>

#include "SqliteCommon.h"

namespace sqlite
{
	class Row : public NoCopy
	{
		friend class StatementPrivate;
	public:
		enum ValueType_t : uint32_t
		{
			INTEGER_TYPE = 1,
			FLOAT_TYPE   = 2,
			TEXT_TYPE    = 3,
			BLOB_TYPE    = 4,
			NULL_TYPE    = 5
		};

		virtual size_t ColumnCount() const = 0;
		virtual ValueType_t ColumnType(size_t index) const = 0;
		
		virtual bool GetNull(const size_t index, nullptr_t *value) const = 0;
		virtual bool GetInteger(const size_t index, int64_t *value) const = 0;
		virtual bool GetFloat(const size_t index, double *value) const = 0;
		virtual bool GetText(const size_t index, std::string *value) const = 0;
		virtual bool GetBlob(const size_t index, std::vector<uint8_t> *value) const = 0;

	protected:
		Row();
	};
}

#endif // SQLITE_ROW_H