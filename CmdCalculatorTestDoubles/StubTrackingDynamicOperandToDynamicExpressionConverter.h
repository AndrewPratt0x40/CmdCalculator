#pragma once

#include <concepts>
#include <memory>

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

		ExpressionNumberType convertedOperandEvaluation;


		std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<ExpressionNumberType>> getOperandAsExpression
			(const CmdCalculator::MathAst::DynamicOperandNode<MathAstStringType>& sourceOperand) const
		{
			return 
				std::make_unique
				<
					CmdCalculatorTestDoubles::Expressions::StubTrackingDynamicExpression
					<
						ExpressionNumberType,
						CmdCalculator::MathAst::DynamicOperandNode<MathAstStringType>
					>
				>
				(sourceOperand, convertedOperandEvaluation)
			;
		}
	};
}