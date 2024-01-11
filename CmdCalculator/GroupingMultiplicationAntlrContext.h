#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "NonGroupingMultiplicationAntlrContext.h"
#include "GroupingTailMultiplicandAntlrContext.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	struct ExpressionAntlrContext_IntendedSatisfaction;
	
	
	/// \brief The base type for types that are intended to satisfy the \ref GroupingMultiplicationAntlrContext concept.
	struct GroupingMultiplicationAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for a grouping multiplication parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept GroupingMultiplicationAntlrContext =
		std::derived_from<T, GroupingMultiplicationAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getHeadMultiplicand() } -> NonGroupingMultiplicationAntlrContext;

			{ instance.getTailMultiplicands() } -> std::ranges::input_range;
			GroupingTailMultiplicandAntlrContext<std::ranges::range_value_t<decltype(instance.getTailMultiplicands())>>;
		}
	;
}