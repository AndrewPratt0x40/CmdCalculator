#pragma once

#include <concepts>

#include "strings.h"
#include "utilities.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref AntlrToken concept.
	struct AntlrToken_IntendedSatisfaction
	{};


	/// \brief A type that wraps an ANTLR token object.
	/// \tparam T The ANTLR token type.
	template<class T>
	concept AntlrToken =
		IntendsToSatisfy<T, AntlrToken_IntendedSatisfaction>
		&& requires(T&& instance)
		{
			{ instance.getText() } -> String;
			{ instance.getStartIndex() } -> std::convertible_to<size_t>;
			{ instance.getStopIndex() } -> std::convertible_to<size_t>;
		}
	;
}