#pragma once

#include "CommonDynamicBinaryOperation.h"
#include "NotImplementedException.h"


#pragma push_macro("THIS_NUMBER_TYPE")
#define THIS_NUMBER_TYPE CmdCalculator::Expressions::CommonDynamicBinaryOperation<NumberT>::NumberType
#pragma push_macro("THIS_NUMBER_TYPENAME")
#define THIS_NUMBER_TYPENAME typename THIS_NUMBER_TYPE


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::CommonDynamicBinaryOperation<NumberT>::CommonDynamicBinaryOperation
(
	std::unique_ptr<DynamicExpression<NumberType>> leftOperand,
	std::unique_ptr<DynamicExpression<NumberType>> rightOperand
) :
	m_leftOperand{ std::move(leftOperand) },
	m_rightOperand{ std::move(rightOperand) }
{
	assert(m_leftOperand);
	assert(m_rightOperand);
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::CommonDynamicBinaryOperation<NumberT>::~CommonDynamicBinaryOperation() = default;


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::CommonDynamicBinaryOperation<NumberT>::getLeftOperand() const
{
	assert(m_leftOperand);
	return *m_leftOperand;
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::CommonDynamicBinaryOperation<NumberT>::getRightOperand() const
{
	assert(m_rightOperand);
	return *m_rightOperand;
}


/*template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline bool CmdCalculator::Expressions::CommonDynamicBinaryOperation<NumberT>::isSimplifiable() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpressionBox<THIS_NUMBER_TYPENAME>
	CmdCalculator::Expressions::CommonDynamicBinaryOperation<NumberT>::getFullSimplification() const
{
	throw NotImplementedException{};
}*/


#pragma pop_macro("THIS_NUMBER_TYPE")
#pragma pop_macro("THIS_NUMBER_TYPENAME")