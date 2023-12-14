#pragma once

#include<concepts>

#include "MathAstNode.h"
#include "Expression.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref MathAstToExpressionConverter concept.
	struct MathAstToExpressionConverter_IntendedSatisfaction
	{};


	/// \brief A type that converts mathematical abstract syntax trees into mathematical expressions.
	/// \tparam T The converter type.
	/// \tparam RootMathAstNodeT The type of the root node of a mathematical AST to be converted into an expression.
	template<class T, class RootMathAstNodeT>
	concept MathAstToExpressionConverter =
		std::derived_from<T, MathAstToExpressionConverter_IntendedSatisfaction>
		&& MathAst::MathAstNode<RootMathAstNodeT>
		&& requires(T&& instance, RootMathAstNodeT sourceRootNode)
	{
		{ instance.getMathAstAsExpression(sourceRootNode) } -> Expressions::Expression;
	}
	;
}