#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "BinaryOperatorAntlrContext.h"
#include "OperandAntlrContext.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref OperationPartPairAntlrContext concept.
	struct OperationPartPairAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for an operation part pair parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept OperationPartPairAntlrContext =
		std::derived_from<T, OperationPartPairAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getOperatorLeadingTrivia() } -> Optional;
			AntlrToken<typename decltype(instance.getOperatorLeadingTrivia())::value_type>;

			{ instance.getOperatorValue() } -> BinaryOperatorAntlrContext;

			{ instance.getOperatorTrailingTrivia() } -> Optional;
			AntlrToken<typename decltype(instance.getOperatorTrailingTrivia())::value_type>;

			{ instance.getOperandValue() } -> OperandAntlrContext;
		}
	;
}