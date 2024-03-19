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


	std::ranges::forward_range auto ExpressionEvaluationToStringConverter_stringifyExpression_TestDataValues
	{
		[]()
		{
			std::vector<ExpressionEvaluationToStringConverter_stringifyExpression_TestData> values;

			// 0.0
			for
			(
				const std::string evaluationStr :
				{
					"0", "-0", "+0",
					"000", "-000", "+000",

					".0", "-.0", "+.0",
					".000", "-.000", "+.000",

					"0.", "-0.", "+0.",
					"0.0", "-0.0", "+0.0",
					"0.000", "-0.000", "+0.000",

					"000.", "-000.", "+000.",
					"000.0", "-000.0", "+000.0",
					"000.000", "-000.000", "+000.000"
				}
			)
			{
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 0.0 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Neutral },
					.evaluationIsInteger{ true },
					.evaluationWholePartIsZero{ true },
					.evaluationStr{ evaluationStr },
					.evaluationWholePartStr{ "0" },
					.evaluationFractionalPartStr{ "0" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ false },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
					}
				);
			}

			// 123.0
			for
			(
				const std::string evaluationStr :
				{
					"123", "0123", "00123",
					"123.", "0123.", "00123.",
					"123.0", "0123.0", "00123.0",
					"123.000", "0123.000", "00123.000"
				}
			)
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
					.evaluationWholePartStr{ "123" },
					.evaluationFractionalPartStr{ "0" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ false },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
					}
				);
			}

			// 0.123
			for
			(
				const std::string evaluationStr :
				{
					".123", "0.123", "000.123",
					".1230", "0.1230", "000.1230",
					".123000", "0.123000", "000.123000"
				}
			)
			{
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 0.123 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
					.evaluationIsInteger{ false },
					.evaluationWholePartIsZero{ true },
					.evaluationStr{ evaluationStr },
					.evaluationWholePartStr{ "0" },
					.evaluationFractionalPartStr{ "123" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ false },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
					}
				);
			}

			// 123.456
			for
			(
				const std::string evaluationStr :
				{
					"123.456", "123.4560", "123.456000",
					"0123.456", "0123.4560", "0123.456000",
					"000123.456", "000123.4560", "000123.456000",
				}
			)
			{
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 123.456 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
					.evaluationIsInteger{ false },
					.evaluationWholePartIsZero{ false },
					.evaluationStr{ evaluationStr },
					.evaluationWholePartStr{ "123" },
					.evaluationFractionalPartStr{ "456" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ false },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
					}
				);
			}

			// 0.0012034
			for
			(
				const std::string evaluationStr :
				{
					".0012034", ".00120340", ".0012034000",
					"0.0012034", "0.00120340", "0.0012034000",
					"000.0012034", "000.00120340", "000.0012034000"
				}
			)
			{
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 0012034 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
					.evaluationIsInteger{ false },
					.evaluationWholePartIsZero{ true },
					.evaluationStr{ evaluationStr },
					.evaluationWholePartStr{ "0" },
					.evaluationFractionalPartStr{ "0012034" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ false },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
					}
				);
			}

			// 1203400.0
			for
			(
				const std::string evaluationStr :
				{
					"1203400", "1203400.", "1203400.0", "1203400.000",
					"01203400", "01203400.", "01203400.0", "01203400.000",
					"0001203400", "0001203400.", "0001203400.0", "0001203400.000"
				}
			)
			{
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 1203400.0 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
					.evaluationIsInteger{ true },
					.evaluationWholePartIsZero{ false },
					.evaluationStr{ evaluationStr },
					.evaluationWholePartStr{ "1203400" },
					.evaluationFractionalPartStr{ "0" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ false },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
					}
				);
			}

			// 1203400.0056078
			for
			(
				const std::string evaluationStr :
				{
					"1203400.0056078", "1203400.00560780", "1203400.0056078000",
					"01203400.0056078", "01203400.00560780", "01203400.0056078000",
					"0001203400.0056078", "0001203400.00560780", "0001203400.0056078000"
				}
			)
			{
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 1203400.0 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
					.evaluationIsInteger{ false },
					.evaluationWholePartIsZero{ false },
					.evaluationStr{ evaluationStr },
					.evaluationWholePartStr{ "1203400" },
					.evaluationFractionalPartStr{ "0056078" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ false },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
					}
				);
			}

			// Varying precision and shouldPreferTrailingZeroOverEmptyDecimalPlace with 123.0
			for
			(
				const std::tuple<int, bool, std::string> data :
				{
					std::make_tuple(0, false, ""),
					std::make_tuple(0, true, "0"),
					std::make_tuple(1, false, ""),
					std::make_tuple(1, true, "0"),
					std::make_tuple(64, false, ""),
					std::make_tuple(64, true, "0")
				}
			)
			{
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 123.0 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
					.evaluationIsInteger{ true },
					.evaluationWholePartIsZero{ false },
					.evaluationStr{ "123.0"},
					.evaluationWholePartStr{ "123" },
					.evaluationFractionalPartStr{ std::get<std::string>(data) },
					.precision{ std::get<int>(data) },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ false },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ std::get<bool>(data) }
					}
				);
			}

			// Varying precision and shouldPreferTrailingZeroOverEmptyDecimalPlace with 123.456789
			for
			(
				//tuple<precision, shouldPreferTrailingZeroOverEmptyDecimalPlace, evaluationFractionalPartStr>
				const std::tuple<int, bool, std::string> data :
				{
					std::make_tuple(0, false, ""),
					std::make_tuple(0, true, "0"),
					std::make_tuple(1, false, "4"),
					std::make_tuple(1, true, "4"),
					std::make_tuple(2, false, "45"),
					std::make_tuple(2, true, "45"),
					std::make_tuple(3, false, "456"),
					std::make_tuple(3, true, "456"),
					std::make_tuple(3, false, "456"),
					std::make_tuple(3, true, "456"),
					std::make_tuple(5, false, "45678"),
					std::make_tuple(5, true, "45678"),
					std::make_tuple(6, false, "456789"),
					std::make_tuple(6, true, "456789"),
					std::make_tuple(7, false, "456789"),
					std::make_tuple(7, true, "456789"),
					std::make_tuple(64, false, "456789"),
					std::make_tuple(64, true, "456789")
				}
			)
			{
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 123.456789 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
					.evaluationIsInteger{ false },
					.evaluationWholePartIsZero{ false },
					.evaluationStr{ "123.456789"},
					.evaluationWholePartStr{ "123" },
					.evaluationFractionalPartStr{ std::get<std::string>(data) },
					.precision{ std::get<int>(data) },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ false },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ std::get<bool>(data) }
					}
				);
			}

			// Varying evaluations and shouldPreferSignExpressionForPositiveValues
			for (const bool shouldPreferSignExpressionForPositiveValues : CmdCalculatorTestUtils::SharedTestData::allBools)
			{

				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 0.0 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Neutral },
					.evaluationIsInteger{ true },
					.evaluationWholePartIsZero{ true },
					.evaluationStr{ "0.0"},
					.evaluationWholePartStr{ "0" },
					.evaluationFractionalPartStr{ "" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ shouldPreferSignExpressionForPositiveValues },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
					}
				);
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 0.0 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Neutral },
					.evaluationIsInteger{ true },
					.evaluationWholePartIsZero{ true },
					.evaluationStr{ "+0.0"},
					.evaluationWholePartStr{ "0" },
					.evaluationFractionalPartStr{ "" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ shouldPreferSignExpressionForPositiveValues },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
					}
				);
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 0.0 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Neutral },
					.evaluationIsInteger{ true },
					.evaluationWholePartIsZero{ true },
					.evaluationStr{ "-0.0"},
					.evaluationWholePartStr{ "0" },
					.evaluationFractionalPartStr{ "" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ shouldPreferSignExpressionForPositiveValues },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
					}
				);
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 123.456 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
					.evaluationIsInteger{ false },
					.evaluationWholePartIsZero{ false },
					.evaluationStr{ "123.456"},
					.evaluationWholePartStr{ "123" },
					.evaluationFractionalPartStr{ "456" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ shouldPreferSignExpressionForPositiveValues },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
					}
				);
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ 123.456 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
					.evaluationIsInteger{ false },
					.evaluationWholePartIsZero{ false },
					.evaluationStr{ "+123.456"},
					.evaluationWholePartStr{ "123" },
					.evaluationFractionalPartStr{ "456" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ shouldPreferSignExpressionForPositiveValues },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
					}
				);
				values.push_back
				(
					ExpressionEvaluationToStringConverter_stringifyExpression_TestData
					{
					.evaluation{ -123.456 },
					.evaluationSign{ CmdCalculator::Arithmetic::ESign::Negative },
					.evaluationIsInteger{ false },
					.evaluationWholePartIsZero{ false },
					.evaluationStr{ "-123.456"},
					.evaluationWholePartStr{ "123" },
					.evaluationFractionalPartStr{ "456" },
					.precision{ 8 },
					.shouldPreferDecimalsOverIntegers{ true },
					.shouldPreferSignExpressionForPositiveValues{ shouldPreferSignExpressionForPositiveValues },
					.shouldPreferLeadingZeroOverWholelessNumbers{ true },
					.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
					}
				);
			}

			// Varying evaluations and shouldPreferLeadingZeroOverWholelessNumbers
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 0.0 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Neutral },
				.evaluationIsInteger{ true },
				.evaluationWholePartIsZero{ true },
				.evaluationStr{ "0.0"},
				.evaluationWholePartStr{ "" },
				.evaluationFractionalPartStr{ "" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ false },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 0.0 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Neutral },
				.evaluationIsInteger{ true },
				.evaluationWholePartIsZero{ true },
				.evaluationStr{ "0.0"},
				.evaluationWholePartStr{ "0" },
				.evaluationFractionalPartStr{ "" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ true },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 123.0 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
				.evaluationIsInteger{ true },
				.evaluationWholePartIsZero{ false },
				.evaluationStr{ "123.0"},
				.evaluationWholePartStr{ "123" },
				.evaluationFractionalPartStr{ "" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ false },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 123.0 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
				.evaluationIsInteger{ true },
				.evaluationWholePartIsZero{ false },
				.evaluationStr{ "123.0"},
				.evaluationWholePartStr{ "123" },
				.evaluationFractionalPartStr{ "" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ true },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 0.123 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
				.evaluationIsInteger{ false },
				.evaluationWholePartIsZero{ true },
				.evaluationStr{ "0.123"},
				.evaluationWholePartStr{ "" },
				.evaluationFractionalPartStr{ "123" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ false },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 0.123 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
				.evaluationIsInteger{ false },
				.evaluationWholePartIsZero{ true },
				.evaluationStr{ "0.123"},
				.evaluationWholePartStr{ "0" },
				.evaluationFractionalPartStr{ "123" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ true },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 123.456 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
				.evaluationIsInteger{ false },
				.evaluationWholePartIsZero{ false },
				.evaluationStr{ "123.456"},
				.evaluationWholePartStr{ "123" },
				.evaluationFractionalPartStr{ "456" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ false },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 123.456 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
				.evaluationIsInteger{ false },
				.evaluationWholePartIsZero{ false },
				.evaluationStr{ "123.456"},
				.evaluationWholePartStr{ "123" },
				.evaluationFractionalPartStr{ "456" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ true },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
				}
			);

			// Varying evaluation and shouldPreferTrailingZeroOverEmptyDecimalPlace
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 0.0 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Neutral },
				.evaluationIsInteger{ true },
				.evaluationWholePartIsZero{ true },
				.evaluationStr{ "0.0"},
				.evaluationWholePartStr{ "" },
				.evaluationFractionalPartStr{ "" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ false },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 0.0 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Neutral },
				.evaluationIsInteger{ true },
				.evaluationWholePartIsZero{ true },
				.evaluationStr{ "0.0"},
				.evaluationWholePartStr{ "" },
				.evaluationFractionalPartStr{ "0" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ false },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 123.0 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
				.evaluationIsInteger{ true },
				.evaluationWholePartIsZero{ false },
				.evaluationStr{ "123.0"},
				.evaluationWholePartStr{ "123" },
				.evaluationFractionalPartStr{ "" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ false },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 123.0 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
				.evaluationIsInteger{ true },
				.evaluationWholePartIsZero{ false },
				.evaluationStr{ "123.0"},
				.evaluationWholePartStr{ "123" },
				.evaluationFractionalPartStr{ "0" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ false },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 0.123 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
				.evaluationIsInteger{ false },
				.evaluationWholePartIsZero{ true },
				.evaluationStr{ "0.123"},
				.evaluationWholePartStr{ "" },
				.evaluationFractionalPartStr{ "123" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ false },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 0.123 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
				.evaluationIsInteger{ false },
				.evaluationWholePartIsZero{ true },
				.evaluationStr{ "0.123"},
				.evaluationWholePartStr{ "" },
				.evaluationFractionalPartStr{ "123" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ false },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 123.456 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
				.evaluationIsInteger{ false },
				.evaluationWholePartIsZero{ false },
				.evaluationStr{ "123.456"},
				.evaluationWholePartStr{ "123" },
				.evaluationFractionalPartStr{ "456" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ false },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
				}
			);
			values.push_back
			(
				ExpressionEvaluationToStringConverter_stringifyExpression_TestData
				{
				.evaluation{ 123.456 },
				.evaluationSign{ CmdCalculator::Arithmetic::ESign::Positive },
				.evaluationIsInteger{ false },
				.evaluationWholePartIsZero{ false },
				.evaluationStr{ "123.456"},
				.evaluationWholePartStr{ "123" },
				.evaluationFractionalPartStr{ "456" },
				.precision{ 8 },
				.shouldPreferDecimalsOverIntegers{ true },
				.shouldPreferSignExpressionForPositiveValues{ false },
				.shouldPreferLeadingZeroOverWholelessNumbers{ false },
				.shouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
				}
			);

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