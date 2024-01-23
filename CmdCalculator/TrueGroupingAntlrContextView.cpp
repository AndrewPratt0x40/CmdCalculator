#include "TrueGroupingAntlrContextView.h"

#include <assert.h>
#include "TrueExpressionAntlrContextView.h"


CmdCalculator::TrueGroupingAntlrContextView::TrueGroupingAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::GroupingContext* groupingContext) :
	m_groupingContext{ groupingContext }
{
	assert(m_groupingContext);
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::TrueGroupingAntlrContextView::getInnerLeadingTrivia() const
{
	return
		m_groupingContext->inner_leading_trivia
		? std::make_optional<TrueAntlrTokenView>(m_groupingContext->inner_leading_trivia)
		: std::optional<TrueAntlrTokenView>{}
	;
}


CmdCalculator::TrueExpressionAntlrContextView CmdCalculator::TrueGroupingAntlrContextView::getInnerExpression() const
{
	return TrueExpressionAntlrContextView{ m_groupingContext->inner_expression };
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::TrueGroupingAntlrContextView::getInnerTrailingTrivia() const
{
	return
		m_groupingContext->inner_trailing_trivia
		? std::make_optional<TrueAntlrTokenView>(m_groupingContext->inner_trailing_trivia)
		: std::optional<TrueAntlrTokenView>{}
	;
}