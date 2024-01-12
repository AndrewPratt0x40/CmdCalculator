#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	struct ExpressionAntlrContext_IntendedSatisfaction;
	
	
	/// \brief The base type for types that are intended to satisfy the \ref GroupingAntlrContext concept.
	struct GroupingAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for a grouping parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept GroupingAntlrContext =
		IntendsToSatisfy<T, GroupingAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getInnerLeadingTrivia() } -> Optional;
			AntlrToken<typename decltype(instance.getInnerLeadingTrivia())::value_type>;

			IntendsToSatisfy<std::remove_reference_t<decltype(instance.getInnerExpression())>, ExpressionAntlrContext_IntendedSatisfaction>;

			{ instance.getInnerTrailingTrivia() } -> Optional;
			AntlrToken<typename decltype(instance.getInnerTrailingTrivia())::value_type>;
		}
	;
}