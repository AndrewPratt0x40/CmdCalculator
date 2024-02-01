#pragma once

#include "DynamicMultiplicationOperation.h"
#include "NotImplementedException.h"


#pragma push_macro("THIS_NUMBER_TYPE")
#define THIS_NUMBER_TYPE CmdCalculator::Expressions::DynamicMultiplicationOperation<NumberT>::NumberType
#pragma push_macro("THIS_NUMBER_TYPENAME")
#define THIS_NUMBER_TYPENAME typename THIS_NUMBER_TYPE


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicMultiplicationOperation<NumberT>::DynamicMultiplicationOperation
(
	std::unique_ptr<DynamicExpression<NumberType>> multiplier,
	std::unique_ptr<DynamicExpression<NumberType>> multiplicand
) :
	CommonDynamicBinaryOperation<NumberType>
	(
		std::move(multiplier),
		std::move(multiplicand)
	)
{}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicMultiplicationOperation<NumberT>::~DynamicMultiplicationOperation() = default;


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::DynamicMultiplicationOperation<NumberT>::getMultiplier() const
{
	return CommonDynamicBinaryOperation<NumberType>::getLeftOperand();
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::DynamicMultiplicationOperation<NumberT>::getMultiplicand() const
{
	return CommonDynamicBinaryOperation<NumberType>::getRightOperand();
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline THIS_NUMBER_TYPE
	CmdCalculator::Expressions::DynamicMultiplicationOperation<NumberT>::getEvaluation() const
{
	return getMultiplier().getEvaluation() * getMultiplicand().getEvaluation();
}


/*template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline bool CmdCalculator::Expressions::DynamicMultiplicationOperation<NumberT>::isSimplifiable() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpressionBox<THIS_NUMBER_TYPENAME>
	CmdCalculator::Expressions::DynamicMultiplicationOperation<NumberT>::getFullSimplification() const
{
	throw NotImplementedException{};
}*/


#pragma pop_macro("THIS_NUMBER_TYPE")
#pragma pop_macro("THIS_NUMBER_TYPENAME")