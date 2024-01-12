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
		IntendsToSatisfy<T, NonGroupingMultiplicationAntlrContext_IntendedSatisfaction>
		&& requires(T&& instance)
	{
		{ instance.getNonGroupingMultiplicationKind() } -> std::same_as<ENonGroupingMultiplicationAntlrContextKind>;

		{ instance.getNumberLiteral() } -> Optional;
		NumberLiteralAntlrContext<typename decltype(instance.getNumberLiteral())::value_type>;

		{ instance.getSignOperation() } -> Optional;
		SignOperationAntlrContext<typename decltype(instance.getSignOperation())::value_type>;

		{ instance.getSqrtOperation() } -> Optional;
		SqrtOperationAntlrContext<typename decltype(instance.getSqrtOperation())::value_type>;

		{ instance.getGrouping() } -> Optional;
		GroupingAntlrContext<typename decltype(instance.getGrouping())::value_type>;

		{ instance.getAbsoluteValueOperation() } -> Optional;
		AbsoluteValueOperationAntlrContext<typename decltype(instance.getAbsoluteValueOperation())::value_type>;
	}
	;
}