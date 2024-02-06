#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicSubtractionOperation.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTests
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

		DynamicSubtractionOperation_TestData(const double minuend, const double subtrahend, const double evaluation) :
			minuend{ DynamicSubtractionOperation_TestData::NumberType{ minuend } },
			subtrahend{ DynamicSubtractionOperation_TestData::NumberType{ subtrahend } },
			expectedMinuendEvaluation{ minuend },
			expectedSubtrahendEvaluation{ subtrahend },
			expectedEvaluation{ evaluation }
		{}


		friend std::ostream& operator<<(std::ostream & ostream, const DynamicSubtractionOperation_TestData & testData)
		{
			ostream
				<< '['
				<< testData.minuend.evaluation.FAKE_getValue()
				<< " - "
				<< testData.subtrahend.evaluation.FAKE_getValue()
				<< " == {"
				<< testData.expectedMinuendEvaluation
				<< '-'
				<< testData.expectedSubtrahendEvaluation
				<< '='
				<< testData.expectedEvaluation
				<< "}]"
			;

			return ostream;
		}
	};

	class DynamicSubtractionOperationWithTestDataTests :
		public testing::TestWithParam<DynamicSubtractionOperation_TestData>
	{};

	const DynamicSubtractionOperation_TestData DynamicSubtractionOperation_TestDataValues[]
	{
		DynamicSubtractionOperation_TestData{  0.0,  0.0,  0.0 },
		DynamicSubtractionOperation_TestData{  0.0,  0.5, -0.5 },
		DynamicSubtractionOperation_TestData{  0.0,  1.0, -1.0 },
		DynamicSubtractionOperation_TestData{  0.0,  1.5, -1.5 },
		DynamicSubtractionOperation_TestData{  0.0,  2.0, -2.0 },

		DynamicSubtractionOperation_TestData{  0.5,  0.0,  0.5 },
		DynamicSubtractionOperation_TestData{  0.5,  0.5,  0.0 },
		DynamicSubtractionOperation_TestData{  0.5,  1.0, -0.5 },
		DynamicSubtractionOperation_TestData{  0.5,  1.5, -1.0 },
		DynamicSubtractionOperation_TestData{  0.5,  2.0, -1.5 },

		DynamicSubtractionOperation_TestData{  1.0,  0.0,  1.0 },
		DynamicSubtractionOperation_TestData{  1.0,  0.5,  0.5 },
		DynamicSubtractionOperation_TestData{  1.0,  1.0,  0.0 },
		DynamicSubtractionOperation_TestData{  1.0,  1.5, -0.5 },
		DynamicSubtractionOperation_TestData{  1.0,  2.0, -1.0 },

		DynamicSubtractionOperation_TestData{  1.5,  0.0,  1.5 },
		DynamicSubtractionOperation_TestData{  1.5,  0.5,  1.0 },
		DynamicSubtractionOperation_TestData{  1.5,  1.0,  0.5 },
		DynamicSubtractionOperation_TestData{  1.5,  1.5,  0.0 },
		DynamicSubtractionOperation_TestData{  1.5,  2.0, -0.5 },

		DynamicSubtractionOperation_TestData{  2.0,  0.0,  2.0 },
		DynamicSubtractionOperation_TestData{  2.0,  0.5,  1.5 },
		DynamicSubtractionOperation_TestData{  2.0,  1.0,  1.0 },
		DynamicSubtractionOperation_TestData{  2.0,  1.5,  0.5 },
		DynamicSubtractionOperation_TestData{  2.0,  2.0,  0.0 },

		DynamicSubtractionOperation_TestData{  12.34,  56.78, -44.44 },
		DynamicSubtractionOperation_TestData{  56.78,  12.34,  44.44 },

		DynamicSubtractionOperation_TestData{  12.34, -56.78,  69.12 },
		DynamicSubtractionOperation_TestData{ -56.78,  12.34, -69.12 },

		DynamicSubtractionOperation_TestData{ -12.34,  56.78, -69.12 },
		DynamicSubtractionOperation_TestData{  56.78, -12.34,  69.12 },

		DynamicSubtractionOperation_TestData{ -12.34, -56.78,  44.44 },
		DynamicSubtractionOperation_TestData{ -56.78, -12.34, -44.44 }
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
		EXPECT_DOUBLE_EQ(expectedMinuendEvaluation, instance.getMinuend().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedSubtrahendEvaluation, instance.getSubtrahend().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedEvaluation, instance.getEvaluation().FAKE_getValue());
	}

#pragma endregion
}