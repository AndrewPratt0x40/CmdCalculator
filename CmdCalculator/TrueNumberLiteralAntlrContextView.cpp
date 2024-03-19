#include "TrueNumberLiteralAntlrContextView.h"

#include <assert.h>


CmdCalculator::TrueNumberLiteralAntlrContextView::TrueNumberLiteralAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Number_literalContext* numberLiteralContext) :
	m_numberLiteralContext{ numberLiteralContext }
{
	assert(m_numberLiteralContext);
}


CmdCalculator::ENumberLiteralAntlrContextKind CmdCalculator::TrueNumberLiteralAntlrContextView::getNumberLiteralAntlrContextKind() const
{
	return
		m_numberLiteralContext->wholeful_number_literal_value
		? ENumberLiteralAntlrContextKind::Wholeful
		: ENumberLiteralAntlrContextKind::Wholeless
	;
}


std::optional<CmdCalculator::TrueWholefulNumberLiteralAntlrContextView> CmdCalculator::TrueNumberLiteralAntlrContextView::getWholefulNumberLiteral() const
{
	return
		m_numberLiteralContext->wholeful_number_literal_value
		? std::make_optional<CmdCalculator::TrueWholefulNumberLiteralAntlrContextView>(m_numberLiteralContext->wholeful_number_literal_value)
		: std::optional<CmdCalculator::TrueWholefulNumberLiteralAntlrContextView>{}
	;
}


std::optional<CmdCalculator::TrueWholelessNumberLiteralAntlrContextView> CmdCalculator::TrueNumberLiteralAntlrContextView::getWholelessNumberLiteral() const
{
	return
		m_numberLiteralContext->wholeless_number_literal_value
		? std::make_optional<CmdCalculator::TrueWholelessNumberLiteralAntlrContextView>(m_numberLiteralContext->wholeless_number_literal_value)
		: std::optional<CmdCalculator::TrueWholelessNumberLiteralAntlrContextView>{}
	;
}