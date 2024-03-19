#pragma once

#include <string>
#include <concepts>
#include <ranges>

#include "strings.h"
#include "utilities.h"
#include "MathAstNode.h"


namespace CmdCalculator::MathAst
{
	/// \brief The base type for types that are intended to satisfy the \ref ExpressionPartNode concept.
	struct ExpressionPartNode_IntendedSatisfaction :
		public MathAstNode_IntendedSatisfaction
	{};


	/// \brief A single node in an abstract syntax tree (AST) representing a mathematical expression.
	/// \tparam T The type of the AST node.
	template<class T>
	concept ExpressionPartNode =
		IntendsToSatisfy<T, ExpressionPartNode_IntendedSatisfaction>
		&& MathAstNode<T>
	;
}