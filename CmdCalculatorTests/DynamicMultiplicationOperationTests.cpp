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

		DynamicMultiplicationOperation_TestData(const double multiplier, const double multiplicand, const double evaluation) :
			multiplier{ DynamicMultiplicationOperation_TestData::NumberType{ multiplier } },
			multiplicand{ DynamicMultiplicationOperation_TestData::NumberType{ multiplicand } },
			expectedMultiplierEvaluation{ multiplier },
			expectedMultiplicandEvaluation{ multiplicand },
			expectedEvaluation{ evaluation }
		{}
	};

	class DynamicMultiplicationOperationWithTestDataTests :
		public testing::TestWithParam<DynamicMultiplicationOperation_TestData>
	{};

	const DynamicMultiplicationOperation_TestData DynamicMultiplicationOperation_TestDataValues[]
	{
		DynamicMultiplicationOperation_TestData{  0.0,  0.0,  0.00 },
		DynamicMultiplicationOperation_TestData{  0.0,  0.5,  0.00 },
		DynamicMultiplicationOperation_TestData{  0.0,  1.0,  0.00 },
		DynamicMultiplicationOperation_TestData{  0.0,  1.5,  0.00 },
		DynamicMultiplicationOperation_TestData{  0.0,  2.0,  0.00 },

		DynamicMultiplicationOperation_TestData{  0.5,  0.0,  0.00 },
		DynamicMultiplicationOperation_TestData{  0.5,  0.5,  0.25 },
		DynamicMultiplicationOperation_TestData{  0.5,  1.0,  0.50 },
		DynamicMultiplicationOperation_TestData{  0.5,  1.5,  0.75 },
		DynamicMultiplicationOperation_TestData{  0.5,  2.0,  1.00 },

		DynamicMultiplicationOperation_TestData{  1.0,  0.0,  0.00 },
		DynamicMultiplicationOperation_TestData{  1.0,  0.5,  0.50 },
		DynamicMultiplicationOperation_TestData{  1.0,  1.0,  1.00 },
		DynamicMultiplicationOperation_TestData{  1.0,  1.5,  1.50 },
		DynamicMultiplicationOperation_TestData{  1.0,  2.0,  2.00 },

		DynamicMultiplicationOperation_TestData{  1.5,  0.0,  0.00 },
		DynamicMultiplicationOperation_TestData{  1.5,  0.5,  0.75 },
		DynamicMultiplicationOperation_TestData{  1.5,  1.0,  1.50 },
		DynamicMultiplicationOperation_TestData{  1.5,  1.5,  2.25 },
		DynamicMultiplicationOperation_TestData{  1.5,  2.0,  3.00 },

		DynamicMultiplicationOperation_TestData{  2.0,  0.0,  0.00 },
		DynamicMultiplicationOperation_TestData{  2.0,  0.5,  1.00 },
		DynamicMultiplicationOperation_TestData{  2.0,  1.0,  2.00 },
		DynamicMultiplicationOperation_TestData{  2.0,  1.5,  3.00 },
		DynamicMultiplicationOperation_TestData{  2.0,  2.0,  4.00 },

		DynamicMultiplicationOperation_TestData{  12.34,  56.78,  700.6652 },
		DynamicMultiplicationOperation_TestData{  56.78,  12.34,  700.6652 },

		DynamicMultiplicationOperation_TestData{  12.34, -56.78, -700.6652 },
		DynamicMultiplicationOperation_TestData{ -56.78,  12.34, -700.6652 },

		DynamicMultiplicationOperation_TestData{ -12.34,  56.78, -700.6652 },
		DynamicMultiplicationOperation_TestData{  56.78, -12.34, -700.6652 },

		DynamicMultiplicationOperation_TestData{ -12.34, -56.78,  700.6652 },
		DynamicMultiplicationOperation_TestData{ -56.78, -12.34,  700.6652 }
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