#pragma once

#include <string>
#include <string_view>
#include <utility>

#include "Calculation.h"
#include "strings.h"
#include "StringToMathAstConverter.h"
#include "MathAstToExpressionConverter.h"
#include "ExpressionToStringConverter.h"
#include "NotImplementedException.h"

namespace CmdCalculator
{
	/// \brief A simple implementation that satisfies the \ref Calculation concept.
	/// \tparam InputExpressionT The type of the expression to be calculated.
	/// \tparam StringToMathAstConverter The type of the object to convert the string representation of the expression to be calculated into a mathematical abstract syntax tree.
	/// \tparam MathAstToExpressionConverter The type of the object to convert the mathematical abstract syntax tree representation of the expression to be calculated into an expression object.
	/// \tparam ExpressionToStringConverter The type of the object to convert the expression object to be calculated into a string.
	template
	<
		String InputExpressionT,
		StringToMathAstConverter StringToMathAstConverterT,
		MathAstToExpressionConverter MathAstToExpressionConverterT,
		ExpressionToStringConverter ExpressionToStringConverterT
	>
	class SimpleCalculation :
		public Calculation_IntendedSatisfaction
	{
	public:
		
		using InputExpressionType = InputExpressionT;
		using StringToMathAstConverterType = StringToMathAstConverterT;
		using MathAstToExpressionConverterType = MathAstToExpressionConverterT;
		using ExpressionToStringConverterType = ExpressionToStringConverterT;

		using OutputExpressionType =
			decltype
			(
				std::declval<ExpressionToStringConverterType>()
				.stringifyExpression
				(
					std::declval<typename ExpressionToStringConverterType::ExpressionType>(),
					std::declval<CalculationConfiguration>()
				)
			)
		;


	private:
		const InputExpressionType m_inputExpression;
		const CalculationConfiguration m_configuration;
		StringToMathAstConverterType m_stringToMathAstConverter;
		MathAstToExpressionConverterType m_mathAstToExpressionConverter;
		ExpressionToStringConverterType m_expressionToStringConverter;


	public:

		/// \brief Accessor to the expression to be calculated.
		/// \returns The expression to be calculated represented as a string.
		InputExpressionType getInputExpression() const
		{
			return m_inputExpression;
		}


		/// \brief Accessor to the calculated expression.
		/// \returns The calculated expression as a string.
		OutputExpressionType getOutputExpression() const
		{
			return m_expressionToStringConverter.stringifyExpression
			(
				m_mathAstToExpressionConverter.getMathAstAsExpression
				(
					m_stringToMathAstConverter.getStringAsMathAst(m_inputExpression)
				).getFullSimplification(),
				m_configuration
			);
		}


		/// \brief Accessor to the calculation configuration object.
		/// \returns The calculation configuration object to use.
		CalculationConfiguration getConfiguration() const
		{
			return m_configuration;
		}


		/// \brief Accessor to the object responsible for converting strings to mathematical abstract syntax trees.
		/// \returns The converter object to use.
		StringToMathAstConverterType getStringToMathAstConverter() const
		{
			return m_stringToMathAstConverter;
		}


		/// \brief Accessor to the object responsible for converting mathematical abstract syntax trees to expression objects.
		/// \returns The converter object to use.
		MathAstToExpressionConverterType getMathAstToExpressionConverter() const
		{
			return m_mathAstToExpressionConverter;
		}


		/// \brief Accessor to the object responsible for converting expression objects to strings.
		/// \returns The converter object to use.
		ExpressionToStringConverterType getExpressionToStringConverter() const
		{
			return m_expressionToStringConverter;
		}


		/// \brief Creates a new instance of the \ref SimpleCalculation class.
		/// \param inputExpression The expression to be calculated.
		/// \param calculationConfiguration The calculation configuration object to use.
		/// \param stringToMathAstConverter The object to use for converting strings to mathematical abstract syntax trees.
		/// \param mathAstToExpressionConverter The object to use for converting mathematical abstract syntax trees to expression objects.
		/// \param expressionToStringConverter The object to use for converting expression objects to strings.
		SimpleCalculation
		(
			InputExpressionType inputExpression,
			CalculationConfiguration calculationConfiguration,
			StringToMathAstConverterType stringToMathAstConverter,
			MathAstToExpressionConverterType mathAstToExpressionConverter,
			ExpressionToStringConverterType expressionToStringConverter
		) :
			m_inputExpression{ inputExpression },
			m_configuration{ calculationConfiguration },
			m_stringToMathAstConverter{ stringToMathAstConverter },
			m_mathAstToExpressionConverter{ mathAstToExpressionConverter },
			m_expressionToStringConverter{ expressionToStringConverter }
		{}
	};
}