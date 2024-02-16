#pragma once

#include <memory>

#include "../CmdCalculator/DynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculator/RealNumber.h"
#include "../CmdCalculator/DynamicOperandNode.h"
#include "../CmdCalculator/DynamicExpression.h"
#include "../CmdCalculator/strings.h"


namespace CmdCalculatorTestDoubles
{
	template
	<
		CmdCalculator::String MathAstStringT,
		CmdCalculator::Expressions::Expression ExpressionT
	>
	requires
		std::convertible_to
		<
			std::unique_ptr<ExpressionT>,
			std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<typename ExpressionT::NumberType>>,
		>
		&& std::copyable<ExpressionT>
	struct StubDynamicOperandToDynamicExpressionConverter :
		public CmdCalculator::DynamicOperandToDynamicExpressionConverter_IntendedSatisfaction
	{
		using MathAstStringType = MathAstStringT;
		using ExpressionType = ExpressionT;
		using ExpressionNumberType = ExpressionType::NumberType;

		ExpressionType convertedOperand;


		CmdCalculator::Expressions::DynamicExpression<ExpressionNumberType> getOperandAsExpression
			(const CmdCalculator::MathAst::DynamicOperandNode<MathAstStringType>& sourceOperand) const
		{
			return std::make_unique<CmdCalculator::Expressions::DynamicExpression<ExpressionNumberType>>
				(convertedOperand)
			;
		}
	};
}