#pragma once

#include <concepts>
#include <string>
#include <functional>

#include "../CmdCalculator/DynamicMathAstToDynamicExpressionConverter.h"
#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/DynamicExpressionBox.h"
#include "StubTrackingDynamicExpression.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::MathAst::MathAstNode RootMathAstNodeT, CmdCalculator::Arithmetic::RealNumber NumberT>
	struct StubTrackingDynamicMathAstToDynamicExpressionConverter :
		public CmdCalculator::DynamicMathAstToDynamicExpressionConverter_IntendedSatisfaction,
		public CmdCalculator::MathAstToExpressionConverter_IntendedSatisfaction
	{
		using NumberType = NumberT;
		using RootMathAstNodeType = RootMathAstNodeT;
		using BoxedExpressionType = Expressions::StubTrackingDynamicExpression
		<
			NumberType,
			std::string
		>;
		using ExpressionType = CmdCalculator::Expressions::DynamicExpressionBox
		<
			BoxedExpressionType
		>;

		std::function<std::string(const RootMathAstNodeT&)> sourceRootNodeFunc;
		
		//bool convertedIsSimplifiableValue;
		NumberType convertedEvaluation;

		ExpressionType getMathAstAsExpression(const RootMathAstNodeT& sourceRootNode) const
		{
			return ExpressionType
			{
				std::move
				(
					std::make_unique<BoxedExpressionType>(sourceRootNodeFunc(sourceRootNode), convertedEvaluation)
				)
			};
		}
	};
}