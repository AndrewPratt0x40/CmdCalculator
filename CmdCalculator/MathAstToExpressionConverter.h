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
	template<class T>
	concept MathAstToExpressionConverter =
		std::derived_from<T, MathAstToExpressionConverter_IntendedSatisfaction>
		&& MathAst::MathAstNode<typename T::RootMathAstNodeType>
		&& requires(T&& instance, const typename T::RootMathAstNodeType& sourceRootNode)
	{
		{ instance.getMathAstAsExpression(sourceRootNode) } -> Expressions::Expression;
	}
	;
}