#pragma once

#include <exception>

namespace CmdCalculator
{
	/// \brief An exception that is thrown when an invalid input expression is given.
	class InvalidInputExpressionException : public std::exception
	{};
}