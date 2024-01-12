#pragma once

#include<concepts>
#include "utilities.h"

namespace CmdCalculator::Expressions
{
	/// \brief The base type for types that are intended to satisfy the \ref Expression concept.
	struct Expression_IntendedSatisfaction
	{};


	/// \brief A mathematical expression.
	/// \tparam T The type of the expression.
	template<class T>
	concept Expression =
		IntendsToSatisfy<T, Expression_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.isSimplifiable() } -> std::same_as<bool>;
			{ instance.getFullSimplification() } -> IntendsToSatisfy<Expression_IntendedSatisfaction>;
		}
	;
}