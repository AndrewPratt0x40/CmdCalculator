#pragma once

#include <concepts>
#include <memory>

#include "../CmdCalculator/DynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculator/RealNumber.h"
#include "../CmdCalculator/DynamicOperandNode.h"
#include "../CmdCalculator/DynamicExpression.h"
#include "../CmdCalculator/strings.h"


namespace CmdCalculatorTestDoubles
{
	template<class T>
	concept DynamicExpressionFor_StubDynamicOperandToDynamicExpressionConverter =
		std::convertible_to
		<
			std::unique_ptr<T>,
			std::unique_ptr
			<
				::CmdCalculator::Expressions::DynamicExpression
				<
					typename T::NumberType
				>
			>
		>
	;


	template
	<
		::CmdCalculator::String MathAstStringT,
		DynamicExpressionFor_StubDynamicOperandToDynamicExpressionConverter ExpressionT
	>
	struct StubDynamicOperandToDynamicExpressionConverter :
		public ::CmdCalculator::DynamicOperandToDynamicExpressionConverter_IntendedSatisfaction
	{
		using MathAstStringType = MathAstStringT;
		using ExpressionType = ExpressionT;
		using ExpressionNumberType = ExpressionType::NumberType;

		ExpressionType convertedOperand;


		::CmdCalculator::Expressions::DynamicExpression<ExpressionNumberType> getOperandAsExpression
			(const ::CmdCalculator::MathAst::DynamicOperandNode<MathAstStringType>& sourceOperand) const
		{
			return std::make_unique<ExpressionType>
				(convertedOperand)
			;
		}
	};
}