#include "pch.h"

#include <string>
#include <ranges>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/DynamicNthRootOperation.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/NegativeRadicandException.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTests
{
#pragma region Concept satisfaction

	TEST(DynamicNthRootOperationTests, DynamicNthRootOperation$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculator::Expressions::DynamicNthRootOperation
				<
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion


#pragma region Test data setup

	struct DynamicNthRootOperation_TestData
	{
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using OperandType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		OperandType degree;
		OperandType radicand;
		double expectedDegreeEvaluation;
		double expectedRadicandEvaluation;
		double expectedEvaluation;

		DynamicNthRootOperation_TestData(const double degree, const double radicand, const double evaluation) :
			degree{ DynamicNthRootOperation_TestData::NumberType{ degree } },
			radicand{ DynamicNthRootOperation_TestData::NumberType{ radicand } },
			expectedDegreeEvaluation{ degree },
			expectedRadicandEvaluation{ radicand },
			expectedEvaluation{ evaluation }
		{}


		friend std::ostream& operator<<(std::ostream & ostream, const DynamicNthRootOperation_TestData & testData)
		{
			ostream
				<< '['
				<< testData.degree.evaluation.FAKE_getValue()
				<< " _ "
				<< testData.radicand.evaluation.FAKE_getValue()
				<< " == {"
				<< testData.expectedDegreeEvaluation
				<< '_'
				<< testData.expectedRadicandEvaluation
				<< '='
				<< testData.expectedEvaluation
				<< "}]"
			;

			return ostream;
		}
	};

	class DynamicNthRootOperationWithTestDataTests :
		public testing::TestWithParam<DynamicNthRootOperation_TestData>
	{};

	const auto DynamicNthRootOperation_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::nthRootOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return DynamicNthRootOperation_TestData
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
		DynamicNthRootOperationTests,
		DynamicNthRootOperationWithTestDataTests,
		CmdCalculatorTestUtils::ValuesInRange(DynamicNthRootOperation_TestDataValues)
	);

#pragma endregion


#pragma region Expected state

	TEST_P(DynamicNthRootOperationWithTestDataTests, DynamicNthRootOperation$has$expected$state)
	{
		// Arrange
		using NumberType = DynamicNthRootOperation_TestData::NumberType;
		using OperandType = DynamicNthRootOperation_TestData::OperandType;

		auto degreeToPass{ std::make_unique<OperandType>(GetParam().degree) };
		auto radicandToPass{ std::make_unique<OperandType>(GetParam().radicand) };

		const double expectedDegreeEvaluation{ GetParam().expectedDegreeEvaluation };
		const double expectedRadicandEvaluation{ GetParam().expectedRadicandEvaluation };
		const double expectedEvaluation{ GetParam().expectedEvaluation };
		
		// Act
		CmdCalculator::Expressions::DynamicNthRootOperation<NumberType> instance
		{
			std::move(degreeToPass),
			std::move(radicandToPass)
		};

		// Assert
		EXPECT_DOUBLE_EQ(expectedDegreeEvaluation, instance.getDegree().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedRadicandEvaluation, instance.getRadicand().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedEvaluation, instance.getEvaluation().FAKE_getValue());
	}

#pragma endregion


#pragma region Negative radicand

	struct DynamicNthRootOperationWithNegativeRadicand_TestData
	{
		double degree;
		double radicand;

		friend std::ostream& operator<<(std::ostream& ostream, const DynamicNthRootOperationWithNegativeRadicand_TestData& testData)
		{
			ostream << testData.degree << '_' << testData.radicand;
			return ostream;
		}
	};
	
	
	class DynamicNthRootOperationWithNegativeRadicandTests :
		public testing::TestWithParam<DynamicNthRootOperationWithNegativeRadicand_TestData>
	{};

	const DynamicNthRootOperationWithNegativeRadicand_TestData DynamicNthRootOperationWithNegativeRadicand_TestDataValues[]
	{
		{ .degree{ 1.0 }, .radicand{ -1.0 } },
		{ .degree{ 1.0 }, .radicand{ -0.5 } },
		{ .degree{ 1.0 }, .radicand{ -12.34 } },

		{.degree{ 2.0 }, .radicand{ -1.0 } },
		{.degree{ 2.0 }, .radicand{ -0.5 } },
		{.degree{ 2.0 }, .radicand{ -12.34 } },

		{.degree{ 3.0 }, .radicand{ -1.0 } },
		{.degree{ 3.0 }, .radicand{ -0.5 } },
		{.degree{ 3.0 }, .radicand{ -12.34 } }
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicNthRootOperationTests,
		DynamicNthRootOperationWithNegativeRadicandTests,
		testing::ValuesIn(DynamicNthRootOperationWithNegativeRadicand_TestDataValues)
	);


	TEST_P(DynamicNthRootOperationWithNegativeRadicandTests, Calling$evaluate$with$negative$radicand$throws$NegativeRadicandException)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using OperandType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		const NumberType degree{ GetParam().degree };
		const NumberType radicand{ GetParam().radicand };

		auto degreeToPass{ std::make_unique<OperandType>(degree) };
		auto radicandToPass{ std::make_unique<OperandType>(radicand) };

		CmdCalculator::Expressions::DynamicNthRootOperation<NumberType> instance
		{
			std::move(degreeToPass),
			std::move(radicandToPass)
		};

		// Act/Assert
		EXPECT_THROW(instance.getEvaluation(), CmdCalculator::NegativeRadicandException);
	}

#pragma endregion
}