#include "TrueAbsoluteValueOperationAntlrContextView.h"

#include <assert.h>
#include "TrueExpressionAntlrContextView.h"


CmdCalculator::TrueAbsoluteValueOperationAntlrContextView::TrueAbsoluteValueOperationAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Absolute_value_operationContext* absoluteValueOperationContext) :
	m_absoluteValueOperationContext{ absoluteValueOperationContext }
{
	assert(m_absoluteValueOperationContext);
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::TrueAbsoluteValueOperationAntlrContextView::getInnerLeadingTrivia() const
{
	return
		m_absoluteValueOperationContext->inner_leading_trivia
		? std::make_optional<TrueAntlrTokenView>(m_absoluteValueOperationContext->inner_leading_trivia)
		: std::optional<TrueAntlrTokenView>{}
	;
}


CmdCalculator::TrueExpressionAntlrContextView CmdCalculator::TrueAbsoluteValueOperationAntlrContextView::getInnerExpression() const
{
	return TrueExpressionAntlrContextView{ m_absoluteValueOperationContext->inner_expression };
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::TrueAbsoluteValueOperationAntlrContextView::getInnerTrailingTrivia() const
{
	return
		m_absoluteValueOperationContext->inner_trailing_trivia
		? std::make_optional<TrueAntlrTokenView>(m_absoluteValueOperationContext->inner_trailing_trivia)
		: std::optional<TrueAntlrTokenView>{}
	;
}