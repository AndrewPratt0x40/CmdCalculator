#pragma once

#include <functional>
#include <concepts>
#include <optional>
#include <memory>
#include <string>
#include <format>
#include <iostream>

#include "../CmdCalculator/RecursiveSplitResultToDynamicExpressionConverter.h"
#include "../CmdCalculator/DynamicExpressionPartRecursiveSplitResult.h"
#include "../CmdCalculator/RealNumber.h"
#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/strings.h"
#include "StubTrackingDynamicExpression.h"


using namespace std::string_literals;


namespace CmdCalculatorTestDoubles
{
	template
	<
		CmdCalculator::DynamicExpressionPartRecursiveSplitResult SourceSplitResultT,
		CmdCalculator::Arithmetic::RealNumber ExpressionNumberT
	>
	struct StubTrackingRecursiveSplitResultToDynamicExpressionConverter :
		public CmdCalculator::RecursiveSplitResultToDynamicExpressionConverter_IntendedSatisfaction
	{
		using SourceSplitResultType = SourceSplitResultT;
		using ExpressionNumberType = ExpressionNumberT;
		using MathAstStringType = SourceSplitResultType::MathAstStringType;
		using ConvertedSplitResultType = CmdCalculatorTestDoubles::Expressions::StubTrackingDynamicExpression
		<
			ExpressionNumberType,
			SourceSplitResultType
		>;


		ExpressionNumberType convertedSplitResultEvaluation;


		std::unique_ptr<ConvertedSplitResultType> getSplitResultAsExpression
			(const SourceSplitResultType& sourceSplitResult) const
		{
			return std::make_unique<ConvertedSplitResultType>(sourceSplitResult, convertedSplitResultEvaluation);
		}
	};
}