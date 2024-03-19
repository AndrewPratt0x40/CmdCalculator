#include "TrueSignOperationAntlrContextView.h"

#include <assert.h>
#include "TrueOperandAntlrContextView.h"


CmdCalculator::TrueSignOperationAntlrContextView::TrueSignOperationAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Sign_operationContext* signOperationContext) :
	m_signOperationContext{ signOperationContext }
{
	assert(m_signOperationContext);
}


CmdCalculator::TrueSignOperatorAntlrContextView CmdCalculator::TrueSignOperationAntlrContextView::getSignOperator() const
{
	return TrueSignOperatorAntlrContextView{ m_signOperationContext->sign_operator_value };
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::TrueSignOperationAntlrContextView::getInnerTrivia() const
{
	return
		m_signOperationContext->inner_trivia
		? std::make_optional<TrueAntlrTokenView>(m_signOperationContext->inner_trivia)
		: std::optional<TrueAntlrTokenView>{}
	;
}


CmdCalculator::TrueOperandAntlrContextView CmdCalculator::TrueSignOperationAntlrContextView::getOperandValue() const
{
	return TrueOperandAntlrContextView{ m_signOperationContext->operand_value };
}