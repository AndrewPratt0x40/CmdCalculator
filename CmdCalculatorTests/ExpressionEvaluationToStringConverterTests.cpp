#include "pch.h"

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/ExpressionEvaluationToStringConverter.h"
#include "../CmdCalculator/ExpressionToStringConverter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <functional>
#include <regex>


namespace CmdCalculatorTests
{
#pragma region Concept satisfaction
	
	TEST(ExpressionEvaluationToStringConverterTests, ExpressionEvaluationToStringConverter$satisfies$the$ExpressionToStringConverter$concept)
	{
		static_assert
		(
			CmdCalculator::ExpressionToStringConverter
			<
				CmdCalculator::ExpressionEvaluationToStringConverter
				<
					CmdCalculatorTestDoubles::Expressions::StubDynamicExpression
					<
						CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
					>
				>
			>
		);
	}

#pragma endregion


#pragma region stringifyExpression

#pragma region stringifyExpression test data

	const std::regex stringifyExpressionRegex{ "^\\s*([+-])?\\s*(\\d*)\\s*(\\.\\s*(\\d*))?\\s*$" };
	enum stringifyExpressionRegexSubgroups : size_t
	{
		FullMatch = 0,
		Sign = 1,
		WholeDigits = 2,
		FractionalPart = 3,
		FractionalDigits = 4
	};


	struct ExpressionEvaluationToStringConverter_stringifyExpression_TestData
	{
		double evaluation;
		CmdCalculator::Arithmetic::ESign evaluationSign;
		bool evaluationIsInteger;
		bool evaluationWholePartIsZero;
		std::string evaluationStr;
		std::string evaluationWholePartStr;
		std::string evaluationFractionalPartStr;
		int precision;
		bool shouldPreferDecimalsOverIntegers;
		bool shouldPreferSignExpressionForPositiveValues;
		bool shouldPreferLeadingZeroOverWholelessNumbers;
		bool shouldPreferTrailingZeroOverEmptyDecimalPlace;


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const ExpressionEvaluationToStringConverter_stringifyExpression_TestData& testData
		)
		{
			ostream
				<< "ExpressionEvaluationToStringConverter.stringifyExpression(Expression{"
				<< testData.evaluationStr
				<< "}, CalculationConfiguration{"
				<< testData.precision
				<< ", "
				<< testData.shouldPreferDecimalsOverIntegers
				<< ", "
				<< testData.shouldPreferSignExpressionForPositiveValues
				<< ", "
				<< testData.shouldPreferLeadingZeroOverWholelessNumbers
				<< ", "
				<< testData.shouldPreferTrailingZeroOverEmptyDecimalPlace
				<< "})"
			;

			return ostream;
		}
	};


	class ExpressionEvaluationToStringConverter$stringifyExpression$Tests :
		public testing::TestWithParam<ExpressionEvaluationToStringConverter_stringifyExpression_TestData>
	{};

	class ExpressionEvaluationToStringConverter$stringifyExpression$WithIntsOnlyTests :
		public testing::TestWithParam<ExpressionEvaluationToStringConverter_stringifyExpression_TestData>
	{};

	class ExpressionEvaluationToStringConverter$stringifyExpression$WithZeroWholePartsOnly$Tests :
		public testing::TestWithParam<ExpressionEvaluationToStringConverter_stringifyExpression_TestData>
	{};

	class ExpressionEvaluationToStringConverter$stringifyExpression$WithNonZeroWholePartsOnly$Tests :
		public testing::TestWithParam<ExpressionEvaluationToStringConverter_stringifyExpression_TestData>
	{};


	constexpr inline static bool isValidOperandDataValuesFor_stringifyExpressionTest
	(
		const CmdCalculatorTestUtils::SharedTestData::CompositeOperandData<double>& compositeValue
	)
	{
		return compositeValue.isInteger.has_value()
			&& compositeValue.isAbsoluteValueAtLeastOne.has_value()
			&& compositeValue.wholePartStr.has_value()
			&& compositeValue.fractionalPartStr.has_value()
		;
	}


	constexpr inline CmdCalculatorTestUtils::SharedTestData::CompositeOperandDataRange auto operandDataValuesFor_stringifyExpressionTests()
	{
		return
			CmdCalculatorTestUtils::SharedTestData::orderedOperandDataValues
			| std::views::filter(isValidOperandDataValuesFor_stringifyExpressionTest)
		;
	};

	const int valid_stringifyExpressionPrecisionValues[]
	{
		0, 1, 2, 3, 4, 5,
		8, 16, 32
	};


	static const CmdCalculatorTestUtils::ForwardRangeOf<std::string> auto getPossibleEvaluationStrs
	(
		const CmdCalculatorTestUtils::SharedTestData::CompositeOperandData<double>& compositeValue
	)
	{
		std::vector<std::string> evalStrs{};
		if (!isValidOperandDataValuesFor_stringifyExpressionTest(compositeValue))
			return evalStrs;

		std::vector<std::string> signPrefixes{};
		if (compositeValue.sign != CmdCalculator::Arithmetic::ESign::Negative)
		{
			signPrefixes.push_back("");
			signPrefixes.push_back("+");
		}
		if (compositeValue.sign != CmdCalculator::Arithmetic::ESign::Positive)
			signPrefixes.push_back("-");


		for (const std::string signPrefix : signPrefixes)
		{
			for (const std::string digitsPrefix : {"", "0", "000"})
			{
				if (compositeValue.isInteger)
				{
					evalStrs.push_back
					(
						std::format
						(
							"{}{}{}",
							signPrefix,
							digitsPrefix,
							compositeValue.wholePartStr.value()
						)
					);
				}

				for (const std::string digitsSuffix : {"", "0", "000"})
				{
					if (compositeValue.isInteger)
					{
						evalStrs.push_back
						(
							std::format
							(
								"{}{}{}.{}",
								signPrefix,
								digitsPrefix,
								compositeValue.wholePartStr.value(),
								digitsSuffix
							)
						);
					}
					else
					{
						evalStrs.push_back
						(
							std::format
							(
								"{}{}{}.{}{}",
								signPrefix,
								digitsPrefix,
								compositeValue.wholePartStr.value(),
								compositeValue.fractionalPartStr.value(),
								digitsSuffix
							)
						);
					}
				}
			}
		}

		return evalStrs;
	}


	const std::ranges::forward_range auto ExpressionEvaluationToStringConverter_stringifyExpression_TestDataValues
	{
		[]()
		{
			std::vector<ExpressionEvaluationToStringConverter_stringifyExpression_TestData> values{};

			for(const CmdCalculatorTestUtils::SharedTestData::CompositeOperandData<double>& compositeValue : operandDataValuesFor_stringifyExpressionTests()){
			for(const std::string evaluationStr : getPossibleEvaluationStrs(compositeValue)){
			for(const int precision : valid_stringifyExpressionPrecisionValues){
			for(const bool shouldPreferDecimalsOverIntegers : CmdCalculatorTestUtils::SharedTestData::allBools){
			for(const bool shouldPreferSignExpressionForPositiveValues : CmdCalculatorTestUtils::SharedTestData::allBools){
			for(const bool shouldPreferLeadingZeroOverWholelessNumbers : CmdCalculatorTestUtils::SharedTestData::allBools){
			for(const bool shouldPreferTrailingZeroOverEmptyDecimalPlace : CmdCalculatorTestUtils::SharedTestData::allBools)
			{
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
						.evaluation{ compositeValue.value },
						.evaluationSign{ compositeValue.sign },
						.evaluationIsInteger{ compositeValue.isInteger.value() },
						.evaluationWholePartIsZero{ compositeValue.isAbsoluteValueAtLeastOne.value() },
						.evaluationStr{ evaluationStr },
						.evaluationWholePartStr{ static_cast<std::string>(compositeValue.wholePartStr.value()) },
						.evaluationFractionalPartStr{ static_cast<std::string>(compositeValue.fractionalPartStr.value()) },
						.precision{ precision },
						.shouldPreferDecimalsOverIntegers{ shouldPreferDecimalsOverIntegers },
						.shouldPreferSignExpressionForPositiveValues{ shouldPreferSignExpressionForPositiveValues },
						.shouldPreferLeadingZeroOverWholelessNumbers{ shouldPreferLeadingZeroOverWholelessNumbers },
						.shouldPreferTrailingZeroOverEmptyDecimalPlace{ shouldPreferTrailingZeroOverEmptyDecimalPlace }
					}
				);
			}}}}}}}

			return values;
		}()
	};


	const std::ranges::forward_range auto ExpressionEvaluationToStringConverter_stringifyExpression_WithIntsOnlyTestDataValues
	{
		[]()
		{
			return
				ExpressionEvaluationToStringConverter_stringifyExpression_TestDataValues
				| std::views::filter
				(
					[](const ExpressionEvaluationToStringConverter_stringifyExpression_TestData& testData)
					{ return testData.evaluationIsInteger; }
				)
			;
		}()
	};


	const std::ranges::forward_range auto ExpressionEvaluationToStringConverter_stringifyExpression_WithZeroWholePartsOnlyTestDataValues
	{
		[]()
		{
			return
				ExpressionEvaluationToStringConverter_stringifyExpression_TestDataValues
				| std::views::filter
				(
					[](const ExpressionEvaluationToStringConverter_stringifyExpression_TestData& testData)
					{ return testData.evaluationWholePartIsZero; }
				)
			;
		}()
	};


	const std::ranges::forward_range auto ExpressionEvaluationToStringConverter_stringifyExpression_WithNonZeroWholePartsOnlyTestDataValues
	{
		[]()
		{
			return
				ExpressionEvaluationToStringConverter_stringifyExpression_TestDataValues
				| std::views::filter
				(
					[](const ExpressionEvaluationToStringConverter_stringifyExpression_TestData& testData)
					{ return !testData.evaluationWholePartIsZero; }
				)
			;
		}()
	};


	INSTANTIATE_TEST_CASE_P
	(
		ExpressionEvaluationToStringConverterTests,
		ExpressionEvaluationToStringConverter$stringifyExpression$Tests,
		CmdCalculatorTestUtils::ValuesInRange(ExpressionEvaluationToStringConverter_stringifyExpression_TestDataValues)
	);


	INSTANTIATE_TEST_CASE_P
	(
		ExpressionEvaluationToStringConverterTests,
		ExpressionEvaluationToStringConverter$stringifyExpression$WithIntsOnlyTests,
		CmdCalculatorTestUtils::ValuesInRange(ExpressionEvaluationToStringConverter_stringifyExpression_WithIntsOnlyTestDataValues)
	);


	INSTANTIATE_TEST_CASE_P
	(
		ExpressionEvaluationToStringConverterTests,
		ExpressionEvaluationToStringConverter$stringifyExpression$WithZeroWholePartsOnly$Tests,
		CmdCalculatorTestUtils::ValuesInRange(ExpressionEvaluationToStringConverter_stringifyExpression_WithZeroWholePartsOnlyTestDataValues)
	);


	INSTANTIATE_TEST_CASE_P
	(
		ExpressionEvaluationToStringConverterTests,
		ExpressionEvaluationToStringConverter$stringifyExpression$WithNonZeroWholePartsOnly$Tests,
		CmdCalculatorTestUtils::ValuesInRange(ExpressionEvaluationToStringConverter_stringifyExpression_WithNonZeroWholePartsOnlyTestDataValues)
	);

#pragma endregion


	TEST_P(ExpressionEvaluationToStringConverter$stringifyExpression$Tests, calling$stringifyExpression$returns$value$with$valid$format)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using SourceExpressionType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		const NumberType sourceEvaluation{ GetParam().evaluationStr, GetParam().evaluation };
		const SourceExpressionType source{ sourceEvaluation };
		const CmdCalculator::CalculationConfiguration configuration
		{
			GetParam().precision,
			GetParam().shouldPreferDecimalsOverIntegers,
			GetParam().shouldPreferSignExpressionForPositiveValues,
			GetParam().shouldPreferLeadingZeroOverWholelessNumbers,
			GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace
		};

		const CmdCalculator::ExpressionEvaluationToStringConverter<SourceExpressionType> instance{};

		// Act
		const std::string returnValue{ instance.stringifyExpression(source, configuration) };

		// Assert
		EXPECT_TRUE(std::regex_match(returnValue, stringifyExpressionRegex));
	}


	TEST_P(ExpressionEvaluationToStringConverter$stringifyExpression$Tests, calling$stringifyExpression$returns$value$with$correct$sign)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using SourceExpressionType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		const NumberType sourceEvaluation{ GetParam().evaluationStr, GetParam().evaluation };
		const SourceExpressionType source{ sourceEvaluation };
		const CmdCalculator::CalculationConfiguration configuration
		{
			GetParam().precision,
			GetParam().shouldPreferDecimalsOverIntegers,
			GetParam().shouldPreferSignExpressionForPositiveValues,
			GetParam().shouldPreferLeadingZeroOverWholelessNumbers,
			GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace
		};

		const CmdCalculator::ExpressionEvaluationToStringConverter<SourceExpressionType> instance{};

		// Act
		const std::string returnValue{ instance.stringifyExpression(source, configuration) };

		// Assert
		std::smatch returnValueMatchResult;
		ASSERT_TRUE(std::regex_match(returnValue, returnValueMatchResult, stringifyExpressionRegex));

		const std::string returnValueSign{ returnValueMatchResult[stringifyExpressionRegexSubgroups::Sign].str() };
		switch (GetParam().evaluationSign)
		{
		case CmdCalculator::Arithmetic::ESign::Negative:
			EXPECT_EQ("-", returnValueSign);
			break;
		case CmdCalculator::Arithmetic::ESign::Neutral:
			EXPECT_TRUE(std::regex_match(returnValueSign, std::regex{ "^[-+]?$" }));
			break;
		case CmdCalculator::Arithmetic::ESign::Positive:
			EXPECT_TRUE(std::regex_match(returnValueSign, std::regex{ "\\+?$" }));
			break;
		default:
			FAIL();
		}
	}


	TEST_P(ExpressionEvaluationToStringConverter$stringifyExpression$Tests, calling$stringifyExpression$returns$value$with$correct$whole$part)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using SourceExpressionType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		const NumberType sourceEvaluation{ GetParam().evaluationStr, GetParam().evaluation };
		const SourceExpressionType source{ sourceEvaluation };
		const CmdCalculator::CalculationConfiguration configuration
		{
			GetParam().precision,
			GetParam().shouldPreferDecimalsOverIntegers,
			GetParam().shouldPreferSignExpressionForPositiveValues,
			GetParam().shouldPreferLeadingZeroOverWholelessNumbers,
			GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace
		};

		const CmdCalculator::ExpressionEvaluationToStringConverter<SourceExpressionType> instance{};

		// Act
		const std::string returnValue{ instance.stringifyExpression(source, configuration) };

		// Assert
		std::smatch returnValueMatchResult;
		ASSERT_TRUE(std::regex_match(returnValue, returnValueMatchResult, stringifyExpressionRegex));

		const std::string returnValueWholeDigits{ returnValueMatchResult[stringifyExpressionRegexSubgroups::WholeDigits].str() };

		std::smatch returnValueWholeDigitsWithoutLeadingZerosMatchResult;
		ASSERT_TRUE
		(
			std::regex_match
			(
				returnValueWholeDigits,
				returnValueWholeDigitsWithoutLeadingZerosMatchResult,
				std::regex{ "^0*(\\d*)$" }
			)
		);
		const std::string returnValueWholeDigitsWithoutLeadingZeros{ returnValueWholeDigitsWithoutLeadingZerosMatchResult[1].str() };

		EXPECT_EQ(GetParam().evaluationWholePartStr, returnValueWholeDigitsWithoutLeadingZeros);
	}


	TEST_P(ExpressionEvaluationToStringConverter$stringifyExpression$Tests, calling$stringifyExpression$returns$value$with$correct$fractional$part)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using SourceExpressionType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		const NumberType sourceEvaluation{ GetParam().evaluationStr, GetParam().evaluation };
		const SourceExpressionType source{ sourceEvaluation };
		const CmdCalculator::CalculationConfiguration configuration
		{
			GetParam().precision,
			GetParam().shouldPreferDecimalsOverIntegers,
			GetParam().shouldPreferSignExpressionForPositiveValues,
			GetParam().shouldPreferLeadingZeroOverWholelessNumbers,
			GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace
		};

		const CmdCalculator::ExpressionEvaluationToStringConverter<SourceExpressionType> instance{};

		// Act
		const std::string returnValue{ instance.stringifyExpression(source, configuration) };

		// Assert
		std::smatch returnValueMatchResult;
		ASSERT_TRUE(std::regex_match(returnValue, returnValueMatchResult, stringifyExpressionRegex));

		const std::string returnValueFractionalDigits{ returnValueMatchResult[stringifyExpressionRegexSubgroups::FractionalDigits].str() };

		std::smatch returnValueFractionalDigitsWithoutTrailingZerosMatchResult;
		ASSERT_TRUE
		(
			std::regex_match
			(
				returnValueFractionalDigits,
				returnValueFractionalDigitsWithoutTrailingZerosMatchResult,
				std::regex{ "^(\\d*?)0*$" }
			)
		);
		const std::string returnValueFractionalDigitsWithoutTrailingZeros{ returnValueFractionalDigitsWithoutTrailingZerosMatchResult[1].str() };

		if (GetParam().evaluationIsInteger)
			EXPECT_EQ(0, returnValueFractionalDigitsWithoutTrailingZeros.size());
		else
			EXPECT_EQ(GetParam().evaluationFractionalPartStr, returnValueFractionalDigitsWithoutTrailingZeros);

	}


	TEST_P(ExpressionEvaluationToStringConverter$stringifyExpression$Tests, calling$stringifyExpression$returns$value$with$correct$precision)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using SourceExpressionType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		const NumberType sourceEvaluation{ GetParam().evaluationStr, GetParam().evaluation };
		const SourceExpressionType source{ sourceEvaluation };
		const CmdCalculator::CalculationConfiguration configuration
		{
			GetParam().precision,
			GetParam().shouldPreferDecimalsOverIntegers,
			GetParam().shouldPreferSignExpressionForPositiveValues,
			GetParam().shouldPreferLeadingZeroOverWholelessNumbers,
			GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace
		};

		const CmdCalculator::ExpressionEvaluationToStringConverter<SourceExpressionType> instance{};

		// Act
		const std::string returnValue{ instance.stringifyExpression(source, configuration) };

		// Assert
		std::smatch returnValueMatchResult;
		ASSERT_TRUE(std::regex_match(returnValue, returnValueMatchResult, stringifyExpressionRegex));

		EXPECT_LE(returnValueMatchResult[stringifyExpressionRegexSubgroups::FractionalDigits].str().size(), GetParam().precision);
	}


	TEST_P(ExpressionEvaluationToStringConverter$stringifyExpression$WithIntsOnlyTests, calling$stringifyExpression$with$integer$returns$value$with$decimal$point$iff$shouldPreferDecimalsOverIntegers$is$true)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using SourceExpressionType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		const NumberType sourceEvaluation{ GetParam().evaluationStr, GetParam().evaluation };
		const SourceExpressionType source{ sourceEvaluation };
		const CmdCalculator::CalculationConfiguration configuration
		{
			GetParam().precision,
			GetParam().shouldPreferDecimalsOverIntegers,
			GetParam().shouldPreferSignExpressionForPositiveValues,
			GetParam().shouldPreferLeadingZeroOverWholelessNumbers,
			GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace
		};

		const CmdCalculator::ExpressionEvaluationToStringConverter<SourceExpressionType> instance{};

		// Act
		const std::string returnValue{ instance.stringifyExpression(source, configuration) };

		// Assert
		std::smatch returnValueMatchResult;
		ASSERT_TRUE(std::regex_match(returnValue, returnValueMatchResult, stringifyExpressionRegex));

		const std::integral auto numFractionalDigits
		{
			returnValueMatchResult[stringifyExpressionRegexSubgroups::FractionalPart].str().size()
		};

		if (GetParam().shouldPreferDecimalsOverIntegers)
			EXPECT_GT(numFractionalDigits, 0);
		else
			EXPECT_EQ(numFractionalDigits, 0);
	}


	TEST_P(ExpressionEvaluationToStringConverter$stringifyExpression$WithZeroWholePartsOnly$Tests, calling$stringifyExpression$with$zero$whole$part$returns$value$with$single$zero$whole$part$iff$shouldPreferLeadingZeroOverWholelessNumbers$is$true$otherwise$no$whole$part)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using SourceExpressionType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		const NumberType sourceEvaluation{ GetParam().evaluationStr, GetParam().evaluation };
		const SourceExpressionType source{ sourceEvaluation };
		const CmdCalculator::CalculationConfiguration configuration
		{
			GetParam().precision,
			GetParam().shouldPreferDecimalsOverIntegers,
			GetParam().shouldPreferSignExpressionForPositiveValues,
			GetParam().shouldPreferLeadingZeroOverWholelessNumbers,
			GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace
		};

		const CmdCalculator::ExpressionEvaluationToStringConverter<SourceExpressionType> instance{};

		// Act
		const std::string returnValue{ instance.stringifyExpression(source, configuration) };

		// Assert
		std::smatch returnValueMatchResult;
		ASSERT_TRUE(std::regex_match(returnValue, returnValueMatchResult, stringifyExpressionRegex));

		const std::string returnValueWholeDigits{ returnValueMatchResult[stringifyExpressionRegexSubgroups::WholeDigits].str() };
		if (GetParam().shouldPreferLeadingZeroOverWholelessNumbers)
			EXPECT_EQ("0", returnValueWholeDigits);
		else
			EXPECT_EQ("", returnValueWholeDigits);
	}


	TEST_P(ExpressionEvaluationToStringConverter$stringifyExpression$WithNonZeroWholePartsOnly$Tests, calling$stringifyExpression$with$non$zero$whole$part$returns$value$with$evaluated$whole$part)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using SourceExpressionType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		const NumberType sourceEvaluation{ GetParam().evaluationStr, GetParam().evaluation };
		const SourceExpressionType source{ sourceEvaluation };
		const CmdCalculator::CalculationConfiguration configuration
		{
			GetParam().precision,
			GetParam().shouldPreferDecimalsOverIntegers,
			GetParam().shouldPreferSignExpressionForPositiveValues,
			GetParam().shouldPreferLeadingZeroOverWholelessNumbers,
			GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace
		};

		const CmdCalculator::ExpressionEvaluationToStringConverter<SourceExpressionType> instance{};

		// Act
		const std::string returnValue{ instance.stringifyExpression(source, configuration) };

		// Assert
		std::smatch returnValueMatchResult;
		ASSERT_TRUE(std::regex_match(returnValue, returnValueMatchResult, stringifyExpressionRegex));

		const std::string returnValueWholeDigits{ returnValueMatchResult[stringifyExpressionRegexSubgroups::WholeDigits].str() };
		
		EXPECT_EQ(GetParam().evaluationWholePartStr, returnValueWholeDigits);
	}


	TEST_P(ExpressionEvaluationToStringConverter$stringifyExpression$WithZeroWholePartsOnly$Tests, calling$stringifyExpression$with$integer$returns$value$with$single$zero$fractional$part$iff$shouldPreferDecimalsOverIntegers$and$shouldPreferTrailingZeroOverEmptyDecimalPlace$are$true$otherwise$no$fractional$part)
	{
		// Arrange
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using SourceExpressionType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		const NumberType sourceEvaluation{ GetParam().evaluationStr, GetParam().evaluation };
		const SourceExpressionType source{ sourceEvaluation };
		const CmdCalculator::CalculationConfiguration configuration
		{
			GetParam().precision,
			GetParam().shouldPreferDecimalsOverIntegers,
			GetParam().shouldPreferSignExpressionForPositiveValues,
			GetParam().shouldPreferLeadingZeroOverWholelessNumbers,
			GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace
		};

		const CmdCalculator::ExpressionEvaluationToStringConverter<SourceExpressionType> instance{};

		// Act
		const std::string returnValue{ instance.stringifyExpression(source, configuration) };

		// Assert
		std::smatch returnValueMatchResult;
		ASSERT_TRUE(std::regex_match(returnValue, returnValueMatchResult, stringifyExpressionRegex));

		const std::string returnValueFractionalDigits{ returnValueMatchResult[stringifyExpressionRegexSubgroups::FractionalDigits].str() };
		if (GetParam().shouldPreferDecimalsOverIntegers && GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace)
			EXPECT_EQ("0", returnValueFractionalDigits);
		else
			EXPECT_EQ("", returnValueFractionalDigits);
	}

#pragma endregion
}