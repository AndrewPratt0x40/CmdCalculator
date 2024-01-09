#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "OperandAntlrContext.h"
#include "OperationPartPairAntlrContext.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref ExpressionAntlrContext concept.
	struct ExpressionAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for an expression parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept ExpressionAntlrContext =
		std::derived_from<T, ExpressionAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ *instance.getHeadOperand() } -> OperandAntlrContext;

			{ instance.getOperationPartPairs() } -> std::ranges::input_range;
			OperationPartPairAntlrContext<DereferencedRangeElementType<decltype(instance.getOperationPartPairs())>>;
		}
	;
}