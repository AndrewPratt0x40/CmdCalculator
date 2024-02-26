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
	template<class T>
	concept StubCalculationOutputExpressionProvider =
		::CmdCalculator::String<typename T::OutputExpressionType>
		&& requires
		{
			{ T::getOutputExpression() } -> std::same_as<typename T::OutputExpressionType>;
		}
	;


	template
	<
		::CmdCalculator::String InputExpressionT,
		::CmdCalculator::String OutputExpressionT,
		class StringToMathAstConverterT,
		class MathAstToExpressionConverterT,
		class ExpressionToStringConverterT
	> requires
		::CmdCalculator::StringToMathAstConverter<StringToMathAstConverterT>
		&& ::CmdCalculator::MathAstToExpressionConverter<MathAstToExpressionConverterT>
		&& ::CmdCalculator::ExpressionToStringConverter<ExpressionToStringConverterT>
	struct StubCalculation_TParams
	{
		using InputExpressionType = InputExpressionT;
		using OutputExpressionType = OutputExpressionT;
		using StringToMathAstConverterType = StringToMathAstConverterT;
		using MathAstToExpressionConverterType = MathAstToExpressionConverterT;
		using ExpressionToStringConverterType = ExpressionToStringConverterT;
	};

	template<class T, StubCalculationOutputExpressionProvider OutputExpressionProviderT>
		requires std::convertible_to<typename T::OutputExpressionType, typename OutputExpressionProviderT::OutputExpressionType>
		&& std::derived_from
		<
			T,
			StubCalculation_TParams
			<
				typename T::InputExpressionType,
				typename T::OutputExpressionType,
				typename T::StringToMathAstConverterType,
				typename T::MathAstToExpressionConverterType,
				typename T::ExpressionToStringConverterType
			>
		>
	struct StubCalculation :
		public ::CmdCalculator::Calculation_IntendedSatisfaction
	{
		using InputExpressionType = T::InputExpressionType;
		using StringToMathAstConverterType = T::StringToMathAstConverterType;
		using MathAstToExpressionConverterType = T::MathAstToExpressionConverterType;
		using ExpressionToStringConverterType = T::ExpressionToStringConverterType;
		
		typename T::InputExpressionType inputExpression;
		typename T::OutputExpressionType outputExpression;
		::CmdCalculator::CalculationConfiguration configuration;

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


		::CmdCalculator::CalculationConfiguration getConfiguration() const
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


		StubCalculation
		(
			typename T::InputExpressionType inputExpression,
			::CmdCalculator::CalculationConfiguration configuration,
			typename T::StringToMathAstConverterType stringToMathAstConverter,
			typename T::MathAstToExpressionConverterType mathAstToExpressionConverter,
			typename T::ExpressionToStringConverterType expressionToStringConverter
		) :
			inputExpression{ inputExpression },
			outputExpression{ OutputExpressionProviderT::getOutputExpression() },
			configuration{ configuration },
			stringToMathAstConverter{ stringToMathAstConverter },
			mathAstToExpressionConverter{ mathAstToExpressionConverter },
			expressionToStringConverter{ expressionToStringConverter }
		{}
	};
}