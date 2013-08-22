#ifndef SQLITE_COMMON_H
#define SQLITE_COMMON_H

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <cstdint>

namespace sqlite
{
	class NoCopy
	{
	public:
		NoCopy() {}

	private:
		NoCopy(const NoCopy &);
		const NoCopy &operator=(const NoCopy &);
	};
}

#endif // SQLITE_COMMON_H