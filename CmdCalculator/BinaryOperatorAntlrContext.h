#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "EBinaryOperator.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	struct OperandAntlrContext_IntendedSatisfaction;


	/// \brief The base type for types that are intended to satisfy the \ref BinaryOperatorAntlrContext concept.
	struct BinaryOperatorAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for a binary operator parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept BinaryOperatorAntlrContext =
		IntendsToSatisfy<T, BinaryOperatorAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getBinaryOperatorAntlrContextKind() } -> std::same_as<MathAst::EBinaryOperator>;
			{ instance.getToken() } -> AntlrToken;
		}
	;
}