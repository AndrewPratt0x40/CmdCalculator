#include "pch.h"

#include <string>

#include "common.h"
#include "../CmdCalculator/DynamicNegationOperation.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTests
{
#pragma region Concept satisfaction

	TEST(DynamicNegationOperationTests, DynamicNegationOperation$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculator::Expressions::DynamicNegationOperation
				<
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion


#pragma region Test data setup

	struct DynamicNegationOperation_TestData
	{
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using OperandType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		OperandType operand;
		double expectedOperandEvaluation;
		double expectedEvaluation;


		friend std::ostream& operator<<(std::ostream & ostream, const DynamicNegationOperation_TestData & testData)
		{
			ostream
				<< '['
				<< " -"
				<< testData.operand.evaluation.FAKE_getValue()
				<< " == {-"
				<< testData.expectedOperandEvaluation
				<< "="
				<< testData.expectedEvaluation
				<< "}]"
			;

			return ostream;
		}
	};

	class DynamicNegationOperationWithTestDataTests :
		public testing::TestWithParam<DynamicNegationOperation_TestData>
	{};

	const auto DynamicNegationOperation_TestDataValues
	{
		SharedTestData::negationOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return DynamicNegationOperation_TestData
				{
					.operand{ data.operand },
					.expectedOperandEvaluation{ data.operand },
					.expectedEvaluation{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicNegationOperationTests,
		DynamicNegationOperationWithTestDataTests,
		ValuesInRange(DynamicNegationOperation_TestDataValues)
	);

#pragma endregion


#pragma region Expected state

	TEST_P(DynamicNegationOperationWithTestDataTests, DynamicNegationOperation$has$expected$state)
	{
		// Arrange
		using NumberType = DynamicNegationOperation_TestData::NumberType;
		using OperandType = DynamicNegationOperation_TestData::OperandType;

		auto operandToPass{ std::make_unique<OperandType>(GetParam().operand) };

		const double expectedOperandEvaluation{ GetParam().expectedOperandEvaluation };
		const double expectedEvaluation{ GetParam().expectedEvaluation };
		
		// Act
		CmdCalculator::Expressions::DynamicNegationOperation<NumberType> instance
		{
			std::move(operandToPass)
		};

		// Assert
		EXPECT_DOUBLE_EQ(expectedOperandEvaluation, instance.getOperand().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedEvaluation, instance.getEvaluation().FAKE_getValue());
	}

#pragma endregion
}