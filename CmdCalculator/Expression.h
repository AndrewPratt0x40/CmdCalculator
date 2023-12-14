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
			// TODO: The following line causes a C7598 error in Visual Studio, and an infinite loop when compiling. Possibly a bug in MSVC.
			//{ instance.getFullSimplification() } -> Expression;
			{ instance.getFullSimplification() } -> std::derived_from<Expression_IntendedSatisfaction>;
		}
	;
}