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