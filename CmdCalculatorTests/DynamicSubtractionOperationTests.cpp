#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicSubtractionOperation.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(DynamicSubtractionOperationTests, DynamicSubtractionOperation$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculator::Expressions::DynamicSubtractionOperation
				<
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion


#pragma region Test data setup

	struct DynamicSubtractionOperation_TestData
	{
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using OperandType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;
		OperandType minuend;
		OperandType subtrahend;
		double expectedMinuendEvaluation;
		double expectedSubtrahendEvaluation;
		double expectedEvaluation;
	};

	class DynamicSubtractionOperationWithTestDataTests :
		public testing::TestWithParam<DynamicSubtractionOperation_TestData>
	{};

	const DynamicSubtractionOperation_TestData DynamicSubtractionOperation_TestDataValues[]
	{
		{
			.minuend{ DynamicSubtractionOperation_TestData::NumberType{ 0.0 } },
			.subtrahend{ DynamicSubtractionOperation_TestData::NumberType{ 0.0 } },
			.expectedMinuendEvaluation{ 0.0 },
			.expectedSubtrahendEvaluation{ 0.0 },
			.expectedEvaluation{ 0.0 }
		},
		{
			.minuend{ DynamicSubtractionOperation_TestData::NumberType{ 1.0 } },
			.subtrahend{ DynamicSubtractionOperation_TestData::NumberType{ 1.0 } },
			.expectedMinuendEvaluation{ 1.0 },
			.expectedSubtrahendEvaluation{ 1.0 },
			.expectedEvaluation{ 0.0 }
		},
		{
			.minuend{ DynamicSubtractionOperation_TestData::NumberType{ 12.34 } },
			.subtrahend{ DynamicSubtractionOperation_TestData::NumberType{ 56.78 } },
			.expectedMinuendEvaluation{ 12.34 },
			.expectedSubtrahendEvaluation{ 56.78 },
			.expectedEvaluation{ -44.44 }
		},
		{
			.minuend{ DynamicSubtractionOperation_TestData::NumberType{ 56.78 } },
			.subtrahend{ DynamicSubtractionOperation_TestData::NumberType{ 12.34 } },
			.expectedMinuendEvaluation{ 56.78 },
			.expectedSubtrahendEvaluation{ 12.34 },
			.expectedEvaluation{ 44.44 }
		},
		{
			.minuend{ DynamicSubtractionOperation_TestData::NumberType{ -12.34 } },
			.subtrahend{ DynamicSubtractionOperation_TestData::NumberType{ 56.78 } },
			.expectedMinuendEvaluation{ -12.34 },
			.expectedSubtrahendEvaluation{ 56.78 },
			.expectedEvaluation{ -69.12 }
		},
		{
			.minuend{ DynamicSubtractionOperation_TestData::NumberType{ 12.34 } },
			.subtrahend{ DynamicSubtractionOperation_TestData::NumberType{ -56.78 } },
			.expectedMinuendEvaluation{ 12.34 },
			.expectedSubtrahendEvaluation{ -56.78 },
			.expectedEvaluation{ 69.12 }
		},
		{
			.minuend{ DynamicSubtractionOperation_TestData::NumberType{ -12.34 } },
			.subtrahend{ DynamicSubtractionOperation_TestData::NumberType{ -56.78 } },
			.expectedMinuendEvaluation{ -12.34 },
			.expectedSubtrahendEvaluation{ -56.78 },
			.expectedEvaluation{ 44.44 }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicSubtractionOperationTests,
		DynamicSubtractionOperationWithTestDataTests,
		testing::ValuesIn(DynamicSubtractionOperation_TestDataValues)
	);

#pragma endregion


#pragma region Expected state

	TEST_P(DynamicSubtractionOperationWithTestDataTests, DynamicSubtractionOperation$has$expected$state)
	{
		// Arrange
		using NumberType = DynamicSubtractionOperation_TestData::NumberType;
		using OperandType = DynamicSubtractionOperation_TestData::OperandType;

		auto minuendToPass{ std::make_unique<OperandType>(GetParam().minuend) };
		auto subtrahendToPass{ std::make_unique<OperandType>(GetParam().subtrahend) };

		const double expectedMinuendEvaluation{ GetParam().expectedMinuendEvaluation };
		const double expectedSubtrahendEvaluation{ GetParam().expectedSubtrahendEvaluation };
		const double expectedEvaluation{ GetParam().expectedEvaluation };
		
		// Act
		CmdCalculator::Expressions::DynamicSubtractionOperation<NumberType> instance
		{
			std::move(minuendToPass),
			std::move(subtrahendToPass)
		};

		// Assert
		EXPECT_EQ(expectedMinuendEvaluation, instance.getMinuend().getEvaluation().FAKE_getValue());
		EXPECT_EQ(expectedSubtrahendEvaluation, instance.getSubtrahend().getEvaluation().FAKE_getValue());
		EXPECT_EQ(expectedEvaluation, instance.getEvaluation().FAKE_getValue());
	}

#pragma endregion
}