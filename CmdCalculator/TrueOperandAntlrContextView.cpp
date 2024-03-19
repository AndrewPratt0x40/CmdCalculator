#include "TrueOperandAntlrContextView.h"

#include <assert.h>


CmdCalculator::TrueOperandAntlrContextView::TrueOperandAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::OperandContext* operandContext) :
	m_operandContext{ operandContext }
{
	assert(m_operandContext);
}


bool CmdCalculator::TrueOperandAntlrContextView::isGroupingMultiplication() const
{
	return m_operandContext->grouping_multiplication_value;
}


std::optional<CmdCalculator::TrueNonGroupingMultiplicationAntlrContextView> CmdCalculator::TrueOperandAntlrContextView::getNonGroupingMultiplicationOperand() const
{
	return
		m_operandContext->non_grouping_multiplication_operand_value
		? std::make_optional<TrueNonGroupingMultiplicationAntlrContextView>(m_operandContext->non_grouping_multiplication_operand_value)
		: std::optional<TrueNonGroupingMultiplicationAntlrContextView>{}
	;
}


std::optional<CmdCalculator::TrueGroupingMultiplicationAntlrContextView> CmdCalculator::TrueOperandAntlrContextView::getGroupingMultiplicationOperand() const
{
	return
		m_operandContext->grouping_multiplication_value
		? std::make_optional<TrueGroupingMultiplicationAntlrContextView>(m_operandContext->grouping_multiplication_value)
		: std::optional<TrueGroupingMultiplicationAntlrContextView>{}
	;
}