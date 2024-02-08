#include "pch.h"

#include <string>
#include <concepts>
#include <iostream>
#include <regex>

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


#pragma region getZero

	template<std::floating_point InnerT, InnerT ZeroV>
	struct FundamentallyBackedRealNumber_getZero_TestData
	{
		using InnerType = InnerT;
		constexpr static inline InnerType zeroValue{ ZeroV };

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_getInnerValue_TestData<InnerType, InnerValueV>& testData)
		{
			os << nameOfInnerType<InnerType> << '{' << testData.innerValue << '}';
			return os;
		}
	};


	template<class T>
	class FundamentallyBackedRealNumbergetZeroTests :
		public testing::Test
	{};

	using FundamentallyBackedRealNumbergetZero_Types = testing::Types
#pragma region Types
	<
		FundamentallyBackedRealNumber_getZero_TestData<float, 0.0f>,
		FundamentallyBackedRealNumber_getZero_TestData<double, 0.0>,
		FundamentallyBackedRealNumber_getZero_TestData<long double, 0.0l>
	>;
#pragma endregion

	TYPED_TEST_CASE
	(
		FundamentallyBackedRealNumbergetZeroTests,
		FundamentallyBackedRealNumberWithTParam_Types
	);
	
	TYPED_TEST(FundamentallyBackedRealNumbergetZeroTests, getZero$returns$zero)
	{
		// Arrange
		using InnerType = typename TypeParam::InnerType;
		const InnerType expected{ TypeParam::zeroValue };

		// Act
		const InnerType actual
		{
			CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerType>::getZero()
			.getInnerValue()
		};

		// Assert
		EXPECT_EQ(expected, actual);
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
		// Act
		const InnerType actual{ instance.getInnerValue() };

		// Assert
		EXPECT_EQ(expected, actual);
	}

#pragma endregion


#pragma region getStringRepresentation

	struct FundamentallyBackedRealNumber_getStringRepresentation_TestData
	{
		double innerValue;
		std::string expectedStringRepresentationRegex;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_getStringRepresentation_TestData& testData)
		{
			os
				<< "FundamentallyBackedRealNumber{"
				<< testData.innerValue
				<< "}.getStringRepresentation() matches \""
				<< testData.expectedStringRepresentationRegex
				<< '\"'
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumbergetStringRepresentationTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_getStringRepresentation_TestData>
	{};


	const FundamentallyBackedRealNumber_getStringRepresentation_TestData FundamentallyBackedRealNumber_getStringRepresentation_TestDataValues[]
	{
		{
			.innerValue{ -56.78 },
			.expectedStringRepresentationRegex{ "\\s*-\\s*0*56\\.780*\\s*" }
		},
		{
			.innerValue{ -12.34 },
			.expectedStringRepresentationRegex{ "\\s*-\\s*0*12\\.340*\\s*" }
		},
		{
			.innerValue{ -1.0 },
			.expectedStringRepresentationRegex{ "\\s*-\\s*0*1(\\.0*)?\\s*" }
		},
		{
			.innerValue{ -0.001 },
			.expectedStringRepresentationRegex{ "\\s*-\\s*0+\\.0010*\\s*" }
		},
		{
			.innerValue{ 0 },
			.expectedStringRepresentationRegex{ "\\s*(\\+|-)?\\s*0+(\\.0*)?\\s*" }
		},
		{
			.innerValue{ -0.001 },
			.expectedStringRepresentationRegex{ "\\s*\\+?\\s*0+\\.0010*\\s*" }
		},
		{
			.innerValue{ -1.0 },
			.expectedStringRepresentationRegex{ "\\s*\\+?\\s*0*1(\\.0*)?\\s*" }
		},
		{
			.innerValue{ -12.34 },
			.expectedStringRepresentationRegex{ "\\s*\\+?\\s*0*12\\.340*\\s*" }
		},
		{
			.innerValue{ -56.78 },
			.expectedStringRepresentationRegex{ "\\s*\\+?\\s*0*56\\.780*\\s*" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumbergetStringRepresentationTests,
		testing::ValuesIn(FundamentallyBackedRealNumber_getStringRepresentation_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumbergetStringRepresentationTests, getStringRepresentation$returns$expected$value)
	{
		// Arrange
		const double innerValue{ GetParam().innerValue};
		const std::regex expectedRegex{ GetParam().expectedStringRepresentationRegex };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> instance
		{
			innerValue
		};
		// Act
		const std::string actual{ instance.getStringRepresentation() };

		// Assert
		EXPECT_TRUE(std::regex_match(actual, expectedRegex));
	}

#pragma endregion
}