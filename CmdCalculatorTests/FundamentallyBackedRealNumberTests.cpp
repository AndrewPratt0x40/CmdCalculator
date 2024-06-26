#include "pch.h"

#include <string>
#include <concepts>
#include <iostream>
#include <regex>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/FundamentallyBackedRealNumber.h"
#include "../CmdCalculator/RealNumber.h"

using namespace std::string_literals;


namespace CmdCalculatorTests
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


	static constexpr std::string getNameOfESign(const CmdCalculator::Arithmetic::ESign sign)
	{
		switch (sign)
		{
		case CmdCalculator::Arithmetic::ESign::Negative:
			return "Negative"s;
		case CmdCalculator::Arithmetic::ESign::Neutral:
			return "Neutral"s;
		case CmdCalculator::Arithmetic::ESign::Positive:
			return "Positive"s;
		default:
			return "UNKNOWN"s;
		}
	}


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

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_getZero_TestData<InnerType, ZeroV>& testData)
		{
			os << nameOfInnerType<InnerType> << '{' << testData.zeroValue << '}';
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
		FundamentallyBackedRealNumbergetZero_Types
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
			.innerValue{ 0.001 },
			.expectedStringRepresentationRegex{ "\\s*\\+?\\s*0+\\.0010*\\s*" }
		},
		{
			.innerValue{ 1.0 },
			.expectedStringRepresentationRegex{ "\\s*\\+?\\s*0*1(\\.0*)?\\s*" }
		},
		{
			.innerValue{ 12.34 },
			.expectedStringRepresentationRegex{ "\\s*\\+?\\s*0*12\\.340*\\s*" }
		},
		{
			.innerValue{ 56.78 },
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


#pragma region getSign

	struct FundamentallyBackedRealNumber_getSign_TestData
	{
		double innerValue;
		CmdCalculator::Arithmetic::ESign expectedSign;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_getSign_TestData& testData)
		{
			os
				<< "FundamentallyBackedRealNumber{"
				<< testData.innerValue
				<< "}.getSign() == "
				<< getNameOfESign(testData.expectedSign)
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumbergetSignTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_getSign_TestData>
	{};


	const auto FundamentallyBackedRealNumber_getSign_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::orderedOperandDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_getSign_TestData
				{
					.innerValue{ data.value },
					.expectedSign{ data.sign }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumbergetSignTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_getSign_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumbergetSignTests, getSign$returns$expected$value)
	{
		// Arrange
		const double innerValue{ GetParam().innerValue};
		const CmdCalculator::Arithmetic::ESign expected{ GetParam().expectedSign };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> instance
		{
			innerValue
		};
		// Act
		const CmdCalculator::Arithmetic::ESign actual{ instance.getSign() };

		// Assert
		EXPECT_EQ(expected, actual);
	}

#pragma endregion


#pragma region getAbsoluteValue

	struct FundamentallyBackedRealNumber_getAbsoluteValue_TestData
	{
		double innerValue;
		double expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_getAbsoluteValue_TestData& testData)
		{
			os
				<< "FundamentallyBackedRealNumber{"
				<< testData.innerValue
				<< "}.getAbsoluteValue() == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumbergetAbsoluteValueTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_getAbsoluteValue_TestData>
	{};


	const auto FundamentallyBackedRealNumber_getAbsoluteValue_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::absoluteValueOperationsDataValues()
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_getAbsoluteValue_TestData
				{
					.innerValue{ data.operand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumbergetAbsoluteValueTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_getAbsoluteValue_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumbergetAbsoluteValueTests, getAbsoluteValue$returns$expected$value)
	{
		// Arrange
		const double innerValue{ GetParam().innerValue};
		const double expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> instance
		{
			innerValue
		};
		// Act
		const double actual{ instance.getAbsoluteValue().getInnerValue() };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region getWholePart

	struct FundamentallyBackedRealNumber_getWholePart_TestData
	{
		double innerValue;
		double expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_getWholePart_TestData& testData)
		{
			os
				<< "FundamentallyBackedRealNumber{"
				<< testData.innerValue
				<< "}.getWholePart() == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumbergetWholePartTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_getWholePart_TestData>
	{};


	const FundamentallyBackedRealNumber_getWholePart_TestData FundamentallyBackedRealNumber_getWholePart_TestDataValues[]
	{
		{
			.innerValue{ -12.34 },
			.expected{ -12 }
		},
		{
			.innerValue{ -1.0 },
			.expected{ -1 }
		},
		{
			.innerValue{ -0.123 },
			.expected{ 0 }
		},
		{
			.innerValue{ 0 },
			.expected{ 0 }
		},
		{
			.innerValue{ 0.123 },
			.expected{ 0 }
		},
		{
			.innerValue{ 1.0 },
			.expected{ 1 }
		},
		{
			.innerValue{ 12.34 },
			.expected{ 12 }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumbergetWholePartTests,
		testing::ValuesIn(FundamentallyBackedRealNumber_getWholePart_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumbergetWholePartTests, getWholePart$returns$expected$value)
	{
		// Arrange
		const double innerValue{ GetParam().innerValue};
		const double expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> instance
		{
			innerValue
		};
		// Act
		const double actual{ instance.getWholePart().getInnerValue() };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region pow

	struct FundamentallyBackedRealNumber_pow_TestData
	{
		double baseInnerValue;
		double exponentInnerValue;
		double expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_pow_TestData& testData)
		{
			os
				<< "FundamentallyBackedRealNumber{"
				<< testData.baseInnerValue
				<< "}.pow(FundamentallyBackedRealNumber{"
				<< testData.exponentInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberpowTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_pow_TestData>
	{};


	const auto FundamentallyBackedRealNumber_pow_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::exponentiationOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_pow_TestData
				{
					.baseInnerValue{ data.leftOperand },
					.exponentInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberpowTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_pow_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumberpowTests, pow$returns$expected$value)
	{
		// Arrange
		const double innerValue{ GetParam().baseInnerValue };
		const double exponentInnerValue{ GetParam().exponentInnerValue };
		const double expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> instance
		{
			innerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> exponent
		{
			exponentInnerValue
		};
		// Act
		const double actual{ instance.pow(exponent).getInnerValue() };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region nthRoot

	struct FundamentallyBackedRealNumber_nthRoot_TestData
	{
		double degreeInnerValue;
		double radicandInnerValue;
		double expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_nthRoot_TestData& testData)
		{
			os
				<< "FundamentallyBackedRealNumber{"
				<< testData.degreeInnerValue
				<< "}.nthRoot(FundamentallyBackedRealNumber{"
				<< testData.radicandInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumbernthRootTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_nthRoot_TestData>
	{};


	const auto FundamentallyBackedRealNumber_nthRoot_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::nthRootOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_nthRoot_TestData
				{
					.degreeInnerValue{ data.leftOperand },
					.radicandInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumbernthRootTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_nthRoot_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumbernthRootTests, nthRoot$returns$expected$value)
	{
		// Arrange
		const double radicandInnerValue{ GetParam().radicandInnerValue };
		const double degreeInnerValue{ GetParam().degreeInnerValue };
		const double expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> radicand
		{
			radicandInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> degree
		{
			degreeInnerValue
		};
		// Act
		const double actual{ radicand.nthRoot(degree).getInnerValue() };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region Operators

#pragma region Comparison operators

#pragma region Equality

	struct FundamentallyBackedRealNumber_equality_operator_TestData
	{
		double lhsInnerValue;
		double rhsInnerValue;
		bool expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_equality_operator_TestData& testData)
		{
			os
				<< "(FundamentallyBackedRealNumber{"
				<< testData.lhsInnerValue
				<< "} == FundamentallyBackedRealNumber{"
				<< testData.rhsInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberEqualityOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_equality_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_equality_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::equalityOperationDataValues()
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_equality_operator_TestData
				{
					.lhsInnerValue{ data.leftOperand },
					.rhsInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberEqualityOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_equality_operator_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumberEqualityOperatorTests, equality$operator$returns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const bool expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};
		// Act
		const bool actual{ lhs == rhs };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region Inequality

	struct FundamentallyBackedRealNumber_inequality_operator_TestData
	{
		double lhsInnerValue;
		double rhsInnerValue;
		bool expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_inequality_operator_TestData& testData)
		{
			os
				<< "(FundamentallyBackedRealNumber{"
				<< testData.lhsInnerValue
				<< "} != FundamentallyBackedRealNumber{"
				<< testData.rhsInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberInequalityOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_inequality_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_inequality_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::inequalityOperationDataValues()
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_inequality_operator_TestData
				{
					.lhsInnerValue{ data.leftOperand },
					.rhsInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberInequalityOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_inequality_operator_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumberInequalityOperatorTests, inequality$operator$returns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const bool expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};
		// Act
		const bool actual{ lhs != rhs };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region Less Than

	struct FundamentallyBackedRealNumber_lessThan_operator_TestData
	{
		double lhsInnerValue;
		double rhsInnerValue;
		bool expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_lessThan_operator_TestData& testData)
		{
			os
				<< "(FundamentallyBackedRealNumber{"
				<< testData.lhsInnerValue
				<< "} < FundamentallyBackedRealNumber{"
				<< testData.rhsInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberLessThanOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_lessThan_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_lessThan_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::lessThanOperationDataValues()
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_lessThan_operator_TestData
				{
					.lhsInnerValue{ data.leftOperand },
					.rhsInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberLessThanOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_lessThan_operator_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumberLessThanOperatorTests, lessThan$operator$returns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const bool expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};

		// Act
		const bool actual{ lhs < rhs };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region Less Than or Equal To

	struct FundamentallyBackedRealNumber_lessThanEqualTo_operator_TestData
	{
		double lhsInnerValue;
		double rhsInnerValue;
		bool expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_lessThanEqualTo_operator_TestData& testData)
		{
			os
				<< "(FundamentallyBackedRealNumber{"
				<< testData.lhsInnerValue
				<< "} <= FundamentallyBackedRealNumber{"
				<< testData.rhsInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberLessThanEqualToOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_lessThanEqualTo_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_lessThanEqualTo_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::lessThanEqualToOperationDataValues()
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_lessThanEqualTo_operator_TestData
				{
					.lhsInnerValue{ data.leftOperand },
					.rhsInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberLessThanEqualToOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_lessThanEqualTo_operator_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumberLessThanEqualToOperatorTests, lessThanEqualTo$operator$returns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const bool expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};

		// Act
		const bool actual{ lhs <= rhs };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region Greater Than

	struct FundamentallyBackedRealNumber_greaterThan_operator_TestData
	{
		double lhsInnerValue;
		double rhsInnerValue;
		bool expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_greaterThan_operator_TestData& testData)
		{
			os
				<< "(FundamentallyBackedRealNumber{"
				<< testData.lhsInnerValue
				<< "} > FundamentallyBackedRealNumber{"
				<< testData.rhsInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberGreaterThanOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_greaterThan_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_greaterThan_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::greaterThanOperationDataValues()
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_greaterThan_operator_TestData
				{
					.lhsInnerValue{ data.leftOperand },
					.rhsInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberGreaterThanOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_greaterThan_operator_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumberGreaterThanOperatorTests, greaterThan$operator$returns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const bool expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};

		// Act
		const bool actual{ lhs > rhs };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region Greater Than or Equal To

	struct FundamentallyBackedRealNumber_greaterThanEqualTo_operator_TestData
	{
		double lhsInnerValue;
		double rhsInnerValue;
		bool expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_greaterThanEqualTo_operator_TestData& testData)
		{
			os
				<< "(FundamentallyBackedRealNumber{"
				<< testData.lhsInnerValue
				<< "} >= FundamentallyBackedRealNumber{"
				<< testData.rhsInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberGreaterThanEqualToOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_greaterThanEqualTo_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_greaterThanEqualTo_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::greaterThanEqualToOperationDataValues()
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_greaterThanEqualTo_operator_TestData
				{
					.lhsInnerValue{ data.leftOperand },
					.rhsInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberGreaterThanEqualToOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_greaterThanEqualTo_operator_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumberGreaterThanEqualToOperatorTests, greaterThanEqualTo$operator$returns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const bool expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};

		// Act
		const bool actual{ lhs >= rhs };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion

#pragma endregion


#pragma region Unary arithmetic operators

#pragma region Negation

	struct FundamentallyBackedRealNumber_negation_operator_TestData
	{
		double innerValue;
		double expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_negation_operator_TestData& testData)
		{
			os
				<< "-FundamentallyBackedRealNumber{"
				<< testData.innerValue
				<< "} == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberNegationOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_negation_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_negation_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::negationOperationsDataValues()
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_negation_operator_TestData
				{
					.innerValue{ data.operand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberNegationOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_negation_operator_TestDataValues)
	);
	
	TEST_P(FundamentallyBackedRealNumberNegationOperatorTests, negation$operator$returns$expected$value)
	{
		// Arrange
		const double innerValue{ GetParam().innerValue };
		const double expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> instance
		{
			innerValue
		};
		// Act
		const double actual{ -instance.getInnerValue() };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region Incrementation

	struct FundamentallyBackedRealNumber_incrementation_operator_TestData
	{
		double innerValueBeforeIncrementation;
		double innerValueAfterIncrementation;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_incrementation_operator_TestData& testData)
		{
			os
				<< "FundamentallyBackedRealNumber{"
				<< testData.innerValueBeforeIncrementation
				<< "}++ == "
				<< testData.innerValueAfterIncrementation
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberIncrementationOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_incrementation_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_incrementation_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::incrementationOperationsDataValues()
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_incrementation_operator_TestData
				{
					.innerValueBeforeIncrementation{ data.operand },
					.innerValueAfterIncrementation{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberIncrementationOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_incrementation_operator_TestDataValues)
	);

	
	TEST_P(FundamentallyBackedRealNumberIncrementationOperatorTests, prefix$incrementation$operator$returns$and$sets$expected$value)
	{
		// Arrange
		const double innerValue{ GetParam().innerValueBeforeIncrementation };
		const double expectedInnerValue{ GetParam().innerValueAfterIncrementation };
		const double expectedReturnValue{ GetParam().innerValueAfterIncrementation };
		CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> instance
		{
			innerValue
		};
		// Act
		const double actualReturnValue{ (++instance).getInnerValue()};

		// Assert
		EXPECT_DOUBLE_EQ(expectedInnerValue, instance.getInnerValue());
		EXPECT_DOUBLE_EQ(expectedReturnValue, actualReturnValue);
	}
	
	
	TEST_P(FundamentallyBackedRealNumberIncrementationOperatorTests, postfix$incrementation$operator$returns$and$sets$expected$value)
	{
		// Arrange
		const double innerValue{ GetParam().innerValueBeforeIncrementation };
		const double expectedInnerValue{ GetParam().innerValueAfterIncrementation };
		const double expectedReturnValue{ GetParam().innerValueBeforeIncrementation };
		CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> instance
		{
			innerValue
		};
		// Act
		const double actualReturnValue{ (instance++).getInnerValue()};

		// Assert
		EXPECT_DOUBLE_EQ(expectedInnerValue, instance.getInnerValue());
		EXPECT_DOUBLE_EQ(expectedReturnValue, actualReturnValue);
	}

#pragma endregion


#pragma region Decrementation

	struct FundamentallyBackedRealNumber_decrementation_operator_TestData
	{
		double innerValueBeforeDecrementation;
		double innerValueAfterDecrementation;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_decrementation_operator_TestData& testData)
		{
			os
				<< "FundamentallyBackedRealNumber{"
				<< testData.innerValueBeforeDecrementation
				<< "}-- == "
				<< testData.innerValueAfterDecrementation
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberDecrementationOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_decrementation_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_decrementation_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::decrementationOperationsDataValues()
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_decrementation_operator_TestData
				{
					.innerValueBeforeDecrementation{ data.operand },
					.innerValueAfterDecrementation{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberDecrementationOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_decrementation_operator_TestDataValues)
	);

	
	TEST_P(FundamentallyBackedRealNumberDecrementationOperatorTests, prefix$decrementation$operator$returns$and$sets$expected$value)
	{
		// Arrange
		const double innerValue{ GetParam().innerValueBeforeDecrementation };
		const double expectedInnerValue{ GetParam().innerValueAfterDecrementation };
		const double expectedReturnValue{ GetParam().innerValueAfterDecrementation };
		CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> instance
		{
			innerValue
		};
		// Act
		const double actualReturnValue{ (--instance).getInnerValue()};

		// Assert
		EXPECT_DOUBLE_EQ(expectedInnerValue, instance.getInnerValue());
		EXPECT_DOUBLE_EQ(expectedReturnValue, actualReturnValue);
	}
	
	
	TEST_P(FundamentallyBackedRealNumberDecrementationOperatorTests, postfix$decrementation$operator$returns$and$sets$expected$value)
	{
		// Arrange
		const double innerValue{ GetParam().innerValueBeforeDecrementation };
		const double expectedInnerValue{ GetParam().innerValueAfterDecrementation };
		const double expectedReturnValue{ GetParam().innerValueBeforeDecrementation };
		CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> instance
		{
			innerValue
		};
		// Act
		const double actualReturnValue{ (instance--).getInnerValue()};

		// Assert
		EXPECT_DOUBLE_EQ(expectedInnerValue, instance.getInnerValue());
		EXPECT_DOUBLE_EQ(expectedReturnValue, actualReturnValue);
	}

#pragma endregion

#pragma endregion


#pragma region Binary arithmetic operations

#pragma region Addition

	struct FundamentallyBackedRealNumber_addition_operator_TestData
	{
		double lhsInnerValue;
		double rhsInnerValue;
		double expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_addition_operator_TestData& testData)
		{
			os
				<< "(FundamentallyBackedRealNumber{"
				<< testData.lhsInnerValue
				<< "} + FundamentallyBackedRealNumber{"
				<< testData.rhsInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberAdditionOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_addition_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_addition_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::additionOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_addition_operator_TestData
				{
					.lhsInnerValue{ data.leftOperand },
					.rhsInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberAdditionOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_addition_operator_TestDataValues)
	);


	TEST_P(FundamentallyBackedRealNumberAdditionOperatorTests, addition$equality$operator$assigns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const double expected{ GetParam().expected };
		CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};
		// Act
		lhs += rhs;

		// Assert
		EXPECT_DOUBLE_EQ(expected, lhs.getInnerValue());
	}


	TEST_P(FundamentallyBackedRealNumberAdditionOperatorTests, addition$operator$returns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const double expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};
		// Act
		const double actual{ (lhs + rhs).getInnerValue() };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region Subtraction

	struct FundamentallyBackedRealNumber_subtraction_operator_TestData
	{
		double lhsInnerValue;
		double rhsInnerValue;
		double expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_subtraction_operator_TestData& testData)
		{
			os
				<< "(FundamentallyBackedRealNumber{"
				<< testData.lhsInnerValue
				<< "} - FundamentallyBackedRealNumber{"
				<< testData.rhsInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberSubtractionOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_subtraction_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_subtraction_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::subtractionOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_subtraction_operator_TestData
				{
					.lhsInnerValue{ data.leftOperand },
					.rhsInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberSubtractionOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_subtraction_operator_TestDataValues)
	);


	TEST_P(FundamentallyBackedRealNumberSubtractionOperatorTests, subtraction$equality$operator$assigns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const double expected{ GetParam().expected };
		CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};

		// Act
		lhs -= rhs;

		// Assert
		EXPECT_DOUBLE_EQ(expected, lhs.getInnerValue());
	}


	TEST_P(FundamentallyBackedRealNumberSubtractionOperatorTests, subtraction$operator$returns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const double expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};

		// Act
		const double actual{ (lhs - rhs).getInnerValue() };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region Multiplication

	struct FundamentallyBackedRealNumber_multiplication_operator_TestData
	{
		double lhsInnerValue;
		double rhsInnerValue;
		double expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_multiplication_operator_TestData& testData)
		{
			os
				<< "(FundamentallyBackedRealNumber{"
				<< testData.lhsInnerValue
				<< "} * FundamentallyBackedRealNumber{"
				<< testData.rhsInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberMultiplicationOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_multiplication_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_multiplication_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::multiplicationOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_multiplication_operator_TestData
				{
					.lhsInnerValue{ data.leftOperand },
					.rhsInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberMultiplicationOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_multiplication_operator_TestDataValues)
	);


	TEST_P(FundamentallyBackedRealNumberMultiplicationOperatorTests, multiplication$equality$operator$assigns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const double expected{ GetParam().expected };
		CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};

		// Act
		lhs *= rhs;

		// Assert
		EXPECT_DOUBLE_EQ(expected, lhs.getInnerValue());
	}


	TEST_P(FundamentallyBackedRealNumberMultiplicationOperatorTests, multiplication$operator$returns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const double expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};

		// Act
		const double actual{ (lhs * rhs).getInnerValue() };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region Division

	struct FundamentallyBackedRealNumber_division_operator_TestData
	{
		double lhsInnerValue;
		double rhsInnerValue;
		double expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_division_operator_TestData& testData)
		{
			os
				<< "(FundamentallyBackedRealNumber{"
				<< testData.lhsInnerValue
				<< "} / FundamentallyBackedRealNumber{"
				<< testData.rhsInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberDivisionOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_division_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_division_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::divisionOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_division_operator_TestData
				{
					.lhsInnerValue{ data.leftOperand },
					.rhsInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberDivisionOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_division_operator_TestDataValues)
	);


	TEST_P(FundamentallyBackedRealNumberDivisionOperatorTests, division$equality$operator$assigns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const double expected{ GetParam().expected };
		CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};

		// Act
		lhs /= rhs;

		// Assert
		EXPECT_DOUBLE_EQ(expected, lhs.getInnerValue());
	}


	TEST_P(FundamentallyBackedRealNumberDivisionOperatorTests, division$operator$returns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const double expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};

		// Act
		const double actual{ (lhs / rhs).getInnerValue() };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion


#pragma region Modulo

	struct FundamentallyBackedRealNumber_modulo_operator_TestData
	{
		double lhsInnerValue;
		double rhsInnerValue;
		double expected;

		friend std::ostream& operator<<(std::ostream& os, const FundamentallyBackedRealNumber_modulo_operator_TestData& testData)
		{
			os
				<< "(FundamentallyBackedRealNumber{"
				<< testData.lhsInnerValue
				<< "} % FundamentallyBackedRealNumber{"
				<< testData.rhsInnerValue
				<< "}) == "
				<< testData.expected
			;
			return os;
		}
	};
	
	
	class FundamentallyBackedRealNumberModuloOperatorTests :
		public testing::TestWithParam<FundamentallyBackedRealNumber_modulo_operator_TestData>
	{};


	const auto FundamentallyBackedRealNumber_modulo_operator_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::moduloOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return FundamentallyBackedRealNumber_modulo_operator_TestData
				{
					.lhsInnerValue{ data.leftOperand },
					.rhsInnerValue{ data.rightOperand },
					.expected{ data.result }
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FundamentallyBackedRealNumberTests,
		FundamentallyBackedRealNumberModuloOperatorTests,
		CmdCalculatorTestUtils::ValuesInRange(FundamentallyBackedRealNumber_modulo_operator_TestDataValues)
	);

	TEST_P(FundamentallyBackedRealNumberModuloOperatorTests, modulo$equality$operator$assigns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const double expected{ GetParam().expected };
		CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};

		// Act
		lhs %= rhs;

		// Assert
		EXPECT_DOUBLE_EQ(expected, lhs.getInnerValue());
	}


	TEST_P(FundamentallyBackedRealNumberModuloOperatorTests, modulo$operator$returns$expected$value)
	{
		// Arrange
		const double lhsInnerValue{ GetParam().lhsInnerValue };
		const double rhsInnerValue{ GetParam().rhsInnerValue };
		const double expected{ GetParam().expected };
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> lhs
		{
			lhsInnerValue
		};
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<double> rhs
		{
			rhsInnerValue
		};

		// Act
		const double actual{ (lhs % rhs).getInnerValue() };

		// Assert
		EXPECT_DOUBLE_EQ(expected, actual);
	}

#pragma endregion

#pragma endregion

#pragma endregion
}