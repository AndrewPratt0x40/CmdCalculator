#pragma once

#include <concepts>
#include <optional>

#include "AntlrToken.h"
#include "ExpressionAntlrContext.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref FullExpressionAntlrContext concept.
	struct FullExpressionAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for a full expression parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept FullExpressionAntlrContext =
		IntendsToSatisfy<T, FullExpressionAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getLeadingTrivia() } -> Optional;
			AntlrToken<typename decltype(instance.getLeadingTrivia())::value_type>;

			{ instance.getExpressionValue() } -> ExpressionAntlrContext;
		
			{ instance.getTrailingTrivia() } -> Optional;
			AntlrToken<typename decltype(instance.getTrailingTrivia())::value_type>;
		}
	;
}