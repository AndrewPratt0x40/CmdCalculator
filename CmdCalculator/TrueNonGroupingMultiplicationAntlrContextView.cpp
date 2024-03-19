#include "TrueNonGroupingMultiplicationAntlrContextView.h"

#include <assert.h>


CmdCalculator::TrueNonGroupingMultiplicationAntlrContextView::TrueNonGroupingMultiplicationAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Non_grouping_multiplication_operandContext* nonGroupingMultiplicationContext) :
	m_nonGroupingMultiplicationContext{ nonGroupingMultiplicationContext }
{
	assert(m_nonGroupingMultiplicationContext);
}


CmdCalculator::ENonGroupingMultiplicationAntlrContextKind CmdCalculator::TrueNonGroupingMultiplicationAntlrContextView::getNonGroupingMultiplicationKind() const
{
	if (m_nonGroupingMultiplicationContext->number_literal_value)
		return ENonGroupingMultiplicationAntlrContextKind::NumberLiteral;

	if (m_nonGroupingMultiplicationContext->sign_operation_value)
		return ENonGroupingMultiplicationAntlrContextKind::SignOperation;

	if (m_nonGroupingMultiplicationContext->sqrt_operation_value)
		return ENonGroupingMultiplicationAntlrContextKind::SqrtOperation;

	if (m_nonGroupingMultiplicationContext->grouping_value)
		return ENonGroupingMultiplicationAntlrContextKind::Grouping;

	assert(m_nonGroupingMultiplicationContext->absolute_value_operation_value);
	return ENonGroupingMultiplicationAntlrContextKind::AbsoluteValueOperation;
}


std::optional<CmdCalculator::TrueNumberLiteralAntlrContextView> CmdCalculator::TrueNonGroupingMultiplicationAntlrContextView::getNumberLiteral() const
{
	return
		m_nonGroupingMultiplicationContext->number_literal_value
		? std::make_optional<TrueNumberLiteralAntlrContextView>(m_nonGroupingMultiplicationContext->number_literal_value)
		: std::optional<TrueNumberLiteralAntlrContextView>{}
	;
}


std::optional<CmdCalculator::TrueSignOperationAntlrContextView> CmdCalculator::TrueNonGroupingMultiplicationAntlrContextView::getSignOperation() const
{
	return
		m_nonGroupingMultiplicationContext->sign_operation_value
		? std::make_optional<TrueSignOperationAntlrContextView>(m_nonGroupingMultiplicationContext->sign_operation_value)
		: std::optional<TrueSignOperationAntlrContextView>{}
	;
}


std::optional<CmdCalculator::TrueSqrtOperationAntlrContextView> CmdCalculator::TrueNonGroupingMultiplicationAntlrContextView::getSqrtOperation() const
{
	return
		m_nonGroupingMultiplicationContext->sqrt_operation_value
		? std::make_optional<TrueSqrtOperationAntlrContextView>(m_nonGroupingMultiplicationContext->sqrt_operation_value)
		: std::optional<TrueSqrtOperationAntlrContextView>{}
	;
}


std::optional<CmdCalculator::TrueGroupingAntlrContextView> CmdCalculator::TrueNonGroupingMultiplicationAntlrContextView::getGrouping() const
{
	return
		m_nonGroupingMultiplicationContext->grouping_value
		? std::make_optional<TrueGroupingAntlrContextView>(m_nonGroupingMultiplicationContext->grouping_value)
		: std::optional<TrueGroupingAntlrContextView>{}
	;
}


std::optional<CmdCalculator::TrueAbsoluteValueOperationAntlrContextView> CmdCalculator::TrueNonGroupingMultiplicationAntlrContextView::getAbsoluteValueOperation() const
{
	return
		m_nonGroupingMultiplicationContext->absolute_value_operation_value
		? std::make_optional<TrueAbsoluteValueOperationAntlrContextView>(m_nonGroupingMultiplicationContext->absolute_value_operation_value)
		: std::optional<TrueAbsoluteValueOperationAntlrContextView>{}
	;
}