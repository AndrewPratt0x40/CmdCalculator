#pragma once

#include "InvalidInputExpressionException.h"

namespace CmdCalculator
{
	/// \brief An exception that is thrown when an input expression is empty.
	class EmptyInputExpressionException : public InvalidInputExpressionException
	{
	public:
		virtual ~EmptyInputExpressionException() = default;



		const char* what() const noexcept override;
	};
}