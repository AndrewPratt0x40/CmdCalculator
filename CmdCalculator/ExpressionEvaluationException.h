#pragma once

#include <exception>

namespace CmdCalculator
{
	/// \brief An exception that is thrown when the evaluation of an expression fails.
	class ExpressionEvaluationException : public std::exception
	{
	public:
		virtual ~ExpressionEvaluationException()
		{}
	};
}