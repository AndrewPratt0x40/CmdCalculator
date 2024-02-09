#include "pch.h"

#include <string>

#include "common.h"
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

	const auto DynamicExponentiationOperation_TestDataValues
	{
		SharedTestData::exponentiationOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return DynamicExponentiationOperation_TestData
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
		DynamicExponentiationOperationTests,
		DynamicExponentiationOperationWithTestDataTests,
		ValuesInRange(DynamicExponentiationOperation_TestDataValues)
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