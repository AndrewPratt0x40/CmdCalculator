#include "DivisionByZeroException.h"


CmdCalculator::DivisionByZeroException::DivisionByZeroException(std::string_view dividend) :
	m_dividend{ dividend }
{}


// TODO: Use dividend in error message.
const char* CmdCalculator::DivisionByZeroException::what() const noexcept
{
	return "Attempted to divide by zero.";
}


std::string_view CmdCalculator::DivisionByZeroException::getDividend() const noexcept
{
	return m_dividend;
}