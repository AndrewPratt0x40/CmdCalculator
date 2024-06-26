#pragma once

#include "DynamicSubtractionOperation.h"
#include "NotImplementedException.h"


#pragma push_macro("THIS_NUMBER_TYPE")
#define THIS_NUMBER_TYPE CmdCalculator::Expressions::DynamicSubtractionOperation<NumberT>::NumberType
#pragma push_macro("THIS_NUMBER_TYPENAME")
#define THIS_NUMBER_TYPENAME typename THIS_NUMBER_TYPE


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicSubtractionOperation<NumberT>::DynamicSubtractionOperation
(
	std::unique_ptr<DynamicExpression<NumberType>> minuend,
	std::unique_ptr<DynamicExpression<NumberType>> subtrahend
) :
	CommonDynamicBinaryOperation<NumberType>
	(
		std::move(minuend),
		std::move(subtrahend)
	)
{}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicSubtractionOperation<NumberT>::~DynamicSubtractionOperation() = default;


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::DynamicSubtractionOperation<NumberT>::getMinuend() const
{
	return CommonDynamicBinaryOperation<NumberType>::getLeftOperand();
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::DynamicSubtractionOperation<NumberT>::getSubtrahend() const
{
	return CommonDynamicBinaryOperation<NumberType>::getRightOperand();
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline THIS_NUMBER_TYPE
	CmdCalculator::Expressions::DynamicSubtractionOperation<NumberT>::getEvaluation() const
{
	return getMinuend().getEvaluation() - getSubtrahend().getEvaluation();
}


/*template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline bool CmdCalculator::Expressions::DynamicSubtractionOperation<NumberT>::isSimplifiable() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpressionBox<THIS_NUMBER_TYPENAME>
	CmdCalculator::Expressions::DynamicSubtractionOperation<NumberT>::getFullSimplification() const
{
	throw NotImplementedException{};
}*/


#pragma pop_macro("THIS_NUMBER_TYPE")
#pragma pop_macro("THIS_NUMBER_TYPENAME")