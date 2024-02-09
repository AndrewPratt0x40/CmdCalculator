#include "pch.h"

#include <string>

#include "common.h"
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

	const auto DynamicSubtractionOperation_TestDataValues
	{
		SharedTestData::subtractionOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return DynamicSubtractionOperation_TestData
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
		DynamicSubtractionOperationTests,
		DynamicSubtractionOperationWithTestDataTests,
		ValuesInRange(DynamicSubtractionOperation_TestDataValues)
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