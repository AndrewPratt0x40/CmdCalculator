#pragma once

#include "../CmdCalculator/MathAstToExpressionConverter.h"
#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/Expression.h"
#include "StubTrackingExpression.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::MathAst::MathAstNode RootMathAstNodeT>
	struct StubTrackingMathAstToExpressionConverter :
		public CmdCalculator::MathAstToExpressionConverter_IntendedSatisfaction
	{
		using RootMathAstNodeType = RootMathAstNodeT;
		using ExpressionType = Expressions::StubTrackingExpression<RootMathAstNodeType>;

		bool convertedIsSimplifiableValue;
		

		ExpressionType getMathAstAsExpression(const RootMathAstNodeT& sourceRootNode) const
		{
			return ExpressionType
			{
				.mathAstSource{ sourceRootNode },
				.wasSimplified{ false },
				.isSimplifiableValue{ convertedIsSimplifiableValue }
			};
		}
	};
}