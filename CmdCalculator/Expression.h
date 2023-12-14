#pragma once

#include<concepts>

namespace CmdCalculator::Expressions
{
	/// \brief The base type for types that are intended to satisfy the \ref Expression concept.
	struct Expression_IntendedSatisfaction
	{};


	/// \brief A mathematical expression.
	/// \tparam T The type of the expression.
	template<class T>
	concept Expression =
		std::derived_from<T, Expression_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.isSimplifiable() } -> std::same_as<bool>;
			{ instance.getFullSimplification() } -> Expression;
		}
	;
}