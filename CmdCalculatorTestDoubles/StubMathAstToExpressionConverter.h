#pragma once

#include "../CmdCalculator/MathAstToExpressionConverter.h"
#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/Expression.h"

namespace CmdCalculatorTestDoubles
{
	template<::CmdCalculator::MathAst::MathAstNode RootMathAstNodeT, ::CmdCalculator::Expressions::Expression ExpressionT>
	struct StubMathAstToExpressionConverter :
		public ::CmdCalculator::MathAstToExpressionConverter_IntendedSatisfaction
	{
		using RootMathAstNodeType = RootMathAstNodeT;
		using ExpressionType = ExpressionT;

		ExpressionT convertedExpression;

		ExpressionT getMathAstAsExpression(const RootMathAstNodeT& sourceRootNode) const
		{
			return convertedExpression;
		}
	};
}