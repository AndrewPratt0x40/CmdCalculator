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
		requires(T&& instance)
		{
			StringView<typename T::StringViewType>;
			MathAst::MathAstNode<typename T::RootMathAstNodeType>;
			Expressions::Expression<typename T::ExpressionType>;

			//{ instance.getInputExpression() } -> String;
			instance.getInputExpression();
			{ instance.getOutputExpression() } -> String;
			{ instance.getConfiguration() } -> std::same_as<CalculationConfiguration>;

			{ instance.getStringToMathAstConverter() } -> StringToMathAstConverter<typename T::StringViewType>;
			{ instance.getMathAstToExpressionConverter() } -> MathAstToExpressionConverter<typename T::RootMathAstNodeType>;
			{ instance.getExpressionToStringConverter() } -> ExpressionToStringConverter<typename T::ExpressionType>;
		}
	;
}