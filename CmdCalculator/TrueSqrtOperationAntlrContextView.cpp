#include "TrueSqrtOperationAntlrContextView.h"

#include <assert.h>
#include "TrueOperandAntlrContextView.h"


CmdCalculator::TrueSqrtOperationAntlrContextView::TrueSqrtOperationAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sqrt_operationContext* sqrtOperationContext) :
	m_sqrtOperationContext{ sqrtOperationContext }
{
	assert(m_sqrtOperationContext);
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::TrueSqrtOperationAntlrContextView::getInnerTrivia() const
{
	return
		m_sqrtOperationContext->inner_trivia
		? std::make_optional<TrueAntlrTokenView>(m_sqrtOperationContext->inner_trivia)
		: std::optional<TrueAntlrTokenView>{}
	;
}


CmdCalculator::TrueOperandAntlrContextView CmdCalculator::TrueSqrtOperationAntlrContextView::getOperandValue() const
{
	return TrueOperandAntlrContextView{ m_sqrtOperationContext->operand_value };
}