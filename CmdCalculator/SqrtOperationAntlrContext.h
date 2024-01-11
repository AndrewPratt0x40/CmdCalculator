#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	struct OperandAntlrContext_IntendedSatisfaction;


	/// \brief The base type for types that are intended to satisfy the \ref SqrtOperationAntlrContext concept.
	struct SqrtOperationAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for a square root operation parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept SqrtOperationAntlrContext =
		std::derived_from<T, SqrtOperationAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getInnerTrivia() } -> Optional;
			{ *instance.getInnerTrivia() } -> AntlrToken;

			{ instance.getOperandValue() } -> std::derived_from<OperandAntlrContext_IntendedSatisfaction>;
		}
	;
}