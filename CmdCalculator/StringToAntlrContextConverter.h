#pragma once

#include<concepts>

#include "FullExpressionAntlrContext.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref StringToAntlrContextConverter concept.
	struct StringToAntlrContextConverter_IntendedSatisfaction
	{};


	/// \brief A type that parses strings into ANTLR contexts objects.
	/// \tparam T The converter type.
	template<class T>
	concept StringToAntlrContextConverter =
		std::derived_from<T, StringToAntlrContextConverter_IntendedSatisfaction>
		&& StringView<typename T::StringViewType>
		&& requires(T&& instance, typename T::StringViewType source)
		{
			{ *instance.getStringAsAntlrContext(source) } -> FullExpressionAntlrContext;
		}
	;
}