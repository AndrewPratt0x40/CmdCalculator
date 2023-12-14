#pragma once

#include<concepts>

#include "strings.h"
#include "MathAstNode.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref StringToMathConverter concept.
	struct StringToMathConverter_IntendedSatisfaction
	{};


	/// \brief A type that parses strings into mathematical abstract syntax trees.
	/// \tparam T The converter type.
	/// \tparam StringViewT The string type to be converted into an AST.
	template<class T, class StringViewT>
	concept StringToMathConverter =
		std::derived_from<T, StringToMathConverter_IntendedSatisfaction>
		&& StringView<StringViewT>
		&& requires(T&& instance, StringViewT source)
		{
			{ instance.getStringAsMathAst(source) } -> MathAst::MathAstNode;
		}
	;
}