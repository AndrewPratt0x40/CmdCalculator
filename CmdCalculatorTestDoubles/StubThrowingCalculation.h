#pragma once

#include "StubCalculation.h"
#include "../CmdCalculator/Calculation.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/StringToMathAstConverter.h"
#include "../CmdCalculator/MathAstToExpressionConverter.h"
#include "../CmdCalculator/ExpressionToStringConverter.h"

namespace CmdCalculatorTestDoubles
{
	template<class T, class ExceptionT>
		requires std::derived_from
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
	struct StubThrowingCalculation :
		public ::CmdCalculator::Calculation_IntendedSatisfaction
	{
		using InputExpressionType = T::InputExpressionType;
		using StringToMathAstConverterType = T::StringToMathAstConverterType;
		using MathAstToExpressionConverterType = T::MathAstToExpressionConverterType;
		using ExpressionToStringConverterType = T::ExpressionToStringConverterType;
			
		ExceptionT exceptionToThrow;

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
			throw exceptionToThrow;
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


		StubThrowingCalculation
		(
			typename T::InputExpressionType inputExpression,
			::CmdCalculator::CalculationConfiguration configuration,
			typename T::StringToMathAstConverterType stringToMathAstConverter,
			typename T::MathAstToExpressionConverterType mathAstToExpressionConverter,
			typename T::ExpressionToStringConverterType expressionToStringConverter
		) :
			inputExpression{ inputExpression },
			outputExpression{},
			configuration{ configuration },
			stringToMathAstConverter{ stringToMathAstConverter },
			mathAstToExpressionConverter{ mathAstToExpressionConverter },
			expressionToStringConverter{ expressionToStringConverter }
		{}
	};
}