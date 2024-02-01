#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicMultiplicationOperation.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTestDoubleTests
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
	};

	class DynamicMultiplicationOperationWithTestDataTests :
		public testing::TestWithParam<DynamicMultiplicationOperation_TestData>
	{};

	const DynamicMultiplicationOperation_TestData DynamicMultiplicationOperation_TestDataValues[]
	{
		{
			.multiplier{ DynamicMultiplicationOperation_TestData::NumberType{ 0.0 } },
			.multiplicand{ DynamicMultiplicationOperation_TestData::NumberType{ 0.0 } },
			.expectedMultiplierEvaluation{ 0.0 },
			.expectedMultiplicandEvaluation{ 0.0 },
			.expectedEvaluation{ 0.0 }
		},
		{
			.multiplier{ DynamicMultiplicationOperation_TestData::NumberType{ 1.0 } },
			.multiplicand{ DynamicMultiplicationOperation_TestData::NumberType{ 1.0 } },
			.expectedMultiplierEvaluation{ 1.0 },
			.expectedMultiplicandEvaluation{ 1.0 },
			.expectedEvaluation{ 1.0 }
		},
		{
			.multiplier{ DynamicMultiplicationOperation_TestData::NumberType{ 12.34 } },
			.multiplicand{ DynamicMultiplicationOperation_TestData::NumberType{ 56.78 } },
			.expectedMultiplierEvaluation{ 12.34 },
			.expectedMultiplicandEvaluation{ 56.78 },
			.expectedEvaluation{ 700.6652 }
		},
		{
			.multiplier{ DynamicMultiplicationOperation_TestData::NumberType{ 56.78 } },
			.multiplicand{ DynamicMultiplicationOperation_TestData::NumberType{ 12.34 } },
			.expectedMultiplierEvaluation{ 56.78 },
			.expectedMultiplicandEvaluation{ 12.34 },
			.expectedEvaluation{ 700.6652 }
		},
		{
			.multiplier{ DynamicMultiplicationOperation_TestData::NumberType{ -12.34 } },
			.multiplicand{ DynamicMultiplicationOperation_TestData::NumberType{ 56.78 } },
			.expectedMultiplierEvaluation{ -12.34 },
			.expectedMultiplicandEvaluation{ 56.78 },
			.expectedEvaluation{ -700.6652 }
		},
		{
			.multiplier{ DynamicMultiplicationOperation_TestData::NumberType{ 12.34 } },
			.multiplicand{ DynamicMultiplicationOperation_TestData::NumberType{ -56.78 } },
			.expectedMultiplierEvaluation{ 12.34 },
			.expectedMultiplicandEvaluation{ -56.78 },
			.expectedEvaluation{ -700.6652 }
		},
		{
			.multiplier{ DynamicMultiplicationOperation_TestData::NumberType{ -12.34 } },
			.multiplicand{ DynamicMultiplicationOperation_TestData::NumberType{ -56.78 } },
			.expectedMultiplierEvaluation{ -12.34 },
			.expectedMultiplicandEvaluation{ -56.78 },
			.expectedEvaluation{ 700.6652 }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicMultiplicationOperationTests,
		DynamicMultiplicationOperationWithTestDataTests,
		testing::ValuesIn(DynamicMultiplicationOperation_TestDataValues)
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
		EXPECT_EQ(expectedMultiplierEvaluation, instance.getMultiplier().getEvaluation().FAKE_getValue());
		EXPECT_EQ(expectedMultiplicandEvaluation, instance.getMultiplicand().getEvaluation().FAKE_getValue());
		EXPECT_EQ(expectedEvaluation, instance.getEvaluation().FAKE_getValue());
	}

#pragma endregion
}