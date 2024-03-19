#include "pch.h"

#include <string>
#include <ranges>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/DynamicNumber.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTests
{
#pragma region Concept satisfaction

	TEST(DynamicNumberTests, DynamicNumber$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculator::Expressions::DynamicNumber
				<
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion


#pragma region Test data setup

	struct DynamicNumber_TestData
	{
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using OperandType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		NumberType number;
		double expectedEvaluation;


		friend std::ostream& operator<<(std::ostream & ostream, const DynamicNumber_TestData & testData)
		{
			ostream
				<< "DynamicNumber{"
				<< testData.number.FAKE_getValue()
				<< "} = "
				<< testData.expectedEvaluation
			;

			return ostream;
		}
	};

	class DynamicNumberWithTestDataTests :
		public testing::TestWithParam<DynamicNumber_TestData>
	{};

	const std::ranges::forward_range auto DynamicNumber_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::numbers()
		| std::views::transform
		(
			[](const auto& number)
			{
				return DynamicNumber_TestData
				{
					.number{ number },
					.expectedEvaluation{ number }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicNumberTests,
		DynamicNumberWithTestDataTests,
		CmdCalculatorTestUtils::ValuesInRange(DynamicNumber_TestDataValues)
	);

#pragma endregion


#pragma region Expected state

	TEST_P(DynamicNumberWithTestDataTests, DynamicNumber$has$expected$state)
	{
		// Arrange
		using NumberType = DynamicNumber_TestData::NumberType;

		const NumberType numberToPass{ GetParam().number };

		const NumberType expectedValue{ GetParam().number };
		const double expectedEvaluation{ GetParam().expectedEvaluation };
		
		// Act
		CmdCalculator::Expressions::DynamicNumber<NumberType> instance
		{
			numberToPass
		};

		// Assert
		EXPECT_EQ(expectedValue, instance.getValue());
		EXPECT_DOUBLE_EQ(expectedEvaluation, instance.getEvaluation().FAKE_getValue());
	}

#pragma endregion
}