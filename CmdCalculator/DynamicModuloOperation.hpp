#pragma once

#include "DynamicModuloOperation.h"
#include "NotImplementedException.h"


#pragma push_macro("THIS_NUMBER_TYPE")
#define THIS_NUMBER_TYPE CmdCalculator::Expressions::DynamicModuloOperation<NumberT>::NumberType
#pragma push_macro("THIS_NUMBER_TYPENAME")
#define THIS_NUMBER_TYPENAME typename THIS_NUMBER_TYPE


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicModuloOperation<NumberT>::DynamicModuloOperation
(
	std::unique_ptr<DynamicExpression<NumberType>> dividend,
	std::unique_ptr<DynamicExpression<NumberType>> divisor
)
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicModuloOperation<NumberT>::~DynamicModuloOperation() = default;


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::DynamicModuloOperation<NumberT>::getDividend() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::DynamicModuloOperation<NumberT>::getDivisor() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline bool CmdCalculator::Expressions::DynamicModuloOperation<NumberT>::isSimplifiable() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpressionBox<THIS_NUMBER_TYPENAME>
	CmdCalculator::Expressions::DynamicModuloOperation<NumberT>::getFullSimplification() const
{
	throw NotImplementedException{};
}


#pragma pop_macro("THIS_NUMBER_TYPE")
#pragma pop_macro("THIS_NUMBER_TYPENAME")