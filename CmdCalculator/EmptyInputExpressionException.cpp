#include "EmptyInputExpressionException.h"


const char* CmdCalculator::EmptyInputExpressionException::what() const noexcept
{
	return "Cannot calculate an empty input expression.";
}