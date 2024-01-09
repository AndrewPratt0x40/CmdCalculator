#pragma once

#include <concepts>
#include <ranges>

#include "AntlrToken.h"
#include "NumberLiteralAntlrContext.h"
#include "SignOperationAntlrContext.h"
#include "SqrtOperationAntlrContext.h"
#include "GroupingAntlrContext.h"
#include "AbsoluteValueOperationAntlrContext.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief Enumerates the different possible kinds of an ANTLR non-grouping operand parser rule.
	enum class ENonGroupingMultiplicationAntlrContextKind
	{
		NumberLiteral,
		SignOperation,
		SqrtOperation,
		Grouping,
		AbsoluteValueOperation
	};


	/// \brief The base type for types that are intended to satisfy the \ref NonGroupingMultiplicationAntlrContext concept.
	struct NonGroupingMultiplicationAntlrContext_IntendedSatisfaction
	{};


	/// \brief A type that wraps a ANTLR context object for a non-grouping operand parser rule.
	/// \tparam T The ANTLR context type.
	template<class T>
	concept NonGroupingMultiplicationAntlrContext =
		std::derived_from<T, NonGroupingMultiplicationAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
	{
		{ instance.getNonGroupingMultiplicationKind() } -> std::same_as<ENonGroupingMultiplicationAntlrContextKind>;

		{ instance.getNumberLiteral() } -> Optional;
		{ **instance.getNumberLiteral() } -> NumberLiteralAntlrContext;

		{ instance.getSignOperation() } -> Optional;
		{ **instance.getSignOperation() } -> SignOperationAntlrContext;

		{ instance.getSqrtOperation() } -> Optional;
		{ **instance.getSqrtOperation() } -> SqrtOperationAntlrContext;

		{ instance.getGrouping() } -> Optional;
		{ **instance.getGrouping() } -> GroupingAntlrContext;

		{ instance.getAbsoluteValueOperation() } -> Optional;
		{ **instance.getAbsoluteValueOperation() } -> AbsoluteValueOperationAntlrContext;
	}
	;
}