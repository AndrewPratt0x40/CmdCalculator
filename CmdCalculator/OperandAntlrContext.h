#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "GroupingMultiplicationAntlrContext.h"
#include "NonGroupingMultiplicationAntlrContext.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref OperandAntlrContext concept.
	struct OperandAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for an operand parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept OperandAntlrContext =
		std::derived_from<T, OperandAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.isGroupingMultiplication() } -> std::same_as<bool>;

			{ instance.getNonGroupingMultiplicationOperand() } -> Optional;
			NonGroupingMultiplicationAntlrContext<typename decltype(instance.getNonGroupingMultiplicationOperand())::value_type>;

			{ instance.getGroupingMultiplicationOperand() } -> Optional;
			GroupingMultiplicationAntlrContext<typename decltype(instance.getGroupingMultiplicationOperand())::value_type>;
		}
	;
}