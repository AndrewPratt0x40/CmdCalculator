#include "pch.h"

#include <string>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/DynamicExpressionBox.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"

namespace CmdCalculatorTests
{
#pragma region Concept satisfaction

	TEST(DynamicExpressionBoxTests, DynamicExpressionBox$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculator::Expressions::DynamicExpressionBox
				<
					CmdCalculator::Expressions::DynamicExpression<CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber>
				>
			>
		);
	}

#pragma endregion


#pragma region getEvaluation

	class DynamicExpressionBoxgetEvaluationTests :
		public testing::TestWithParam<double>
	{};

	const auto DynamicExpressionBoxgetEvaluation_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::numbers()
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicExpressionBoxTests,
		DynamicExpressionBoxgetEvaluationTests,
		CmdCalculatorTestUtils::ValuesInRange(DynamicExpressionBoxgetEvaluation_TestDataValues)
	);

	TEST_P(DynamicExpressionBoxgetEvaluationTests, getEvaluation$returns$evaluation$of$inner$value)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using InnerType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;
		const double expectedEvaluation{ GetParam() };
		const CmdCalculator::Expressions::DynamicExpressionBox<InnerType> instance
		{
			std::move
			(
				std::make_unique<InnerType>(NumberType{ GetParam() })
			)
		};

		// Act
		const double actualEvaluation{ instance.getEvaluation().FAKE_getValue() };

		// Assert
		EXPECT_EQ(expectedEvaluation, actualEvaluation);
	}

#pragma endregion
}