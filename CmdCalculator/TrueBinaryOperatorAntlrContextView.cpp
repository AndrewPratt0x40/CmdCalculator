#include "TrueBinaryOperatorAntlrContextView.h"

#include <assert.h>


CmdCalculator::TrueBinaryOperatorAntlrContextView::TrueBinaryOperatorAntlrContextView
	(const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Binary_operatorContext* binaryOperatorContext) :
	m_binaryOperatorContext{ binaryOperatorContext }
{
	assert(m_binaryOperatorContext);
}


CmdCalculator::MathAst::EBinaryOperator CmdCalculator::TrueBinaryOperatorAntlrContextView::getBinaryOperatorAntlrContextKind() const
{
	if (m_binaryOperatorContext->addition_operator)
		return MathAst::EBinaryOperator::Addition;

	if (m_binaryOperatorContext->subtraction_operator)
		return MathAst::EBinaryOperator::Subtraction;

	if (m_binaryOperatorContext->multiplication_operator)
		return MathAst::EBinaryOperator::Multiplication;

	if (m_binaryOperatorContext->division_operator)
		return MathAst::EBinaryOperator::Division;

	if (m_binaryOperatorContext->exponentiation_operator)
		return MathAst::EBinaryOperator::Exponentiation;

	if (m_binaryOperatorContext->nth_root_operator)
		return MathAst::EBinaryOperator::NthRoot;

	assert(m_binaryOperatorContext->modulo_operator);
	return MathAst::EBinaryOperator::Modulo;
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