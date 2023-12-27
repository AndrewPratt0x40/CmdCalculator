#pragma once

#include <exception>

namespace CmdCalculator
{
	/// \brief An exception that is thrown when command-line arguments are invalid.
	class BadRawCmdLineArgsException : public std::exception
	{};
}