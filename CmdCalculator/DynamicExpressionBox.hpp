#pragma once

#include <assert.h>

#include "DynamicExpressionBox.h"
#include "NotImplementedException.h"


template<CmdCalculator::Expressions::BoxableInnerExpression BoxedExpressionT>
CmdCalculator::Expressions::DynamicExpressionBox<BoxedExpressionT>::DynamicExpressionBox
(
	std::unique_ptr<BoxedExpressionT> innerValue
) :
	m_innerValue{ std::move(innerValue) }
{
	assert(m_innerValue);
}


template<CmdCalculator::Expressions::BoxableInnerExpression BoxedExpressionT>
inline const BoxedExpressionT& CmdCalculator::Expressions::DynamicExpressionBox<BoxedExpressionT>::getInnerValue() const
{
	return *m_innerValue;
}


template<CmdCalculator::Expressions::BoxableInnerExpression BoxedExpressionT>
inline typename BoxedExpressionT::NumberType CmdCalculator::Expressions::DynamicExpressionBox<BoxedExpressionT>::getEvaluation() const
{
	return m_innerValue->getEvaluation();
}