#pragma once

#include<concepts>

#include "strings.h"
#include "utilities.h"
#include "CalculationConfiguration.h"
#include "Expression.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref ExpressionToStringConverter concept.
	struct ExpressionToStringConverter_IntendedSatisfaction
	{};


	/// \brief A type that converts mathematical expressions into strings.
	/// \tparam T The converter type.
	template<class T>
	concept ExpressionToStringConverter =
		IntendsToSatisfy<T, ExpressionToStringConverter_IntendedSatisfaction>
		&& Expressions::Expression<typename T::ExpressionType>
		&& requires(T&& instance, const typename T::ExpressionType& source, const CalculationConfiguration configuration)
		{
			{ instance.stringifyExpression(source, configuration) } -> String;
		}
	;
}