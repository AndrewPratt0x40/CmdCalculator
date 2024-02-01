#include "pch.h"

#include <string>
#include <string_view>

#include "../CmdCalculator/BasicCalculation.h"
#include "../CmdCalculatorTestDoubles/StubMathAstNode.h"
#include "../CmdCalculatorTestDoubles/StubTrackingMathAstNode.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"
#include "../CmdCalculatorTestDoubles/StubExpression.h"
#include "../CmdCalculatorTestDoubles/StubTrackingExpression.h"
#include "../CmdCalculatorTestDoubles/StubStringToMathAstConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingStringToMathAstConverter.h"
#include "../CmdCalculatorTestDoubles/StubMathAstToExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingMathAstToExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubExpressionToStringConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingExpressionToStringConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingConvertedString.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/Calculation.h"

namespace CmdCalculatorTests
{
#pragma region Concept satisfaction

	TEST(BasicCalculationTests, BasicCalculation$satisfies$Calculation$concept)
	{
		static_assert
		(
			CmdCalculator::Calculation
			<
				CmdCalculator::BasicCalculation
				<
					std::string,
					CmdCalculatorTestDoubles::StubStringToMathAstConverter
					<
						std::string_view,
						CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>
					>,
					CmdCalculatorTestDoubles::StubMathAstToExpressionConverter
					<
						CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>,
						CmdCalculatorTestDoubles::Expressions::StubExpression<CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber>
					>,
					CmdCalculatorTestDoubles::StubExpressionToStringConverter
					<
						CmdCalculatorTestDoubles::Expressions::StubExpression<CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber>,
						std::string
					>
				>
			>
		);
	}

#pragma endregion


#pragma region Constructor

	TEST(BasicCalculationTests, Constructor$sets$members$correctly)
	{
		// Arrange
		std::string inputExpression{ "2 + 3" };
		CmdCalculator::CalculationConfiguration calculationConfiguration{ 4, false, true, false, true };
		CmdCalculatorTestDoubles::StubStringToMathAstConverter
		<
			std::string_view,
			CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>
		> stringToMathAstConverter{};
		CmdCalculatorTestDoubles::StubMathAstToExpressionConverter
		<
			CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>,
			CmdCalculatorTestDoubles::Expressions::StubExpression<CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber>
		> mathAstToExpressionConverter{};
		CmdCalculatorTestDoubles::StubExpressionToStringConverter
		<
			CmdCalculatorTestDoubles::Expressions::StubExpression<CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber>,
			std::string
		> expressionToStringConverter{};

		CmdCalculator::BasicCalculation
		<
			decltype(inputExpression),
			decltype(stringToMathAstConverter),
			decltype(mathAstToExpressionConverter),
			decltype(expressionToStringConverter)
		> instance
		{
			inputExpression,
			calculationConfiguration,
			stringToMathAstConverter,
			mathAstToExpressionConverter,
			expressionToStringConverter
		};

		// Assert
		EXPECT_EQ(inputExpression, instance.getInputExpression());
		EXPECT_EQ(calculationConfiguration, instance.getConfiguration());
		EXPECT_EQ
		(
			stringToMathAstConverter.convertedString.getStringRepresentation(),
			instance.getStringToMathAstConverter().convertedString.getStringRepresentation()
		);
		EXPECT_EQ
		(
			mathAstToExpressionConverter.convertedExpression.evaluation,
			instance.getMathAstToExpressionConverter().convertedExpression.evaluation
		);
		/*EXPECT_EQ
		(
			mathAstToExpressionConverter.convertedExpression.fullSimplification,
			instance.getMathAstToExpressionConverter().convertedExpression.fullSimplification
		);*/
		EXPECT_EQ
		(
			expressionToStringConverter.stringifiedExpression,
			instance.getExpressionToStringConverter().stringifiedExpression
		);
	}

#pragma endregion


#pragma region Output expression

	TEST(BasicCalculationTests, getOutputExpression$returns$the$result$of$using$converters$and$evaluating$expression)
	{
		// Arrange
		std::string inputExpression{ "Input expression" };
		CmdCalculator::CalculationConfiguration calculationConfiguration{ 4, false, true, false, true };

		using StringToMathAstConverterType = CmdCalculatorTestDoubles::StubTrackingStringToMathAstConverter
		<
			std::string_view,
			std::string
		>;

		using MathAstRootNodeType = StringToMathAstConverterType::MathAstNodeType;

		using MathAstToExpressionConverterType = CmdCalculatorTestDoubles::StubTrackingMathAstToExpressionConverter
		<
			MathAstRootNodeType
		>;

		using ExpressionType = MathAstToExpressionConverterType::ExpressionType;

		using ExpressionToStringConverterType = CmdCalculatorTestDoubles::StubTrackingExpressionToStringConverter
		<
			ExpressionType,
			std::string
		>;

		using ConvertedStringType = ExpressionToStringConverterType::StringType;

		StringToMathAstConverterType stringToMathAstConverter
		{
			.convertedValueLeadingTrivia{},
			.convertedValueTrailingTrivia{},
			.convertedValueStringRepresentation{ "MathAstNode representation" }
		};

		MathAstToExpressionConverterType mathAstToExpressionConverter
		{
			.convertedEvaluation{ 12.34 }
			//.convertedIsSimplifiableValue{true},
		};

		ExpressionToStringConverterType expressionToStringConverter
		{
			.stringifiedExpression{ "Output expression" }
		};

		CmdCalculator::BasicCalculation
		<
			decltype(inputExpression),
			decltype(stringToMathAstConverter),
			decltype(mathAstToExpressionConverter),
			decltype(expressionToStringConverter)
		> instance
		{
			inputExpression,
			calculationConfiguration,
			stringToMathAstConverter,
			mathAstToExpressionConverter,
			expressionToStringConverter
		};

		// Act
		ConvertedStringType returnValue{ instance.getOutputExpression() };

		// Assert
		EXPECT_EQ(returnValue.value, expressionToStringConverter.stringifiedExpression);
		EXPECT_EQ(returnValue.expressionSource.mathAstSource.getStringRepresentation(), stringToMathAstConverter.convertedValueStringRepresentation);
		EXPECT_EQ(returnValue.expressionSource.mathAstSource.stringSource, inputExpression);

		//EXPECT_TRUE(returnValue.expressionSource.wasSimplified);
		//EXPECT_FALSE(returnValue.expressionSource.isSimplifiable());
	}

#pragma endregion
}