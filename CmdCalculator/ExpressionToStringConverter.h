#pragma once

#include<concepts>

#include "strings.h"
#include "Expression.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref ExpressionToStringConverter concept.
	struct ExpressionToStringConverter_IntendedSatisfaction
	{};


	/// \brief A type that converts mathematical expressions into strings.
	/// \tparam T The converter type.
	/// \tparam ExpressionT The type of the expression to be converted into a string.
	template<class T, class ExpressionT>
	concept ExpressionToStringConverter =
		std::derived_from<T, ExpressionToStringConverter_IntendedSatisfaction>
		&& Expressions::Expression<ExpressionT>
		&& requires(T&& instance, ExpressionT source)
		{
			{ instance.stringifyExpression(source) } -> String;
		}
	;
}