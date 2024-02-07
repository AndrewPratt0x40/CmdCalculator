#include "pch.h"

#include <string>
#include <iostream>

#include "../CmdCalculator/DynamicModuloOperation.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/DivisionByZeroException.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTests
{
#pragma region Concept satisfaction

	TEST(DynamicModuloOperationTests, DynamicModuloOperation$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculator::Expressions::DynamicModuloOperation
				<
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion


#pragma region Test data setup

	struct DynamicModuloOperation_TestData
	{
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using OperandType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		OperandType dividend;
		OperandType divisor;
		double expectedDividendEvaluation;
		double expectedDivisorEvaluation;
		double expectedEvaluation;

		DynamicModuloOperation_TestData(const double dividend, const double divisor, const double evaluation) :
			dividend{ DynamicModuloOperation_TestData::NumberType{ dividend } },
			divisor{ DynamicModuloOperation_TestData::NumberType{ divisor } },
			expectedDividendEvaluation{ dividend },
			expectedDivisorEvaluation{ divisor },
			expectedEvaluation{ evaluation }
		{}


		friend std::ostream& operator<<(std::ostream& ostream, const DynamicModuloOperation_TestData& testData)
		{
			ostream
				<< '['
				<< testData.dividend.evaluation.FAKE_getValue()
				<< " % "
				<< testData.divisor.evaluation.FAKE_getValue()
				<< " == {"
				<< testData.expectedDividendEvaluation
				<< '%'
				<< testData.expectedDivisorEvaluation
				<< '='
				<< testData.expectedEvaluation
				<< "}]"
			;

			return ostream;
		}
	};

	class DynamicModuloOperationWithTestDataTests :
		public testing::TestWithParam<DynamicModuloOperation_TestData>
	{};

	const DynamicModuloOperation_TestData DynamicModuloOperation_TestDataValues[]
	{
		DynamicModuloOperation_TestData{  0.00,  1.0,  0.00 },
		DynamicModuloOperation_TestData{  0.25,  1.0,  0.25 },
		DynamicModuloOperation_TestData{  0.50,  1.0,  0.50 },
		DynamicModuloOperation_TestData{  0.75,  1.0,  0.75 },
		DynamicModuloOperation_TestData{  1.00,  1.0,  0.00 },
		DynamicModuloOperation_TestData{  1.25,  1.0,  0.25 },
		DynamicModuloOperation_TestData{  1.50,  1.0,  0.50 },
		DynamicModuloOperation_TestData{  2.00,  1.0,  0.00 },

		DynamicModuloOperation_TestData{  0.00,  3.0,  0.00 },
		DynamicModuloOperation_TestData{  1.00,  3.0,  1.00 },
		DynamicModuloOperation_TestData{  2.00,  3.0,  2.00 },
		DynamicModuloOperation_TestData{  3.00,  3.0,  0.00 },
		DynamicModuloOperation_TestData{  4.00,  3.0,  1.00 },
		DynamicModuloOperation_TestData{  5.00,  3.0,  2.00 },
		DynamicModuloOperation_TestData{  6.00,  3.0,  0.00 },
		DynamicModuloOperation_TestData{  7.00,  3.0,  1.00 },

		DynamicModuloOperation_TestData{  0.00,  1.5,  0.00 },
		DynamicModuloOperation_TestData{  0.50,  1.5,  0.50 },
		DynamicModuloOperation_TestData{  1.00,  1.5,  1.00 },
		DynamicModuloOperation_TestData{  1.50,  1.5,  0.00 },
		DynamicModuloOperation_TestData{  2.00,  1.5,  0.50 },

		DynamicModuloOperation_TestData{  12.34,  56.78,  12.34 },
		DynamicModuloOperation_TestData{  56.78,  12.34,   7.42 },

		DynamicModuloOperation_TestData{  12.34, -56.78, -12.34 },
		DynamicModuloOperation_TestData{ -56.78,  12.34,  -7.42 },

		DynamicModuloOperation_TestData{ -12.34,  56.78, -12.34 },
		DynamicModuloOperation_TestData{  56.78, -12.34, - 7.42 },

		DynamicModuloOperation_TestData{ -12.34, -56.78,  12.34 },
		DynamicModuloOperation_TestData{ -56.78, -12.34,   7.42 }
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicModuloOperationTests,
		DynamicModuloOperationWithTestDataTests,
		testing::ValuesIn(DynamicModuloOperation_TestDataValues)
	);

#pragma endregion


#pragma region Expected state

	TEST_P(DynamicModuloOperationWithTestDataTests, DynamicModuloOperation$has$expected$state)
	{
		// Arrange
		using NumberType = DynamicModuloOperation_TestData::NumberType;
		using OperandType = DynamicModuloOperation_TestData::OperandType;

		auto dividendToPass{ std::make_unique<OperandType>(GetParam().dividend) };
		auto divisorToPass{ std::make_unique<OperandType>(GetParam().divisor) };

		const double expectedDividendEvaluation{ GetParam().expectedDividendEvaluation };
		const double expectedDivisorEvaluation{ GetParam().expectedDivisorEvaluation };
		const double expectedEvaluation{ GetParam().expectedEvaluation };
		
		// Act
		CmdCalculator::Expressions::DynamicModuloOperation<NumberType> instance
		{
			std::move(dividendToPass),
			std::move(divisorToPass)
		};

		// Assert
		EXPECT_DOUBLE_EQ(expectedDividendEvaluation, instance.getDividend().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedDivisorEvaluation, instance.getDivisor().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedEvaluation, instance.getEvaluation().FAKE_getValue());
	}

#pragma endregion


#pragma region Modulo by zero

	class DynamicModuloOperationDivisionByZeroTests :
		public testing::TestWithParam<double>
	{};

	const double DynamicModuloOperationDivisionByZeroTests_Values[]
	{
		-12.34,
		 0.00,
		 0.50,
		 1.00,
		 12.34,
		 56.78
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicModuloOperationTests,
		DynamicModuloOperationDivisionByZeroTests,
		testing::ValuesIn(DynamicModuloOperationDivisionByZeroTests_Values)
	);


	TEST_P(DynamicModuloOperationDivisionByZeroTests, Calling$evaluate$with$divisor$of$zero$throws$DivisionByZeroException)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using OperandType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		const NumberType dividend{ GetParam() };
		const NumberType divisor{ 0.0 };

		auto dividendToPass{ std::make_unique<OperandType>(dividend) };
		auto divisorToPass{ std::make_unique<OperandType>(divisor) };

		CmdCalculator::Expressions::DynamicModuloOperation<NumberType> instance
		{
			std::move(dividendToPass),
			std::move(divisorToPass)
		};

		// Act/Assert
		EXPECT_THROW(instance.getEvaluation(), CmdCalculator::DivisionByZeroException);
	}

#pragma endregion
}