#include "UnexpectedInputExpressionCharException.h"

#include <format>


CmdCalculator::UnexpectedInputExpressionCharException::UnexpectedInputExpressionCharException
(
	const size_t charIndex
) :UnexpectedInputExpressionCharException
(
	charIndex,
	std::ranges::empty_view<std::string>()
)
{}


size_t CmdCalculator::UnexpectedInputExpressionCharException::getCharIndex() const
{
	return m_charIndex;
};


// TODO: Use charIndex and expectedValues in message
const char* CmdCalculator::UnexpectedInputExpressionCharException::what() const noexcept
{
	return "An unexpected character was encountered";
}