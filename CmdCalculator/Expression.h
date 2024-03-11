#pragma once

#include<concepts>
#include "RealNumber.h"
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
			{ instance.getEvaluation() } -> Arithmetic::RealNumber;
			// TODO: { instance.isSimplifiable() } -> std::same_as<bool>;
			// TODO: { instance.getFullSimplification() } -> IntendsToSatisfy<Expression_IntendedSatisfaction>;
		}
	;


	template<Expression ExpressionT>
	using ExpressionEvaluationType = decltype
	(
		std::declval<ExpressionT>().getEvaluation()
	);
}