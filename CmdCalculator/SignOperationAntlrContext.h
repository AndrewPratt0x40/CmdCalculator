#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "SignOperatorAntlrContext.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	struct OperandAntlrContext_IntendedSatisfaction;


	/// \brief The base type for types that are intended to satisfy the \ref SignOperationAntlrContext concept.
	struct SignOperationAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for a sign operation parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept SignOperationAntlrContext =
		std::derived_from<T, SignOperationAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getSignOperator() } -> SignOperatorAntlrContext;

			{ instance.getInnerTrivia() } -> Optional;
			AntlrToken<typename decltype(instance.getInnerTrivia())::value_type>;

			std::derived_from<std::remove_reference_t<decltype(instance.getOperandValue())>, OperandAntlrContext_IntendedSatisfaction>;
		}
	;
}