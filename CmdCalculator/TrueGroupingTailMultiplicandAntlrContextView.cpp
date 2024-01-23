#include "TrueGroupingTailMultiplicandAntlrContextView.h"

#include <assert.h>


CmdCalculator::TrueGroupingTailMultiplicandAntlrContextView::TrueGroupingTailMultiplicandAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Grouping_tail_multiplicandContext* groupingTailMultiplicandContext) :
	m_groupingTailMultiplicandContext{ groupingTailMultiplicandContext }
{
	assert(m_groupingTailMultiplicandContext);
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::TrueGroupingTailMultiplicandAntlrContextView::getInnerTrivia() const
{
	return
		m_groupingTailMultiplicandContext->inner_trivia
		? std::make_optional<TrueAntlrTokenView>(m_groupingTailMultiplicandContext->inner_trivia)
		: std::optional<TrueAntlrTokenView>{}
	;
}


CmdCalculator::TrueGroupingAntlrContextView CmdCalculator::TrueGroupingTailMultiplicandAntlrContextView::getGroupingValue() const
{
	return TrueGroupingAntlrContextView{ m_groupingTailMultiplicandContext->grouping_value };
}