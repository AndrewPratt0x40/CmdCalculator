#include "TrueOperationPartPairAntlrContextView.h"

#include <assert.h>


CmdCalculator::TrueOperationPartPairAntlrContextView::TrueOperationPartPairAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Operation_part_pairContext* operationPartPairContext) :
	m_operationPartPairContext{ operationPartPairContext }
{
	assert(m_operationPartPairContext);
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::TrueOperationPartPairAntlrContextView::getOperatorLeadingTrivia() const
{
	return
		m_operationPartPairContext->operator_leading_trivia
		? std::make_optional<TrueAntlrTokenView>(m_operationPartPairContext->operator_leading_trivia)
		: std::optional<TrueAntlrTokenView>{}
	;
}


CmdCalculator::TrueBinaryOperatorAntlrContextView CmdCalculator::TrueOperationPartPairAntlrContextView::getOperatorValue() const
{
	return TrueBinaryOperatorAntlrContextView{ m_operationPartPairContext->operator_value };
}


std::optional<CmdCalculator::TrueAntlrTokenView> CmdCalculator::TrueOperationPartPairAntlrContextView::getOperatorTrailingTrivia() const
{
	return
		m_operationPartPairContext->operator_trailing_trivia
		? std::make_optional<TrueAntlrTokenView>(m_operationPartPairContext->operator_trailing_trivia)
		: std::optional<TrueAntlrTokenView>{}
	;
}


CmdCalculator::TrueOperandAntlrContextView CmdCalculator::TrueOperationPartPairAntlrContextView::getOperandValue() const
{
	return TrueOperandAntlrContextView{ m_operationPartPairContext->operand_value };
}