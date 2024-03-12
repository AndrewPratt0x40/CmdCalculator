#pragma once

#include "ExpressionEvaluationToStringConverter.h"
#include "NotImplementedException.h"


template<CmdCalculator::Expressions::Expression ExpressionT>
inline typename CmdCalculator::ExpressionEvaluationToStringConverter<ExpressionT>::StringType
	CmdCalculator::ExpressionEvaluationToStringConverter<ExpressionT>
	::stringifyExpression(const ExpressionT& source, const CalculationConfiguration& configuration) const
{
	throw NotImplementedException{};
}