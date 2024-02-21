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
		IntendsToSatisfy<T, ExpressionAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getHeadOperand() } -> OperandAntlrContext;

			{ instance.getOperationPartPairs() } -> std::ranges::forward_range;
			OperationPartPairAntlrContext<std::ranges::range_value_t<decltype(instance.getOperationPartPairs())>>;

			std::same_as
			<
				decltype(instance.getHeadOperand()),
				std::ranges::range_value_t<decltype(instance.getOperationPartPairs())>
			>;
		}
	;
}