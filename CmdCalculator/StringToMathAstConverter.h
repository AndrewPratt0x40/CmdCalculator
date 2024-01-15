#pragma once

#include<concepts>

#include "strings.h"
#include "utilities.h"
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
		IntendsToSatisfy<T, StringToMathAstConverter_IntendedSatisfaction>
		&& StringView<typename T::StringViewType>
		// axiom(T&& instance, typename T::StringViewType source) { instance.getStringAsMathAst(source); }
		&& requires(T&& instance, typename T::StringViewType source)
		{
			{ instance.getStringAsMathAst(source) } -> UniquePtr;
			MathAst::MathAstNode<SmartPointedToType<decltype(instance.getStringAsMathAst(source))>>;
		}
	;
}