#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicAdditionOperation.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(DynamicAdditionOperationTests, DynamicAdditionOperation$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculator::Expressions::DynamicAdditionOperation
				<
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion


#pragma region Test data setup

	struct DynamicAdditionOperation_TestData
	{
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using OperandType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;
		OperandType augend;
		OperandType addend;
		double expectedAugendEvaluation;
		double expectedAddendEvaluation;
		double expectedEvaluation;
	};

	class DynamicAdditionOperationWithTestDataTests :
		public testing::TestWithParam<DynamicAdditionOperation_TestData>
	{};

	const DynamicAdditionOperation_TestData DynamicAdditionOperation_TestDataValues[]
	{
		{
			.augend{ DynamicAdditionOperation_TestData::NumberType{ 0.0 } },
			.addend{ DynamicAdditionOperation_TestData::NumberType{ 0.0 } },
			.expectedAugendEvaluation{ 0.0 },
			.expectedAddendEvaluation{ 0.0 },
			.expectedEvaluation{ 0.0 }
		},
		{
			.augend{ DynamicAdditionOperation_TestData::NumberType{ 1.0 } },
			.addend{ DynamicAdditionOperation_TestData::NumberType{ 1.0 } },
			.expectedAugendEvaluation{ 1.0 },
			.expectedAddendEvaluation{ 1.0 },
			.expectedEvaluation{ 2.0 }
		},
		{
			.augend{ DynamicAdditionOperation_TestData::NumberType{ 12.34 } },
			.addend{ DynamicAdditionOperation_TestData::NumberType{ 56.78 } },
			.expectedAugendEvaluation{ 12.34 },
			.expectedAddendEvaluation{ 56.78 },
			.expectedEvaluation{ 69.12 }
		},
		{
			.augend{ DynamicAdditionOperation_TestData::NumberType{ 56.78 } },
			.addend{ DynamicAdditionOperation_TestData::NumberType{ 12.34 } },
			.expectedAugendEvaluation{ 56.78 },
			.expectedAddendEvaluation{ 12.34 },
			.expectedEvaluation{ 69.12 }
		},
		{
			.augend{ DynamicAdditionOperation_TestData::NumberType{ -12.34 } },
			.addend{ DynamicAdditionOperation_TestData::NumberType{ 56.78 } },
			.expectedAugendEvaluation{ -12.34 },
			.expectedAddendEvaluation{ 56.78 },
			.expectedEvaluation{ 44.44 }
		},
		{
			.augend{ DynamicAdditionOperation_TestData::NumberType{ 12.34 } },
			.addend{ DynamicAdditionOperation_TestData::NumberType{ -56.78 } },
			.expectedAugendEvaluation{ 12.34 },
			.expectedAddendEvaluation{ -56.78 },
			.expectedEvaluation{ -44.44 }
		},
		{
			.augend{ DynamicAdditionOperation_TestData::NumberType{ -12.34 } },
			.addend{ DynamicAdditionOperation_TestData::NumberType{ -56.78 } },
			.expectedAugendEvaluation{ -12.34 },
			.expectedAddendEvaluation{ -56.78 },
			.expectedEvaluation{ -69.12 }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicAdditionOperationTests,
		DynamicAdditionOperationWithTestDataTests,
		testing::ValuesIn(DynamicAdditionOperation_TestDataValues)
	);

#pragma endregion


#pragma region Expected state

	TEST_P(DynamicAdditionOperationWithTestDataTests, DynamicAdditionOperation$has$expected$state)
	{
		// Arrange
		using NumberType = DynamicAdditionOperation_TestData::NumberType;
		using OperandType = DynamicAdditionOperation_TestData::OperandType;

		auto augendToPass{ std::make_unique<OperandType>(GetParam().augend) };
		auto addendToPass{ std::make_unique<OperandType>(GetParam().addend) };

		const double expectedAugendEvaluation{ GetParam().expectedAugendEvaluation };
		const double expectedAddendEvaluation{ GetParam().expectedAddendEvaluation };
		const double expectedEvaluation{ GetParam().expectedEvaluation };
		
		// Act
		CmdCalculator::Expressions::DynamicAdditionOperation<NumberType> instance
		{
			std::move(augendToPass),
			std::move(addendToPass)
		};

		// Assert
		EXPECT_EQ(expectedAugendEvaluation, instance.getAugend().getEvaluation().FAKE_getValue());
		EXPECT_EQ(expectedAddendEvaluation, instance.getAddend().getEvaluation().FAKE_getValue());
		EXPECT_EQ(expectedEvaluation, instance.getEvaluation().FAKE_getValue());
	}

#pragma endregion
}