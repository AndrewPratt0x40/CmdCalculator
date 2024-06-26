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
		IntendsToSatisfy<T, SqrtOperationAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getInnerTrivia() } -> Optional;
			AntlrToken<typename decltype(instance.getInnerTrivia())::value_type>;

			IntendsToSatisfy<std::remove_reference_t<decltype(instance.getOperandValue())>, OperandAntlrContext_IntendedSatisfaction>;
		}
	;
}