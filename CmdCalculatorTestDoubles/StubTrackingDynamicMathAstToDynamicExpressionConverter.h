#pragma once

#include <concepts>
#include <string>
#include <functional>
#include <variant>

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
		using ConvertedEvaluationCalcFuncType = std::function<NumberType(const RootMathAstNodeT&)>;

		std::function<std::string(const RootMathAstNodeT&)> sourceRootNodeFunc;
		
		//bool convertedIsSimplifiableValue;
		std::variant<NumberType, ConvertedEvaluationCalcFuncType> convertedEvaluation;

		ExpressionType getMathAstAsExpression(const RootMathAstNodeT& sourceRootNode) const
		{
			NumberType eval;
			if (const NumberType* evalPtr = std::get_if<NumberType>(&convertedEvaluation); evalPtr)
				eval = *evalPtr;
			else
			{
				eval = std::get<ConvertedEvaluationCalcFuncType>(convertedEvaluation)(sourceRootNode);
			}

			return ExpressionType
			{
				std::move
				(
					std::make_unique<BoxedExpressionType>(sourceRootNodeFunc(sourceRootNode), eval)
				)
			};
		}
	};
}