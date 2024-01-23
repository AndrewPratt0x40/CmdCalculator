#include "TrueExpressionAntlrContextView.h"

#include <assert.h>


CmdCalculator::TrueExpressionAntlrContextView::TrueExpressionAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::ExpressionContext* expressionContext) :
	m_expressionContext{ expressionContext }
{
	assert(m_expressionContext);
}


CmdCalculator::TrueOperandAntlrContextView CmdCalculator::TrueExpressionAntlrContextView::getHeadOperand() const
{
	return TrueOperandAntlrContextView{ m_expressionContext->head_operand };
}


std::ranges::input_range auto CmdCalculator::TrueExpressionAntlrContextView::getOperationPartPairs() const
{
	return
		m_expressionContext->operation_part_pairs()
		| std::views::transform
		(
			[](auto* operationPartPair)
			{
				return TrueGroupingTailMultiplicandAntlrContextView{ tailMultiplicand };
			}
		)
	;
}