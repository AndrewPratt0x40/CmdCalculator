#pragma once

#include <exception>

namespace CmdCalculator
{
	/// \brief An exception to be thrown when non-implemented code is invoked.
	class NotImplementedException : public std::exception
	{
	public:
		const char* what() const noexcept override
		{
			return "Code that has not been implemented has been invoked";
		}
	};
}