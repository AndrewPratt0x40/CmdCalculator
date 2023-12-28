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
	// TODO: Unit test
	template
	<
		CmdCalculator::String InputExpressionT,
		CmdCalculator::StringToMathAstConverter StringToMathAstConverterT,
		CmdCalculator::MathAstToExpressionConverter MathAstToExpressionConverterT,
		CmdCalculator::ExpressionToStringConverter ExpressionToStringConverterT
	>
	class FakeCalculation :
		public CmdCalculator::Calculation_IntendedSatisfaction
	{
	public:
		using InputExpressionType = InputExpressionT;
		using StringToMathAstConverterType = StringToMathAstConverterT;
		using MathAstToExpressionConverterType =MathAstToExpressionConverterT;
		using ExpressionToStringConverterType = ExpressionToStringConverterT;

	private:
		InputExpressionType m_inputExpression;
		CmdCalculator::CalculationConfiguration m_configuration;
		StringToMathAstConverterType m_stringToMathAstConverter;
		MathAstToExpressionConverterType m_mathAstToExpressionConverter;
		ExpressionToStringConverterType m_expressionToStringConverter;

	public:
		
		InputExpressionType getInputExpression() const
		{
			return m_inputExpression;
		}


		auto getOutputExpression() const
		{
			const auto mathAst
			{
				m_stringToMathAstConverter.getStringAsMathAst
				(
					static_cast<std::basic_string_view<typename InputExpressionType::value_type>>(m_inputExpression)
				)
			};

			const auto expression
			{
				m_mathAstToExpressionConverter.getMathAstAsExpression(mathAst)
			};

			return m_expressionToStringConverter.stringifyExpression(expression);
		}


		CmdCalculator::CalculationConfiguration getConfiguration() const
		{
			return m_configuration;
		}


		StringToMathAstConverterType getStringToMathAstConverter() const
		{
			return m_stringToMathAstConverter;
		}


		MathAstToExpressionConverterType getMathAstToExpressionConverter() const
		{
			return m_mathAstToExpressionConverter;
		}


		ExpressionToStringConverterType getExpressionToStringConverter() const
		{
			return m_expressionToStringConverter;
		}


		FakeCalculation
		(
			InputExpressionType inputExpression,
			CmdCalculator::CalculationConfiguration configuration,
			StringToMathAstConverterType stringToMathAstConverter,
			MathAstToExpressionConverterType mathAstToExpressionConverter,
			ExpressionToStringConverterType expressionToStringConverter
		) :
			m_inputExpression{ inputExpression },
			m_configuration{ configuration },
			m_stringToMathAstConverter{ stringToMathAstConverter },
			m_mathAstToExpressionConverter{ mathAstToExpressionConverter },
			m_expressionToStringConverter{ expressionToStringConverter }
		{}
	};
}