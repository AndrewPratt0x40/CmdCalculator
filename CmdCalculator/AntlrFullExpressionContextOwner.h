#pragma once

#include <concepts>

#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref AntlrFullExpressionContextOwner concept.
	struct AntlrFullExpressionContextOwner_IntendedSatisfaction
	{};


	/// \brief A type that owns an instance of \ref CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext.
	/// \tparam T The converter type.
	template<class T>
	concept AntlrFullExpressionContextOwner =
		std::derived_from<T, AntlrFullExpressionContextOwner_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getContext() } -> std::same_as<const Antlr::CmdCalculatorExpressionParser::Full_expressionContext&>;
		}
	;
}