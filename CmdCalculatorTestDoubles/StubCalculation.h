#pragma once

#include "../CmdCalculator/Calculation.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/StringToMathAstConverter.h"
#include "../CmdCalculator/MathAstToExpressionConverter.h"
#include "../CmdCalculator/ExpressionToStringConverter.h"

namespace CmdCalculatorTestDoubles
{
	template
	<
		CmdCalculator::String InputExpressionT,
		CmdCalculator::String OutputExpressionT,
		CmdCalculator::StringView StringViewT,
		CmdCalculator::MathAst::MathAstNode RootMathAstNodeT,
		CmdCalculator::Expressions::Expression ExpressionT,
		class StringToMathAstConverterT,
		class MathAstToExpressionConverterT,
		class ExpressionToStringConverterT
	> requires
		CmdCalculator::StringToMathAstConverter<StringToMathAstConverterT, StringViewT>
		&& CmdCalculator::MathAstToExpressionConverter<MathAstToExpressionConverterT, RootMathAstNodeT>
		&& CmdCalculator::ExpressionToStringConverter<ExpressionToStringConverterT, ExpressionT>
	struct StubCalculation_TParams
	{
		using InputExpressionType = InputExpressionT;
		using OutputExpressionType = OutputExpressionT;
		using StringViewType = StringViewT;
		using RootMathAstNodeType = RootMathAstNodeT;
		using ExpressionType = ExpressionT;
		using StringToMathAstConverterType = StringToMathAstConverterT;
		using MathAstToExpressionConverterType = MathAstToExpressionConverterT;
		using ExpressionToStringConverterType = ExpressionToStringConverterT;
	};

	template<class T>
		requires std::derived_from
		<
			T,
			StubCalculation_TParams
			<
				typename T::InputExpressionType,
				typename T::OutputExpressionType,
				typename T::StringViewType,
				typename T::RootMathAstNodeType,
				typename T::ExpressionType,
				typename T::StringToMathAstConverterType,
				typename T::MathAstToExpressionConverterType,
				typename T::ExpressionToStringConverterType
			>
		>
	struct StubCalculation :
		public CmdCalculator::Calculation_IntendedSatisfaction
	{
		using StringViewType = typename T::StringViewType;
		using RootMathAstNodeType = typename T::RootMathAstNodeType;
		using ExpressionType = typename T::ExpressionType;


		typename T::InputExpressionType inputExpression;
		typename T::OutputExpressionType outputExpression;
		CmdCalculator::CalculationConfiguration configuration;

		typename T::StringToMathAstConverterType stringToMathAstConverter;
		typename T::MathAstToExpressionConverterType mathAstToExpressionConverter;
		typename T::ExpressionToStringConverterType expressionToStringConverter;


		typename T::InputExpressionType getInputExpression() const
		{
			return inputExpression;
		}


		typename T::OutputExpressionType getOutputExpression() const
		{
			return outputExpression;
		}


		CmdCalculator::CalculationConfiguration getConfiguration() const
		{
			return configuration;
		}


		typename T::StringToMathAstConverterType getStringToMathAstConverter() const
		{
			return stringToMathAstConverter;
		}


		typename T::MathAstToExpressionConverterType getMathAstToExpressionConverter() const
		{
			return mathAstToExpressionConverter;
		}


		typename T::ExpressionToStringConverterType getExpressionToStringConverter() const
		{
			return expressionToStringConverter;
		}
	};
}