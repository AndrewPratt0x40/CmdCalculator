#include "pch.h"

#include <string>
#include <concepts>
#include <iostream>

#include "../CmdCalculator/FundamentallyBackedRealNumber.h"
#include "../CmdCalculator/RealNumber.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Shared test data

	template<std::floating_point InnerT>
	constexpr static auto nameOfInnerType{ "UNKNOWN" };
	template<>
	constexpr static auto nameOfInnerType<float>{ "float" };
	template<>
	constexpr static auto nameOfInnerType<double>{ "double" };
	template<>
	constexpr static auto nameOfInnerType<long double>{ "long double" };

	using FundamentallyBackedRealNumber_ValidInnerTypes = testing::Types<float, double, long double>;

#pragma endregion


#pragma region Concept satisfaction

	template<class T>
	class FundamentallyBackedRealNumberWithTParamTests :
		public testing::Test
	{};

	using FundamentallyBackedRealNumberWithTParam_Types = FundamentallyBackedRealNumber_ValidInnerTypes;

	TYPED_TEST_CASE
	(
		FundamentallyBackedRealNumberWithTParamTests,
		FundamentallyBackedRealNumberWithTParam_Types
	);
	
	TYPED_TEST(FundamentallyBackedRealNumberWithTParamTests, FundamentallyBackedRealNumber$satisfies$RealNumber$concept)
	{
		static_assert
		(
			CmdCalculator::Arithmetic::RealNumber
			<
				CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<TypeParam>
			>
		);
	}

#pragma endregion


#pragma region getInnerValue

	template<std::floating_point InnerT, InnerT InnerValueV>
	struct FundamentallyBackedRealNumber_getInnerValue_TestData
	{
		using InnerType = InnerT;
		constexpr static inline InnerType innerValue{ InnerValueV };

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_getInnerValue_TestData<InnerType, InnerValueV>& testData)
		{
			os << nameOfInnerType<InnerType> << '{' << testData.innerValue << '}';
			return os;
		}
	};
	
	
	template<class T>
	class FundamentallyBackedRealNumbergetInnerValueTests :
		public testing::Test
	{};


	using FundamentallyBackedRealNumber_getInnerValue_TestDataValues = testing::Types
#pragma region Types
	<
		FundamentallyBackedRealNumber_getInnerValue_TestData<float, -56.78f>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<float, -12.34f>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<float,  -1.00f>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<float,   0.00f>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<float,   1.00f>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<float,  12.34f>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<float,  56.78f>,

		FundamentallyBackedRealNumber_getInnerValue_TestData<double, -56.78>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<double, -12.34>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<double,  -1.00>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<double,   0.00>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<double,   1.00>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<double,  12.34>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<double,  56.78>,

		FundamentallyBackedRealNumber_getInnerValue_TestData<long double, -56.78l>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<long double, -12.34l>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<long double,  -1.00l>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<long double,   0.00l>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<long double,   1.00l>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<long double,  12.34l>,
		FundamentallyBackedRealNumber_getInnerValue_TestData<long double,  56.78l>
	>;
#pragma endregion

	TYPED_TEST_CASE
	(
		FundamentallyBackedRealNumbergetInnerValueTests,
		FundamentallyBackedRealNumber_getInnerValue_TestDataValues
	);
	
	TYPED_TEST(FundamentallyBackedRealNumbergetInnerValueTests, getInnerValue$returns$expected$value)
	{
		// Arrange
		using InnerType = typename TypeParam::InnerType;
		const InnerType innerValue{ TypeParam::innerValue };
		const InnerType expected{ TypeParam::innerValue };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerType> instance
		{
			innerValue
		};

		auto foo = instance == instance;

		// Act
		const InnerType actual{ instance.getInnerValue() };

		// Assert
		EXPECT_EQ(expected, actual);
	}

#pragma endregion
}