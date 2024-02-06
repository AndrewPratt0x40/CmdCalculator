#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicExponentiationOperation.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTests
{
#pragma region Concept satisfaction

	TEST(DynamicExponentiationOperationTests, DynamicExponentiationOperation$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculator::Expressions::DynamicExponentiationOperation
				<
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion


#pragma region Test data setup

	struct DynamicExponentiationOperation_TestData
	{
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using OperandType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		OperandType base;
		OperandType exponent;
		double expectedBaseEvaluation;
		double expectedExponentEvaluation;
		double expectedEvaluation;

		DynamicExponentiationOperation_TestData(const double base, const double exponent, const double evaluation) :
			base{ DynamicExponentiationOperation_TestData::NumberType{ base } },
			exponent{ DynamicExponentiationOperation_TestData::NumberType{ exponent } },
			expectedBaseEvaluation{ base },
			expectedExponentEvaluation{ exponent },
			expectedEvaluation{ evaluation }
		{}


		friend std::ostream& operator<<(std::ostream & ostream, const DynamicExponentiationOperation_TestData & testData)
		{
			ostream
				<< '['
				<< testData.base.evaluation.FAKE_getValue()
				<< " ^ "
				<< testData.exponent.evaluation.FAKE_getValue()
				<< " == {"
				<< testData.expectedBaseEvaluation
				<< '^'
				<< testData.expectedExponentEvaluation
				<< '='
				<< testData.expectedEvaluation
				<< "}]"
			;

			return ostream;
		}
	};

	class DynamicExponentiationOperationWithTestDataTests :
		public testing::TestWithParam<DynamicExponentiationOperation_TestData>
	{};

	const DynamicExponentiationOperation_TestData DynamicExponentiationOperation_TestDataValues[]
	{
		DynamicExponentiationOperation_TestData{  0.0,  0,  1.0 },
		DynamicExponentiationOperation_TestData{  0.0,  1,  0.0 },
		DynamicExponentiationOperation_TestData{  0.0,  2,  0.0 },
		DynamicExponentiationOperation_TestData{  0.0,  3,  0.0 },
		DynamicExponentiationOperation_TestData{  0.0,  10, 0.0 },

		DynamicExponentiationOperation_TestData{  0.5,  0,  1.0 },
		DynamicExponentiationOperation_TestData{  0.5,  1,  0.5 },
		DynamicExponentiationOperation_TestData{  0.5,  2,  0.25 },
		DynamicExponentiationOperation_TestData{  0.5,  3,  0.125 },
		DynamicExponentiationOperation_TestData{  0.5,  10, 0.0009765625 },

		DynamicExponentiationOperation_TestData{  1.0,  0,  1.0 },
		DynamicExponentiationOperation_TestData{  1.0,  1,  1.0 },
		DynamicExponentiationOperation_TestData{  1.0,  2,  1.0 },
		DynamicExponentiationOperation_TestData{  1.0,  3,  1.0 },
		DynamicExponentiationOperation_TestData{  1.0,  10, 1.0 },

		DynamicExponentiationOperation_TestData{  1.5,  0,  1.0 },
		DynamicExponentiationOperation_TestData{  1.5,  1,  1.5 },
		DynamicExponentiationOperation_TestData{  1.5,  2,  2.25 },
		DynamicExponentiationOperation_TestData{  1.5,  3,  3.375 },
		DynamicExponentiationOperation_TestData{  1.5,  10, 57.6650390625 },

		DynamicExponentiationOperation_TestData{  2.0,  0,  1.0 },
		DynamicExponentiationOperation_TestData{  2.0,  1,  2.0 },
		DynamicExponentiationOperation_TestData{  2.0,  2,  4.0 },
		DynamicExponentiationOperation_TestData{  2.0,  3,  8.0 },
		DynamicExponentiationOperation_TestData{  2.0,  10, 1024.0 },

		DynamicExponentiationOperation_TestData{ -1.0,  0,  1.0 },
		DynamicExponentiationOperation_TestData{ -1.0,  1, -1.0 },
		DynamicExponentiationOperation_TestData{ -1.0,  2,  1.0 },
		DynamicExponentiationOperation_TestData{ -1.0,  3, -1.0 },
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicExponentiationOperationTests,
		DynamicExponentiationOperationWithTestDataTests,
		testing::ValuesIn(DynamicExponentiationOperation_TestDataValues)
	);

#pragma endregion


#pragma region Expected state

	TEST_P(DynamicExponentiationOperationWithTestDataTests, DynamicExponentiationOperation$has$expected$state)
	{
		// Arrange
		using NumberType = DynamicExponentiationOperation_TestData::NumberType;
		using OperandType = DynamicExponentiationOperation_TestData::OperandType;

		auto baseToPass{ std::make_unique<OperandType>(GetParam().base) };
		auto exponentToPass{ std::make_unique<OperandType>(GetParam().exponent) };

		const double expectedBaseEvaluation{ GetParam().expectedBaseEvaluation };
		const double expectedExponentEvaluation{ GetParam().expectedExponentEvaluation };
		const double expectedEvaluation{ GetParam().expectedEvaluation };
		
		// Act
		CmdCalculator::Expressions::DynamicExponentiationOperation<NumberType> instance
		{
			std::move(baseToPass),
			std::move(exponentToPass)
		};

		// Assert
		EXPECT_DOUBLE_EQ(expectedBaseEvaluation, instance.getBase().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedExponentEvaluation, instance.getExponent().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedEvaluation, instance.getEvaluation().FAKE_getValue());
	}

#pragma endregion
}