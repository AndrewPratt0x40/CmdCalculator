#pragma once

#include "DynamicDivisionOperation.h"
#include "DivisionByZeroException.h"
#include "NotImplementedException.h"


#pragma push_macro("THIS_NUMBER_TYPE")
#define THIS_NUMBER_TYPE CmdCalculator::Expressions::DynamicDivisionOperation<NumberT>::NumberType
#pragma push_macro("THIS_NUMBER_TYPENAME")
#define THIS_NUMBER_TYPENAME typename THIS_NUMBER_TYPE


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicDivisionOperation<NumberT>::DynamicDivisionOperation
(
	std::unique_ptr<DynamicExpression<NumberType>> dividend,
	std::unique_ptr<DynamicExpression<NumberType>> divisor
) :
	CommonDynamicBinaryOperation<NumberType>
	(
		std::move(dividend),
		std::move(divisor)
	)
{}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicDivisionOperation<NumberT>::~DynamicDivisionOperation() = default;


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::DynamicDivisionOperation<NumberT>::getDividend() const
{
	return CommonDynamicBinaryOperation<NumberType>::getLeftOperand();
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::DynamicDivisionOperation<NumberT>::getDivisor() const
{
	return CommonDynamicBinaryOperation<NumberType>::getRightOperand();
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline THIS_NUMBER_TYPE
	CmdCalculator::Expressions::DynamicDivisionOperation<NumberT>::getEvaluation() const
{
	const NumberType divisorEvaluation{ getDivisor().getEvaluation() };
	if (divisorEvaluation == NumberType::getZero())
	{
		throw DivisionByZeroException
		{
			std::move
			(
				convertString<char>(divisorEvaluation.getStringRepresentation())
			)
		};
	}

	return getDividend().getEvaluation() / divisorEvaluation;
}


/*template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline bool CmdCalculator::Expressions::DynamicDivisionOperation<NumberT>::isSimplifiable() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpressionBox<THIS_NUMBER_TYPENAME>
	CmdCalculator::Expressions::DynamicDivisionOperation<NumberT>::getFullSimplification() const
{
	throw NotImplementedException{};
}*/


#pragma pop_macro("THIS_NUMBER_TYPE")
#pragma pop_macro("THIS_NUMBER_TYPENAME")