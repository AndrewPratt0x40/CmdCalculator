#pragma once

#include <concepts>
#include <memory>
#include <variant>

#include "../CmdCalculator/DynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculator/RealNumber.h"
#include "../CmdCalculator/DynamicOperandNode.h"
#include "../CmdCalculator/DynamicExpression.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"


namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::String MathAstStringT, CmdCalculator::Arithmetic::RealNumber ExpressionNumberT>
	struct StubDynamicOperandToDynamicExpressionConverter :
		public CmdCalculator::DynamicOperandToDynamicExpressionConverter_IntendedSatisfaction
	{
		using MathAstStringType = MathAstStringT;
		using ExpressionNumberType = ExpressionNumberT;
		using ConvertedOperandEvaluationCalcFuncType = std::function<ExpressionNumberType(const CmdCalculator::MathAst::DynamicOperandNode<MathAstStringType>&)>;

		std::variant<ExpressionNumberType, ConvertedOperandEvaluationCalcFuncType> convertedOperandEvaluation;


		std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<ExpressionNumberType>> getOperandAsExpression
			(const CmdCalculator::MathAst::DynamicOperandNode<MathAstStringType>& sourceOperand) const
		{
			ExpressionNumberType eval;
			if (const ExpressionNumberType* evalPtr = std::get_if<ExpressionNumberType>(&convertedOperandEvaluation); evalPtr)
				eval = *evalPtr;
			else
			{
				eval = std::get<ConvertedOperandEvaluationCalcFuncType>(convertedOperandEvaluation)(sourceOperand);
			}

			return std::make_unique<CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<ExpressionNumberType>>
				(eval)
			;
		}
	};
}