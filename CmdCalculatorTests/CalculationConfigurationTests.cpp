#include "pch.h"

#include "..\CmdCalculator\NotImplementedException.h"
#include "..\CmdCalculator\CalculationConfiguration.h"

namespace CmdCalculatorTests
{
	struct CalculationConfiguration_CtorParams
	{
		int precision;
		bool shouldPreferDecimalsOverIntegers;
		bool shouldPreferSignExpressionForPositiveValues;
		bool shouldPreferLeadingZeroOverWholelessNumbers;
		bool shouldPreferTrailingZeroOverEmptyDecimalPlace;
	};

	constexpr CalculationConfiguration_CtorParams validValuesFor_CalculationConfiguration_CtorParams[]
	{
		CalculationConfiguration_CtorParams{0, false, false, false, false},
		CalculationConfiguration_CtorParams{1, true, true, true, true}
	};

	constexpr CalculationConfiguration_CtorParams negativePrecisionsFor_CalculationConfiguration_CtorParams[]
	{
		CalculationConfiguration_CtorParams{-1, false, false, false, false},
		CalculationConfiguration_CtorParams{-2, true, true, true, true}
	};

#pragma region Constructor with valid parameters

	class CtorWithValidParamsFixture :
		public testing::TestWithParam<CalculationConfiguration_CtorParams>
	{};


	TEST_P(CtorWithValidParamsFixture, Constructor$with$valid$params$sets$expected$values)
	{
		// Arrange / Act
		CmdCalculator::CalculationConfiguration instance
		{
			GetParam().precision,
			GetParam().shouldPreferDecimalsOverIntegers,
			GetParam().shouldPreferSignExpressionForPositiveValues,
			GetParam().shouldPreferLeadingZeroOverWholelessNumbers,
			GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace
		};

		// Assert
		EXPECT_EQ(instance.getPrecision(), GetParam().precision);
		EXPECT_EQ(instance.shouldPreferDecimalsOverIntegers(), GetParam().shouldPreferDecimalsOverIntegers);
		EXPECT_EQ(instance.shouldPreferSignExpressionForPositiveValues(), GetParam().shouldPreferSignExpressionForPositiveValues);
		EXPECT_EQ(instance.shouldPreferLeadingZeroOverWholelessNumbers(), GetParam().shouldPreferLeadingZeroOverWholelessNumbers);
		EXPECT_EQ(instance.shouldPreferTrailingZeroOverEmptyDecimalPlace(), GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace);
	}


	INSTANTIATE_TEST_CASE_P
	(
		SimpleValues,
		CtorWithValidParamsFixture,
		testing::ValuesIn(validValuesFor_CalculationConfiguration_CtorParams)
	);

#pragma endregion


#pragma region Constructor with invalid parameters

	class CtorWithNegativePrecisionFixture :
		public testing::TestWithParam<CalculationConfiguration_CtorParams>
	{};


	TEST_P(CtorWithNegativePrecisionFixture, Constructor$with$negative$precision$throws$invalid$argument)
	{
		// Arrange
		auto action
		{
			[&]
			{
				CmdCalculator::CalculationConfiguration
				{
					GetParam().precision,
					GetParam().shouldPreferDecimalsOverIntegers,
					GetParam().shouldPreferSignExpressionForPositiveValues,
					GetParam().shouldPreferLeadingZeroOverWholelessNumbers,
					GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace
				};
			}
		};

		// Assert
		EXPECT_THROW(action(), std::invalid_argument);
	}


	INSTANTIATE_TEST_CASE_P
	(
		SimpleValues,
		CtorWithNegativePrecisionFixture,
		testing::ValuesIn(negativePrecisionsFor_CalculationConfiguration_CtorParams)
	);

#pragma endregion
}