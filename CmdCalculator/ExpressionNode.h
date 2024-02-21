#pragma once

#include <string>
#include <concepts>
#include <ranges>

#include "strings.h"
#include "utilities.h"
#include "MathAstNode.h"
#include "ExpressionPartNode.h"


namespace CmdCalculator::MathAst
{
	/// \brief The base type for types that are intended to satisfy the \ref ExpressionNode concept.
	struct ExpressionNode_IntendedSatisfaction :
		public MathAstNode_IntendedSatisfaction
	{};


	/// \brief A single node in an abstract syntax tree (AST) representing a mathematical expression.
	/// \tparam T The type of the AST node.
	template<class T>
	concept ExpressionNode =
		IntendsToSatisfy<T, ExpressionNode_IntendedSatisfaction>
		&& MathAstNode<T>
		&& requires(T&& instance)
		{
			{ instance.getParts() } -> std::ranges::forward_range;
			ExpressionPartNode<std::ranges::range_value_t<decltype(instance.getParts())>>;
		}
	;
}