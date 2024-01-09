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
		{ instance.isWholeful() } -> std::same_as<bool>;

		{ instance.getWholefulNumberLiteral() } -> Optional;
		{ **instance.getWholefulNumberLiteral() } -> WholefulNumberLiteralAntlrContext;

		{ instance.getWholelessNumberLiteral() } -> Optional;
		{ **instance.getWholelessNumberLiteral() } -> WholelessNumberLiteralAntlrContext;
	}
	;
}