#include "NegativeRadicandException.h"


CmdCalculator::NegativeRadicandException::NegativeRadicandException(std::string&& radicand) :
	m_radicand{ std::move(radicand) }
{}


CmdCalculator::NegativeRadicandException::NegativeRadicandException(std::string_view radicand) :
	m_radicand{ radicand }
{}


// TODO: Use radicand in error message.
const char* CmdCalculator::NegativeRadicandException::what() const noexcept
{
	return "Attempted to evaluate an nth-root operation with a negative radicand.";
}


std::string_view CmdCalculator::NegativeRadicandException::getDividend() const noexcept
{
	return m_radicand;
}