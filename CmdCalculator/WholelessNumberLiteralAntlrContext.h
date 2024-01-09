#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref WholelessNumberLiteralAntlrContext concept.
	struct WholelessNumberLiteralAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for a wholeless number literal rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept WholelessNumberLiteralAntlrContext =
		std::derived_from<T, WholelessNumberLiteralAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
	{
		{ instance.getWholelePart() } -> Optional;
		{ **instance.getWholelePart() } -> AntlrToken;

		{ instance.getDecimalPoint() } -> Optional;

		{ instance.getFractionalPart() } -> AntlrToken;
	}
	;
}