#include "TrueGroupingMultiplicationAntlrContextView.h"

#include <assert.h>


CmdCalculator::TrueGroupingMultiplicationAntlrContextView::TrueGroupingMultiplicationAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Grouping_multiplicationContext* groupingMultiplicationContext) :
	m_groupingMultiplicationContext{ groupingMultiplicationContext }
{
	assert(m_groupingMultiplicationContext);
}


CmdCalculator::TrueNonGroupingMultiplicationAntlrContextView CmdCalculator::TrueGroupingMultiplicationAntlrContextView::getHeadMultiplicand() const
{
	return TrueNonGroupingMultiplicationAntlrContextView{ m_groupingMultiplicationContext->head_multiplicand };
}