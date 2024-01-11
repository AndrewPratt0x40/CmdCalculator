#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref WholefulNumberLiteralAntlrContext concept.
	struct WholefulNumberLiteralAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for a wholeful number literal rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept WholefulNumberLiteralAntlrContext =
		std::derived_from<T, WholefulNumberLiteralAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getWholePart() } -> AntlrToken;

			{ instance.getDecimalPoint() } -> Optional;
			AntlrToken<typename decltype(instance.getDecimalPoint())::value_type>;

			{ instance.getFractionalPart() } -> Optional;
			AntlrToken<typename decltype(instance.getFractionalPart())::value_type>;
		}
	;
}