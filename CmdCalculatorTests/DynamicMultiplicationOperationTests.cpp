#include "pch.h"

#include <string>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/DynamicMultiplicationOperation.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTests
{
#pragma region Concept satisfaction

	TEST(DynamicMultiplicationOperationTests, DynamicMultiplicationOperation$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculator::Expressions::DynamicMultiplicationOperation
				<
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion


#pragma region Test data setup

	struct DynamicMultiplicationOperation_TestData
	{
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using OperandType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		OperandType multiplier;
		OperandType multiplicand;
		double expectedMultiplierEvaluation;
		double expectedMultiplicandEvaluation;
		double expectedEvaluation;

		DynamicMultiplicationOperation_TestData(const double multiplier, const double multiplicand, const double evaluation) :
			multiplier{ DynamicMultiplicationOperation_TestData::NumberType{ multiplier } },
			multiplicand{ DynamicMultiplicationOperation_TestData::NumberType{ multiplicand } },
			expectedMultiplierEvaluation{ multiplier },
			expectedMultiplicandEvaluation{ multiplicand },
			expectedEvaluation{ evaluation }
		{}


		friend std::ostream& operator<<(std::ostream & ostream, const DynamicMultiplicationOperation_TestData & testData)
		{
			ostream
				<< '['
				<< testData.multiplier.evaluation.FAKE_getValue()
				<< " * "
				<< testData.multiplicand.evaluation.FAKE_getValue()
				<< " == {"
				<< testData.expectedMultiplierEvaluation
				<< '+'
				<< testData.expectedMultiplicandEvaluation
				<< "*"
				<< testData.expectedEvaluation
				<< "}]"
			;

			return ostream;
		}
	};

	class DynamicMultiplicationOperationWithTestDataTests :
		public testing::TestWithParam<DynamicMultiplicationOperation_TestData>
	{};

	const auto DynamicMultiplicationOperation_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::multiplicationOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return DynamicMultiplicationOperation_TestData
				{
					data.leftOperand,
					data.rightOperand,
					data.result
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicMultiplicationOperationTests,
		DynamicMultiplicationOperationWithTestDataTests,
		CmdCalculatorTestUtils::ValuesInRange(DynamicMultiplicationOperation_TestDataValues)
	);

#pragma endregion


#pragma region Expected state

	TEST_P(DynamicMultiplicationOperationWithTestDataTests, DynamicMultiplicationOperation$has$expected$state)
	{
		// Arrange
		using NumberType = DynamicMultiplicationOperation_TestData::NumberType;
		using OperandType = DynamicMultiplicationOperation_TestData::OperandType;

		auto multiplierToPass{ std::make_unique<OperandType>(GetParam().multiplier) };
		auto multiplicandToPass{ std::make_unique<OperandType>(GetParam().multiplicand) };

		const double expectedMultiplierEvaluation{ GetParam().expectedMultiplierEvaluation };
		const double expectedMultiplicandEvaluation{ GetParam().expectedMultiplicandEvaluation };
		const double expectedEvaluation{ GetParam().expectedEvaluation };
		
		// Act
		CmdCalculator::Expressions::DynamicMultiplicationOperation<NumberType> instance
		{
			std::move(multiplierToPass),
			std::move(multiplicandToPass)
		};

		// Assert
		EXPECT_DOUBLE_EQ(expectedMultiplierEvaluation, instance.getMultiplier().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedMultiplicandEvaluation, instance.getMultiplicand().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedEvaluation, instance.getEvaluation().FAKE_getValue());
	}

#pragma endregion
}