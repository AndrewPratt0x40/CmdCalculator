#pragma once

#include "strings.h"
#include "CalculationConfiguration.h"
#include "StringToMathAstConverter.h"
#include "MathAstToExpressionConverter.h"
#include "ExpressionToStringConverter.h"
#include "MathAstNode.h"
#include "Expression.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref Calculation concept.
	struct Calculation_IntendedSatisfaction
	{};


	/// \brief A singular calculation.
	/// \tparam T The type of the calculation object.
	template<class T>
	concept Calculation =
		String<typename T::InputExpressionType>
		&& StringToMathAstConverter<typename T::StringToMathAstConverterType>
		&& MathAstToExpressionConverter<typename T::MathAstToExpressionConverterType>
		&& ExpressionToStringConverter<typename T::ExpressionToStringConverterType>
		&& std::constructible_from
		<
			T,
			typename T::InputExpressionType,
			CalculationConfiguration,
			typename T::StringToMathAstConverterType,
			typename T::MathAstToExpressionConverterType,
			typename T::ExpressionToStringConverterType
		>
		&& requires(T&& instance)
		{
			{ instance.getInputExpression() } -> String;
			{ instance.getOutputExpression() } -> String;
			{ instance.getConfiguration() } -> std::same_as<CalculationConfiguration>;

			{ instance.getStringToMathAstConverter() } -> StringToMathAstConverter;
			{ instance.getMathAstToExpressionConverter() } -> MathAstToExpressionConverter;
			{ instance.getExpressionToStringConverter() } -> ExpressionToStringConverter;
		}
	;
}