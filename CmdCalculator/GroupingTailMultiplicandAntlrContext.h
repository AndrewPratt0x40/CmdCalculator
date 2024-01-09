#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "GroupingAntlrContext.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	struct ExpressionAntlrContext_IntendedSatisfaction;
	
	
	/// \brief The base type for types that are intended to satisfy the \ref GroupingTailMultiplicandAntlrContext concept.
	struct GroupingTailMultiplicandAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for a grouping tail multiplicand parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept GroupingTailMultiplicandAntlrContext =
		std::derived_from<T, GroupingTailMultiplicandAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getInnerTrivia() } -> Optional;
			{ **instance.getInnerTrivia() } -> AntlrToken;

			{ *instance.getGroupingValue() } -> GroupingAntlrContext;
		}
	;
}