#include "TrueBinaryOperatorAntlrContextView.h"

#include <assert.h>


CmdCalculator::TrueBinaryOperatorAntlrContextView::TrueBinaryOperatorAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Binary_operatorContext* binaryOperatorContext) :
	m_binaryOperatorContext{ binaryOperatorContext }
{
	assert(m_binaryOperatorContext);
}


CmdCalculator::EBinaryOperatorAntlrContextKind CmdCalculator::TrueBinaryOperatorAntlrContextView::getBinaryOperatorAntlrContextKind() const
{
	if (m_binaryOperatorContext->addition_operator)
		return EBinaryOperatorAntlrContextKind::Addition;

	if (m_binaryOperatorContext->subtraction_operator)
		return EBinaryOperatorAntlrContextKind::Subtraction;

	if (m_binaryOperatorContext->multiplication_operator)
		return EBinaryOperatorAntlrContextKind::Multiplication;

	if (m_binaryOperatorContext->division_operator)
		return EBinaryOperatorAntlrContextKind::Division;

	if (m_binaryOperatorContext->exponentiation_operator)
		return EBinaryOperatorAntlrContextKind::Exponentiation;

	if (m_binaryOperatorContext->nth_root_operator)
		return EBinaryOperatorAntlrContextKind::NthRoot;

	assert(m_binaryOperatorContext->modulo_operator);
	return EBinaryOperatorAntlrContextKind::Modulo;
}


CmdCalculator::TrueAntlrTokenView CmdCalculator::TrueBinaryOperatorAntlrContextView::getToken() const
{
	if (m_binaryOperatorContext->addition_operator)
		return TrueAntlrTokenView{ m_binaryOperatorContext->addition_operator };

	if (m_binaryOperatorContext->subtraction_operator)
		return TrueAntlrTokenView{ m_binaryOperatorContext->subtraction_operator };

	if (m_binaryOperatorContext->multiplication_operator)
		return TrueAntlrTokenView{ m_binaryOperatorContext->multiplication_operator };

	if (m_binaryOperatorContext->division_operator)
		return TrueAntlrTokenView{ m_binaryOperatorContext->division_operator };

	if (m_binaryOperatorContext->exponentiation_operator)
		return TrueAntlrTokenView{ m_binaryOperatorContext->exponentiation_operator };

	if (m_binaryOperatorContext->nth_root_operator)
		return TrueAntlrTokenView{ m_binaryOperatorContext->nth_root_operator };

	assert(m_binaryOperatorContext->modulo_operator);
	return TrueAntlrTokenView{ m_binaryOperatorContext->modulo_operator };
}