#include "TrueWholelessNumberLiteralAntlrContextView.h"

#include <assert.h>


CmdCalculator::TrueWholelessNumberLiteralAntlrContextView::TrueWholelessNumberLiteralAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Wholeless_number_literalContext* wholelessNumberLiteralContext) :
	m_wholelessNumberLiteralContext{ wholelessNumberLiteralContext }
{
	assert(m_wholelessNumberLiteralContext);
}


CmdCalculator::TrueAntlrTokenView CmdCalculator::TrueWholelessNumberLiteralAntlrContextView::getDecimalPoint() const
{
	assert(m_wholelessNumberLiteralContext->decimal_point);
	return TrueAntlrTokenView{ m_wholelessNumberLiteralContext->decimal_point };
}


CmdCalculator::TrueAntlrTokenView CmdCalculator::TrueWholelessNumberLiteralAntlrContextView::getFractionalPart() const
{
	assert(m_wholelessNumberLiteralContext->fractional_part);
	return TrueAntlrTokenView{ m_wholelessNumberLiteralContext->fractional_part };
}