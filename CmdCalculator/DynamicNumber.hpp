#pragma once

#include "DynamicNumber.h"
#include "NotImplementedException.h"


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicNumber<NumberT>::DynamicNumber(const NumberType value) :
	m_value{ value }
{}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicNumber<NumberT>::~DynamicNumber() = default;


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline NumberT CmdCalculator::Expressions::DynamicNumber<NumberT>::getValue() const
{
	return m_value;
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline NumberT CmdCalculator::Expressions::DynamicNumber<NumberT>::getEvaluation() const
{
	return m_value;
}


/*template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline bool CmdCalculator::Expressions::DynamicNumber<NumberT>::isSimplifiable() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpressionBox<THIS_NUMBER_TYPENAME>
	CmdCalculator::Expressions::DynamicNumber<NumberT>::getFullSimplification() const
{
	return DynamicExpressionBox();
}*/