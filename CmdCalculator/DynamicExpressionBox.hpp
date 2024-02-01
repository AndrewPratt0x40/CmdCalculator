#pragma once

#include <assert.h>

#include "DynamicExpressionBox.h"
#include "NotImplementedException.h"


#pragma push_macro("THIS_NUMBER_TYPE")
#define THIS_NUMBER_TYPE CmdCalculator::Expressions::DynamicExpressionBox<NumberT>::NumberType
#pragma push_macro("THIS_NUMBER_TYPENAME")
#define THIS_NUMBER_TYPENAME typename THIS_NUMBER_TYPE


template<CmdCalculator::Arithmetic::RealNumber NumberT>
CmdCalculator::Expressions::DynamicExpressionBox<NumberT>::DynamicExpressionBox
(
	std::unique_ptr<DynamicExpression<NumberType>> innerValue
) :
	m_innerValue{ std::move(innerValue) }
{
	assert(m_innerValue);
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline bool CmdCalculator::Expressions::DynamicExpressionBox<NumberT>::isSimplifiable() const
{
	return m_innerValue->isSimplifiable();
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpressionBox<THIS_NUMBER_TYPENAME>
	CmdCalculator::Expressions::DynamicExpressionBox<NumberT>::getFullSimplification() const
{
	return std::move(m_innerValue->getFullSimplification());
}


#pragma pop_macro("THIS_NUMBER_TYPE")
#pragma pop_macro("THIS_NUMBER_TYPENAME")