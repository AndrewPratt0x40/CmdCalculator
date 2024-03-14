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


using namespace std::string_literals;


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
				<< "}, CalculationConfiguration{precision="
				<< testData.precision
				<< ", shouldPreferDecimalsOverIntegers="
				<< testData.shouldPreferDecimalsOverIntegers
				<< ", shouldPreferSignExpressionForPositiveValues="
				<< testData.shouldPreferSignExpressionForPositiveValues
				<< ", shouldPreferLeadingZeroOverWholelessNumbers="
				<< testData.shouldPreferLeadingZeroOverWholelessNumbers
				<< ", shouldPreferTrailingZeroOverEmptyDecimalPlace="
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
		0, 1, 3, 64
	};


	std::string getExpectedPartStr(std::string fullPartStr, bool zeroCharIfEmpty, std::string regexProj)
	{
		const bool foo{ fullPartStr == "123" && zeroCharIfEmpty && regexProj == "^0*([1-9]\\d*)?$" };

		std::smatch matchResults;
		const bool couldMatch{ std::regex_match(fullPartStr, matchResults, std::regex{ regexProj }) };
		if (!couldMatch && !matchResults.ready())
			throw std::exception{ "Failed to match regex while setting up test data." };
		
		const std::string projFullPartStr{ matchResults[1].str() };

		return (projFullPartStr.empty() && zeroCharIfEmpty) ? "0" : projFullPartStr;
	}

	std::string getExpectedPartStr(std::string fullPartStr, bool zeroCharIfEmpty, std::string regexProj, int precision)
	{
		return getExpectedPartStr(fullPartStr.substr(0, precision), zeroCharIfEmpty, regexProj);
	}

	const std::string expectedWholePartRegexProj{ "^0*([1-9]\\d*)?$" };
	const std::string expectedFractionalPartRegexProj{ "^(\\d*[1-9])?0*$" };


	// TODO: This test data collection uses logic that is complex enough that the data itself may need to be unit-tested for validity.
	const std::ranges::forward_range auto ExpressionEvaluationToStringConverter_stringifyExpression_TestDataValues
	{
		[]()
		{
			std::vector<ExpressionEvaluationToStringConverter_stringifyExpression_TestData> values{};

			for(const int precision : valid_stringifyExpressionPrecisionValues){
			for(const bool shouldPreferDecimalsOverIntegers : CmdCalculatorTestUtils::SharedTestData::allBools){
			for(const bool shouldPreferSignExpressionForPositiveValues : CmdCalculatorTestUtils::SharedTestData::allBools){
			for(const bool shouldPreferLeadingZeroOverWholelessNumbers : CmdCalculatorTestUtils::SharedTestData::allBools){
			for(const bool shouldPreferTrailingZeroOverEmptyDecimalPlace : CmdCalculatorTestUtils::SharedTestData::allBools)
			{
				const bool zeroCharIfWholePartEmpty{ shouldPreferLeadingZeroOverWholelessNumbers };
				const bool zeroCharIfFractionalPartEmpty{ shouldPreferDecimalsOverIntegers && shouldPreferTrailingZeroOverEmptyDecimalPlace };

				for (const std::string evaluationStr : {"-0", "0", "+0"})
				{
					values.push_back
					(
						ExpressionEvaluationToStringConverter_stringifyExpression_TestData
						{
							.evaluation{ 0 },
							.evaluationSign{ CmdCalculator::Arithmetic::ESign::Neutral },
							.evaluationIsInteger{ true },
							.evaluationWholePartIsZero{ true },
							.evaluationStr{ evaluationStr },
							.evaluationWholePartStr{ getExpectedPartStr("0", zeroCharIfWholePartEmpty, expectedWholePartRegexProj) },
							.evaluationFractionalPartStr{ getExpectedPartStr("0", zeroCharIfFractionalPartEmpty, expectedFractionalPartRegexProj, precision) },
							.precision{ precision },
							.shouldPreferDecimalsOverIntegers{ shouldPreferDecimalsOverIntegers },
							.shouldPreferSignExpressionForPositiveValues{ shouldPreferSignExpressionForPositiveValues },
							.shouldPreferLeadingZeroOverWholelessNumbers{ shouldPreferLeadingZeroOverWholelessNumbers },
							.shouldPreferTrailingZeroOverEmptyDecimalPlace{ shouldPreferTrailingZeroOverEmptyDecimalPlace }
						}
					);
				}

				for (const std::string evaluationStr : {"123", "123."})
				{
					values.push_back
					(
						ExpressionEvaluationToStringConverter_stringifyExpression_TestData
						{
							.evaluation{ 123.0 },
							.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
							.evaluationIsInteger{ true },
							.evaluationWholePartIsZero{ false },
							.evaluationStr{ evaluationStr },
							.evaluationWholePartStr{ getExpectedPartStr("123", zeroCharIfWholePartEmpty, expectedWholePartRegexProj) },
							.evaluationFractionalPartStr{ getExpectedPartStr("0", zeroCharIfFractionalPartEmpty, expectedFractionalPartRegexProj, precision) },
							.precision{ precision },
							.shouldPreferDecimalsOverIntegers{ shouldPreferDecimalsOverIntegers },
							.shouldPreferSignExpressionForPositiveValues{ shouldPreferSignExpressionForPositiveValues },
							.shouldPreferLeadingZeroOverWholelessNumbers{ shouldPreferLeadingZeroOverWholelessNumbers },
							.shouldPreferTrailingZeroOverEmptyDecimalPlace{ shouldPreferTrailingZeroOverEmptyDecimalPlace }
						}
					);
				}

				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
						.evaluation{ 0.123 },
						.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
						.evaluationIsInteger{ false },
						.evaluationWholePartIsZero{ true },
						.evaluationStr{ ".123" },
						.evaluationWholePartStr{ getExpectedPartStr("0", zeroCharIfWholePartEmpty, expectedWholePartRegexProj) },
						.evaluationFractionalPartStr{ getExpectedPartStr("123", zeroCharIfFractionalPartEmpty, expectedFractionalPartRegexProj, precision) },
						.precision{ precision },
						.shouldPreferDecimalsOverIntegers{ shouldPreferDecimalsOverIntegers },
						.shouldPreferSignExpressionForPositiveValues{ shouldPreferSignExpressionForPositiveValues },
						.shouldPreferLeadingZeroOverWholelessNumbers{ shouldPreferLeadingZeroOverWholelessNumbers },
						.shouldPreferTrailingZeroOverEmptyDecimalPlace{ shouldPreferTrailingZeroOverEmptyDecimalPlace }
					}
				);

				for(const CmdCalculatorTestUtils::SharedTestData::CompositeOperandData<double>& compositeValue : operandDataValuesFor_stringifyExpressionTests())
				{
					values.push_back
					(
						ExpressionEvaluationToStringConverter_stringifyExpression_TestData
						{
							.evaluation{ compositeValue.value },
							.evaluationSign{ compositeValue.sign },
							.evaluationIsInteger{ compositeValue.isInteger.value() },
							.evaluationWholePartIsZero{ !compositeValue.isAbsoluteValueAtLeastOne.value() },
							.evaluationStr
							{
								std::format
								(
									"{}{}.{}",
									compositeValue.sign == CmdCalculator::Arithmetic::ESign::Negative
										? "-"
										: ""
									,
									compositeValue.wholePartStr.value(),
									compositeValue.fractionalPartStr.value()
								)
							},
							.evaluationWholePartStr
							{
								getExpectedPartStr
								(
									static_cast<std::string>(compositeValue.wholePartStr.value()),
									zeroCharIfWholePartEmpty,
									expectedWholePartRegexProj
								)
							},
							.evaluationFractionalPartStr
							{
								getExpectedPartStr
								(
									static_cast<std::string>(compositeValue.fractionalPartStr.value()),
									zeroCharIfFractionalPartEmpty,
									expectedFractionalPartRegexProj,
									precision
								)
							},
							.precision{ precision },
							.shouldPreferDecimalsOverIntegers{ shouldPreferDecimalsOverIntegers },
							.shouldPreferSignExpressionForPositiveValues{ shouldPreferSignExpressionForPositiveValues },
							.shouldPreferLeadingZeroOverWholelessNumbers{ shouldPreferLeadingZeroOverWholelessNumbers },
							.shouldPreferTrailingZeroOverEmptyDecimalPlace{ shouldPreferTrailingZeroOverEmptyDecimalPlace }
						}
					);
				}
			}}}}}

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

		EXPECT_EQ(GetParam().evaluationWholePartStr, returnValueWholeDigits);
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

		EXPECT_EQ(GetParam().evaluationFractionalPartStr, returnValueFractionalDigits);
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

		const size_t maxExpectedFractionalDigits
		{
			GetParam().precision == 0
				? GetParam().evaluationFractionalPartStr.size()
				: GetParam().precision
		};

		const CmdCalculator::ExpressionEvaluationToStringConverter<SourceExpressionType> instance{};

		// Act
		const std::string returnValue{ instance.stringifyExpression(source, configuration) };

		// Assert
		std::smatch returnValueMatchResult;
		ASSERT_TRUE(std::regex_match(returnValue, returnValueMatchResult, stringifyExpressionRegex));

		const std::string returnValueFractionalDigits{ returnValueMatchResult[stringifyExpressionRegexSubgroups::FractionalDigits].str() };

		EXPECT_LE(returnValueFractionalDigits.size(), maxExpectedFractionalDigits);
	}


	TEST_P(ExpressionEvaluationToStringConverter$stringifyExpression$WithIntsOnlyTests, calling$stringifyExpression$with$integer$returns$value$with$decimal$point$iff$shouldPreferDecimalsOverIntegers$is$true)
	{
		const bool foo{ GetParam().evaluationStr == "-0" && GetParam().precision == 0 && !GetParam().shouldPreferDecimalsOverIntegers && GetParam().shouldPreferTrailingZeroOverEmptyDecimalPlace };
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

		const bool decimalPointExists
		{
			!returnValueMatchResult[stringifyExpressionRegexSubgroups::FractionalPart].str().empty()
		};

		EXPECT_EQ(GetParam().shouldPreferDecimalsOverIntegers, decimalPointExists);
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
		
		EXPECT_TRUE(std::regex_match(returnValueWholeDigits, std::regex{ "^[1-9]\\d*$" }));
	}


	TEST_P(ExpressionEvaluationToStringConverter$stringifyExpression$WithIntsOnlyTests, calling$stringifyExpression$with$integer$returns$value$with$single$zero$fractional$part$iff$shouldPreferDecimalsOverIntegers$and$shouldPreferTrailingZeroOverEmptyDecimalPlace$are$true$otherwise$no$fractional$part)
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