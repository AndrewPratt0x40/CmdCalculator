#pragma once

#include <concepts>
#include <memory>
#include <functional>

#include "../CmdCalculator/DynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculator/RealNumber.h"
#include "../CmdCalculator/DynamicOperandNode.h"
#include "../CmdCalculator/DynamicExpression.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicExpression.h"


namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::String MathAstStringT, CmdCalculator::Arithmetic::RealNumber ExpressionNumberT>
	struct StubTrackingDynamicOperandToDynamicExpressionConverter :
		public CmdCalculator::DynamicOperandToDynamicExpressionConverter_IntendedSatisfaction
	{
		using MathAstStringType = MathAstStringT;
		using ExpressionNumberType = ExpressionNumberT;
		using ExpressionType = CmdCalculatorTestDoubles::Expressions::StubTrackingDynamicExpression
		<
			ExpressionNumberType,
			std::reference_wrapper<const CmdCalculator::MathAst::DynamicOperandNode<MathAstStringType>>
		>;

		ExpressionNumberType convertedOperandEvaluation;


		std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<ExpressionNumberType>> getOperandAsExpression
			(const CmdCalculator::MathAst::DynamicOperandNode<MathAstStringType>& sourceOperand) const
		{
			return std::make_unique<ExpressionType>(std::ref(sourceOperand), convertedOperandEvaluation);
		}
	};
}