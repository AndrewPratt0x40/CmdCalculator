#pragma once

#include "../CmdCalculator/MathAstToExpressionConverter.h"
#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/Expression.h"
#include "StubTrackingExpression.h"
#include "FakeRealNumber.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::MathAst::MathAstNode RootMathAstNodeT>
	struct StubTrackingMathAstToExpressionConverter :
		public CmdCalculator::MathAstToExpressionConverter_IntendedSatisfaction
	{
		using NumberType = Arithmetic::FakeRealNumber;
		using RootMathAstNodeType = RootMathAstNodeT;
		using ExpressionType = Expressions::StubTrackingExpression
		<
			NumberType,
			RootMathAstNodeType
		>;

		//bool convertedIsSimplifiableValue;
		NumberType convertedEvaluation;

		ExpressionType getMathAstAsExpression(const RootMathAstNodeT& sourceRootNode) const
		{
			return ExpressionType
			{
				.mathAstSource{ sourceRootNode },
				.evaluation{ convertedEvaluation }
				//.wasSimplified{ false },
				//.isSimplifiableValue{ convertedIsSimplifiableValue }
			};
		}
	};
}