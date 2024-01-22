#include "TrueWholefulNumberLiteralAntlrContextView.h"

#include <assert.h>


CmdCalculator::TrueWholefulNumberLiteralAntlrContextView::TrueWholefulNumberLiteralAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Wholeful_number_literalContext* wholefulNumberLiteralContext) :
	m_wholefulNumberLiteralContext{ wholefulNumberLiteralContext }
{
	assert(m_wholefulNumberLiteralContext);
}


CmdCalculator::TrueAntlrTokenView CmdCalculator::TrueWholefulNumberLiteralAntlrContextView::getWholePart() const
{
	assert(m_wholefulNumberLiteralContext->whole_part);
	return TrueAntlrTokenView{ m_wholefulNumberLiteralContext->whole_part };
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::TrueWholefulNumberLiteralAntlrContextView::getDecimalPoint() const
{
	return
		m_wholefulNumberLiteralContext->decimal_point
		? std::make_optional<TrueAntlrTokenView>(m_wholefulNumberLiteralContext->decimal_point)
		: std::optional<CmdCalculator::TrueAntlrTokenView>{}
	;
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::TrueWholefulNumberLiteralAntlrContextView::getFractionalPart() const
{
	return
		m_wholefulNumberLiteralContext->fractional_part
		? std::make_optional<TrueAntlrTokenView>(m_wholefulNumberLiteralContext->fractional_part)
		: std::optional<CmdCalculator::TrueAntlrTokenView>{}
	;
}