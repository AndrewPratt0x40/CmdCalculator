#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicAbsoluteValueOperation.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTests
{
#pragma region Concept satisfaction

	TEST(DynamicAbsoluteValueOperationTests, DynamicAbsoluteValueOperation$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculator::Expressions::DynamicAbsoluteValueOperation
				<
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion


#pragma region Test data setup

	struct DynamicAbsoluteValueOperation_TestData
	{
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using OperandType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		OperandType operand;
		double expectedOperandEvaluation;
		double expectedEvaluation;

		DynamicAbsoluteValueOperation_TestData(const double operand, const double evaluation) :
			operand{ DynamicAbsoluteValueOperation_TestData::NumberType{ operand } },
			expectedOperandEvaluation{ operand },
			expectedEvaluation{ evaluation }
		{}


		friend std::ostream& operator<<(std::ostream & ostream, const DynamicAbsoluteValueOperation_TestData & testData)
		{
			ostream
				<< '['
				<< " |"
				<< testData.operand.evaluation.FAKE_getValue()
				<< "| == {|"
				<< testData.expectedOperandEvaluation
				<< "|="
				<< testData.expectedEvaluation
				<< "}]"
			;

			return ostream;
		}
	};

	class DynamicAbsoluteValueOperationWithTestDataTests :
		public testing::TestWithParam<DynamicAbsoluteValueOperation_TestData>
	{};

	const DynamicAbsoluteValueOperation_TestData DynamicAbsoluteValueOperation_TestDataValues[]
	{
		DynamicAbsoluteValueOperation_TestData{ -56.78,  56.78 },
		DynamicAbsoluteValueOperation_TestData{ -12.34,  12.34 },
		DynamicAbsoluteValueOperation_TestData{  -2.00,   2.00 },
		DynamicAbsoluteValueOperation_TestData{  -1.50,   1.50 },
		DynamicAbsoluteValueOperation_TestData{  -1.00,   1.00 },
		DynamicAbsoluteValueOperation_TestData{  -0.50,   0.50 },
		DynamicAbsoluteValueOperation_TestData{   0.00,   0.00 },
		DynamicAbsoluteValueOperation_TestData{   0.50,   0.50 },
		DynamicAbsoluteValueOperation_TestData{   1.00,   1.00 },
		DynamicAbsoluteValueOperation_TestData{   1.50,   1.50 },
		DynamicAbsoluteValueOperation_TestData{   2.00,   2.00 },
		DynamicAbsoluteValueOperation_TestData{  12.34,  12.34 },
		DynamicAbsoluteValueOperation_TestData{  56.78,  56.78 }
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicAbsoluteValueOperationTests,
		DynamicAbsoluteValueOperationWithTestDataTests,
		testing::ValuesIn(DynamicAbsoluteValueOperation_TestDataValues)
	);

#pragma endregion


#pragma region Expected state

	TEST_P(DynamicAbsoluteValueOperationWithTestDataTests, DynamicAbsoluteValueOperation$has$expected$state)
	{
		// Arrange
		using NumberType = DynamicAbsoluteValueOperation_TestData::NumberType;
		using OperandType = DynamicAbsoluteValueOperation_TestData::OperandType;

		auto operandToPass{ std::make_unique<OperandType>(GetParam().operand) };

		const double expectedOperandEvaluation{ GetParam().expectedOperandEvaluation };
		const double expectedEvaluation{ GetParam().expectedEvaluation };
		
		// Act
		CmdCalculator::Expressions::DynamicAbsoluteValueOperation<NumberType> instance
		{
			std::move(operandToPass)
		};

		// Assert
		EXPECT_DOUBLE_EQ(expectedOperandEvaluation, instance.getOperand().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedEvaluation, instance.getEvaluation().FAKE_getValue());
	}

#pragma endregion
}