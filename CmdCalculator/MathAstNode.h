#pragma once

#include <string>
#include <concepts>

#include "strings.h"
#include "utilities.h"


namespace CmdCalculator::MathAst
{
	/// \brief The base type for types that are intended to satisfy the \ref MathAstNode concept.
	struct MathAstNode_IntendedSatisfaction
	{};
	
	
	/// \brief A single node in an abstract syntax tree (AST) representing a mathematical expression.
	/// \tparam T The type of the AST node.
	template<class T>
	concept MathAstNode =
		IntendsToSatisfy<T, MathAstNode_IntendedSatisfaction>
		&& String<typename T::StringType>
		&& requires(T&& instance)
		{
			{ instance.getLeadingTrivia() } -> std::same_as<typename T::StringType>;
			{ instance.getTrailingTrivia() } -> std::same_as<typename T::StringType>;
			{ instance.getStringRepresentation() } -> std::same_as<typename T::StringType>;
		}
	;
}