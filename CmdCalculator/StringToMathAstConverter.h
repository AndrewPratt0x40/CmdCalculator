#pragma once

#include<concepts>

#include "strings.h"
#include "MathAstNode.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref StringToMathConverter concept.
	struct StringToMathAstConverter_IntendedSatisfaction
	{};


	/// \brief A type that parses strings into mathematical abstract syntax trees.
	/// \tparam T The converter type.
	template<class T>
	concept StringToMathAstConverter =
		std::derived_from<T, StringToMathAstConverter_IntendedSatisfaction>
		&& StringView<typename T::StringViewType>
		&& requires(T&& instance, typename T::StringViewType source)
		{ // TODO: This doesn't go well for dynamic polymorphic ast node types.
			{ instance.getStringAsMathAst(source) } -> MathAst::MathAstNode;
		}
	;
}