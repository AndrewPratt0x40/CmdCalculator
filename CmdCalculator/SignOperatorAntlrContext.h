#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	struct OperandAntlrContext_IntendedSatisfaction;


	/// \brief Enumerates the different possible kinds of an ANTLR sign operator parser rule.
	enum class ESignOperatorAntlrContextKind
	{
		Positive,
		Negative,
	};


	/// \brief The base type for types that are intended to satisfy the \ref SignOperatorAntlrContext concept.
	struct SignOperatorAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for a sign operator parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept SignOperatorAntlrContext =
		IntendsToSatisfy<T, SignOperatorAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getSignOperatorAntlrContextKind() } -> std::same_as<ESignOperatorAntlrContextKind>;
			{ instance.getToken() } -> AntlrToken;
		}
	;
}