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


	/// \brief A type that wraps a ANTLR context object for a full_expression parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept FullExpressionAntlrContext =
		std::derived_from<T, FullExpressionAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
	{
		{ instance.getLeadingTrivia() } -> Optional;
		{ **instance.getLeadingTrivia() } -> AntlrToken;

		{ *instance.getExpressionValue() } -> ExpressionAntlrContext;
		
		{ instance.getTrailingTrivia() } -> Optional;
		{ **instance.getTrailingTrivia() } -> AntlrToken;
	}
	;
}