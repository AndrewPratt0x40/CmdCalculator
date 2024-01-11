#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "WholefulNumberLiteralAntlrContext.h"
#include "WholelessNumberLiteralAntlrContext.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief Enumerates the different possible kinds of an ANTLR number literal parser rule.
	enum class ENumberLiteralAntlrContextKind
	{
		Wholeful,
		Wholeless,
	};


	/// \brief The base type for types that are intended to satisfy the \ref NumberLiteralAntlrContext concept.
	struct NumberLiteralAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for a number literal rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept NumberLiteralAntlrContext =
		std::derived_from<T, NumberLiteralAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
	{
		{ instance.getNumberLiteralAntlrContextKind() } -> std::same_as<ENumberLiteralAntlrContextKind>;

		{ instance.getWholefulNumberLiteral() } -> Optional;
		WholefulNumberLiteralAntlrContext<typename decltype(instance.getWholefulNumberLiteral())::value_type>;

		{ instance.getWholelessNumberLiteral() } -> Optional;
		WholelessNumberLiteralAntlrContext<typename decltype(instance.getWholelessNumberLiteral())::value_type>;
	}
	;
}