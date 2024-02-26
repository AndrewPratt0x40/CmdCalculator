#include "pch.h"

#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(FakeRealNumberTests, FakeRealNumber$satisfies$RealNumber$concept)
	{
		static_assert
		(
			::CmdCalculator::Arithmetic::RealNumber<CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber>
		);
	}

#pragma endregion


#pragma region getZero

	TEST(FakeRealNumberTests, getZero$returns$zero)
	{
		// Arrange
		const auto instance{ CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber::getZero() };

		// Assert
		EXPECT_EQ(0.0, instance.FAKE_getValue());
	}

#pragma endregion


#pragma region getSign

	struct FakeRealNumbergetSignTestData
	{
		double value;
		::CmdCalculator::Arithmetic::ESign expectedSign;
	};

	class FakeRealNumbergetSignTests :
		public testing::TestWithParam<FakeRealNumbergetSignTestData>
	{};

	const FakeRealNumbergetSignTestData FakeRealNumbergetSignTestDataValues[]
	{
		{
			.value{ std::numeric_limits<double>::lowest() },
			.expectedSign{ ::CmdCalculator::Arithmetic::ESign::Negative }
		},
		{
			.value{ -12.34 },
			.expectedSign{ ::CmdCalculator::Arithmetic::ESign::Negative }
		},
		{
			.value{ -1.0 },
			.expectedSign{ ::CmdCalculator::Arithmetic::ESign::Negative }
		},
		{
			.value{ -std::numeric_limits<double>::min() },
			.expectedSign{ ::CmdCalculator::Arithmetic::ESign::Negative }
		},
		{
			.value{ 0.0 },
			.expectedSign{ ::CmdCalculator::Arithmetic::ESign::Neutral }
		},
		{
			.value{ std::numeric_limits<double>::min() },
			.expectedSign{ ::CmdCalculator::Arithmetic::ESign::Positive }
		},
		{
			.value{ 1.0 },
			.expectedSign{ ::CmdCalculator::Arithmetic::ESign::Positive }
		},
		{
			.value{ 12.34 },
			.expectedSign{ ::CmdCalculator::Arithmetic::ESign::Positive }
		},
		{
			.value{ std::numeric_limits<double>::max() },
			.expectedSign{ ::CmdCalculator::Arithmetic::ESign::Positive }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		FakeRealNumberTests,
		FakeRealNumbergetSignTests,
		testing::ValuesIn(FakeRealNumbergetSignTestDataValues)
	);

	TEST_P(FakeRealNumbergetSignTests, getSign$returns$expected$value)
	{
		// Arrange
		const ::CmdCalculator::Arithmetic::ESign expectedSign{ GetParam().expectedSign };
		const CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber instance{ GetParam().value };

		// Assert
		EXPECT_EQ(expectedSign, instance.getSign());
	}

#pragma region
}