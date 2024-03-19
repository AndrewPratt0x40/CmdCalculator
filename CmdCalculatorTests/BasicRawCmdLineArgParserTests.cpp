#include "pch.h"

#include <ranges>
#include <string>
#include <optional>
#include <vector>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/BasicRawCmdLineArgParser.h"
#include "../CmdCalculator/RawCmdLineArgParser.h"
#include "../CmdCalculator/MissingCmdLineArgValueException.h"
#include "../CmdCalculator/DuplicateCmdLineArgException.h"
#include "../CmdCalculator/ContradictingCmdLineArgException.h"
#include "../CmdCalculator/UnknownCmdLineArgException.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(BasicRawCmdLineArgParserTests, BasicRawCmdLineArgParser$satisfies$RawCmdLineArgParser$concept)
	{
		static_assert
		(
			CmdCalculator::RawCmdLineArgParser
			<
				CmdCalculator::BasicRawCmdLineArgParser<std::string>,
				std::ranges::empty_view<std::string>
			>
		);
	}

#pragma endregion


#pragma region parseRawCmdLineArgs

	struct BasicRawCmdLineArgParser_parseRawCmdLineArgs_TestData
	{
		std::vector<std::string> argsToPass;
		std::optional<std::string> defaultGivenExpression;
		int defaultPrecision;
		bool defaultShouldPreferDecimalsOverIntegers;
		bool defaultShouldPreferSignExpressionForPositiveValues;
		bool defaultShouldPreferLeadingZeroOverWholelessNumbers;
		bool defaultShouldPreferTrailingZeroOverEmptyDecimalPlace;


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const BasicRawCmdLineArgParser_parseRawCmdLineArgs_TestData& testData
		)
		{
			ostream
				<< "BasicRawCmdLineArgParser.parseRawCmdLineArgs(rawCmdLineArgs={"
				<< CmdCalculatorTestUtils::joinStrings(testData.argsToPass)
				<< "}, defaultConfiguration={.givenExpression="
			;

			if (testData.defaultGivenExpression.has_value())
			{
				ostream
					<< '\"'
					<< testData.defaultGivenExpression.value()
					<< '\"'
					;
			}
			else
				ostream << "{}";

			ostream
				<< ", .calculationConfiguration={.precision="
				<< testData.defaultPrecision
				<< ", .shouldPreferDecimalsOverIntegers="
				<< testData.defaultShouldPreferDecimalsOverIntegers
				<< ", .shouldPreferSignExpressionForPositiveValues="
				<< testData.defaultShouldPreferSignExpressionForPositiveValues
				<< ", .shouldPreferLeadingZeroOverWholelessNumbers="
				<< testData.defaultShouldPreferLeadingZeroOverWholelessNumbers
				<< ", .shouldPreferTrailingZeroOverEmptyDecimalPlace="
				<< testData.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace
				<< "}})"
			;

			return ostream;
		}
	};


#pragma region parseRawCmdLineArgs with valid args

	struct BasicRawCmdLineArgParser_parseRawCmdLineArgs_WithValidArgsTestData
	{
		BasicRawCmdLineArgParser_parseRawCmdLineArgs_TestData callData;

		std::optional<std::string> expectedGivenExpression;
		int expectedPrecision;
		bool expectedShouldPreferDecimalsOverIntegers;
		bool expectedShouldPreferSignExpressionForPositiveValues;
		bool expectedShouldPreferLeadingZeroOverWholelessNumbers;
		bool expectedShouldPreferTrailingZeroOverEmptyDecimalPlace;


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const BasicRawCmdLineArgParser_parseRawCmdLineArgs_WithValidArgsTestData& testData
		)
		{
			ostream
				<< testData.callData
				<< " = {.givenExpression="
			;

			if (testData.expectedGivenExpression.has_value())
			{
				ostream
					<< '\"'
					<< testData.expectedGivenExpression.value()
					<< '\"'
					;
			}
			else
				ostream << "{}";

			ostream
				<< ", .calculationConfiguration={.precision="
				<< testData.expectedPrecision
				<< ", .shouldPreferDecimalsOverIntegers="
				<< testData.expectedShouldPreferDecimalsOverIntegers
				<< ", .shouldPreferSignExpressionForPositiveValues="
				<< testData.expectedShouldPreferSignExpressionForPositiveValues
				<< ", .shouldPreferLeadingZeroOverWholelessNumbers="
				<< testData.expectedShouldPreferLeadingZeroOverWholelessNumbers
				<< ", .shouldPreferTrailingZeroOverEmptyDecimalPlace="
				<< testData.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace
				<< "}}"
			;

			return ostream;
		}
	};

	class BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithValidArgsTests :
		public testing::TestWithParam<BasicRawCmdLineArgParser_parseRawCmdLineArgs_WithValidArgsTestData>
	{};


	const BasicRawCmdLineArgParser_parseRawCmdLineArgs_WithValidArgsTestData BasicRawCmdLineArgParser_parseRawCmdLineArgs_WithValidArgsTestDataValues[]
	{
		// No args
		{
			.callData
			{
				.argsToPass{},
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{},
				.defaultGivenExpression{ std::make_optional<std::string>("Default expression")},
				.defaultPrecision{ 123 },
				.defaultShouldPreferDecimalsOverIntegers{ true },
				.defaultShouldPreferSignExpressionForPositiveValues{ true },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ true },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
			},
			.expectedGivenExpression{ std::make_optional<std::string>("Default expression")},
			.expectedPrecision{ 123 },
			.expectedShouldPreferDecimalsOverIntegers{ true },
			.expectedShouldPreferSignExpressionForPositiveValues{ true },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ true },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
		},
		// Given expression (-e)
		{
			.callData
			{
				.argsToPass{ "-e", "Given expression" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{ std::make_optional<std::string>("Given expression") },
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{ "-e", "Given expression" },
				.defaultGivenExpression{ std::make_optional<std::string>("Default expression") },
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{ std::make_optional<std::string>("Given expression") },
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		// Given precision (-p)
		{
			.callData
			{
				.argsToPass{ "-p", "456" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 456 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		// Given defaultShouldPreferDecimalsOverIntegers (-d/-D)
		{
			.callData
			{
				.argsToPass{ "-d" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ true },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{ "-d" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ true },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ true },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{ "-D" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{ "-D" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ true },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		// Given defaultShouldPreferSignExpressionForPositiveValues (-s/-S)
		{
			.callData
			{
				.argsToPass{ "-s" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ true },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{ "-s" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ true },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ true },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{ "-S" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{ "-S" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ true },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		// Given expectedShouldPreferLeadingZeroOverWholelessNumbers (-l/-L)
		{
			.callData
			{
				.argsToPass{ "-l" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ true },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{ "-l" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ true },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ true },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{ "-L" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{ "-L" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ true },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		// Given expectedShouldPreferTrailingZeroOverEmptyDecimalPlace (-t/-T)
		{
			.callData
			{
				.argsToPass{ "-t" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
		},
		{
			.callData
			{
				.argsToPass{ "-t" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
		},
		{
			.callData
			{
				.argsToPass{ "-T" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{ "-T" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
			},
			.expectedGivenExpression{},
			.expectedPrecision{ 0 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		// Given several arguments
		{
			.callData
			{
				.argsToPass{ "-e", "Given expression", "-p", "456", "-d", "-s", "-l", "-t" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{ std::make_optional<std::string>("Given expression") },
			.expectedPrecision{ 456 },
			.expectedShouldPreferDecimalsOverIntegers{ true },
			.expectedShouldPreferSignExpressionForPositiveValues{ true },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ true },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
		},
		{
			.callData
			{
				.argsToPass{ "-e", "Given expression", "-p", "456", "-d", "-s", "-l", "-t" },
				.defaultGivenExpression{ std::make_optional<std::string>("Default expression") },
				.defaultPrecision{ 123 },
				.defaultShouldPreferDecimalsOverIntegers{ true },
				.defaultShouldPreferSignExpressionForPositiveValues{ true },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ true },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
			},
			.expectedGivenExpression{ std::make_optional<std::string>("Given expression") },
			.expectedPrecision{ 456 },
			.expectedShouldPreferDecimalsOverIntegers{ true },
			.expectedShouldPreferSignExpressionForPositiveValues{ true },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ true },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
		},
		{
			.callData
			{
				.argsToPass{ "-t", "-l", "-s", "-d", "-p", "456", "-e", "Given expression" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{ std::make_optional<std::string>("Given expression") },
			.expectedPrecision{ 456 },
			.expectedShouldPreferDecimalsOverIntegers{ true },
			.expectedShouldPreferSignExpressionForPositiveValues{ true },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ true },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
		},
		{
			.callData
			{
				.argsToPass{ "-e", "Given expression", "-p", "456", "-D", "-S", "-L", "-T" },
				.defaultGivenExpression{},
				.defaultPrecision{ 0 },
				.defaultShouldPreferDecimalsOverIntegers{ false },
				.defaultShouldPreferSignExpressionForPositiveValues{ false },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ false },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
			},
			.expectedGivenExpression{ std::make_optional<std::string>("Given expression") },
			.expectedPrecision{ 456 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		},
		{
			.callData
			{
				.argsToPass{ "-e", "Given expression", "-p", "456", "-D", "-S", "-L", "-T" },
				.defaultGivenExpression{ std::make_optional<std::string>("Default expression") },
				.defaultPrecision{ 123 },
				.defaultShouldPreferDecimalsOverIntegers{ true },
				.defaultShouldPreferSignExpressionForPositiveValues{ true },
				.defaultShouldPreferLeadingZeroOverWholelessNumbers{ true },
				.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace{ true }
			},
			.expectedGivenExpression{ std::make_optional<std::string>("Given expression") },
			.expectedPrecision{ 456 },
			.expectedShouldPreferDecimalsOverIntegers{ false },
			.expectedShouldPreferSignExpressionForPositiveValues{ false },
			.expectedShouldPreferLeadingZeroOverWholelessNumbers{ false },
			.expectedShouldPreferTrailingZeroOverEmptyDecimalPlace{ false }
		}
	};


	INSTANTIATE_TEST_CASE_P
	(
		BasicRawCmdLineArgParserTests,
		BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithValidArgsTests,
		testing::ValuesIn(BasicRawCmdLineArgParser_parseRawCmdLineArgs_WithValidArgsTestDataValues)
	);

	TEST_P(BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithValidArgsTests, calling$parseRawCmdLineArgs$with$valid$args$returns$expected$value)
	{
		// Arrange
		CmdCalculatorTestUtils::ForwardRangeOf<std::string> auto rawCmdLineArgs{ GetParam().callData.argsToPass };

		const CmdCalculator::ProcessConfiguration<std::string> defaultConfiguration
		{
			.givenExpression{ GetParam().callData.defaultGivenExpression },
			.calculationConfiguration
			{
				GetParam().callData.defaultPrecision,
				GetParam().callData.defaultShouldPreferDecimalsOverIntegers,
				GetParam().callData.defaultShouldPreferSignExpressionForPositiveValues,
				GetParam().callData.defaultShouldPreferLeadingZeroOverWholelessNumbers,
				GetParam().callData.defaultShouldPreferTrailingZeroOverEmptyDecimalPlace
			}
		};

		const CmdCalculator::BasicRawCmdLineArgParser<std::string> instance{};

		// Act
		const CmdCalculator::ProcessConfiguration<std::string> returnValue
		{
			instance.parseRawCmdLineArgs(rawCmdLineArgs, defaultConfiguration)
		};

		// Assert
		EXPECT_EQ(GetParam().expectedGivenExpression.has_value(), returnValue.givenExpression.has_value());
		if (GetParam().expectedGivenExpression.has_value() && returnValue.givenExpression.has_value())
			EXPECT_EQ(GetParam().expectedGivenExpression.value(), returnValue.givenExpression.value());

		EXPECT_EQ(GetParam().expectedPrecision, returnValue.calculationConfiguration.getPrecision());
		EXPECT_EQ(GetParam().expectedShouldPreferDecimalsOverIntegers, returnValue.calculationConfiguration.shouldPreferDecimalsOverIntegers());
		EXPECT_EQ(GetParam().expectedShouldPreferSignExpressionForPositiveValues, returnValue.calculationConfiguration.shouldPreferSignExpressionForPositiveValues());
		EXPECT_EQ(GetParam().expectedShouldPreferLeadingZeroOverWholelessNumbers, returnValue.calculationConfiguration.shouldPreferLeadingZeroOverWholelessNumbers());
		EXPECT_EQ(GetParam().expectedShouldPreferTrailingZeroOverEmptyDecimalPlace, returnValue.calculationConfiguration.shouldPreferTrailingZeroOverEmptyDecimalPlace());
	}

#pragma endregion


#pragma region parseRawCmdLineArgs with unknown args

	class BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithUnknownArgsTests :
		public testing::TestWithParam<std::vector<std::string>>
	{};

	const std::vector<std::string> BasicRawCmdLineArgParser_parseRawCmdLineArgs_WithUnknownArgsTestDataValues[]
	{
		// Wrong capitalization
		{ "-E", "2 + 2" },
		{ "-P", "123" },

		// Missing/wrong dash
		{ "e" }, { "p" }, { "d" }, { "s" }, { "l" }, { "t" },
		{ "D" }, { "S" }, { "L" }, { "T" },
		
		{ "- e" }, { "- p" }, { "- d" }, { "- s" }, { "- l" }, { "- t" },
		{ "- D" }, { "- S" }, { "- L" }, { "- T" },
		
		{ "e-" }, { "p-" }, { "d-" }, { "s-" }, { "l-" }, { "t-" },
		{ "D-" }, { "S-" }, { "L-" }, { "T-" },

		// Unknown single arg
		{ "x" }, {"-x"}, { "0" }, { "-0" }, { "-" },
		{ "Hello, world!" }, { "-Hello, world!" },

		// Several unknown args
		{ "-x", "-y", "-z" },
		{ "-e", "2 + 3", "-z", "-D" }
	};

	INSTANTIATE_TEST_CASE_P
	(
		BasicRawCmdLineArgParserTests,
		BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithUnknownArgsTests,
		testing::ValuesIn(BasicRawCmdLineArgParser_parseRawCmdLineArgs_WithUnknownArgsTestDataValues)
	);

	TEST_P(BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithUnknownArgsTests, calling$parseRawCmdLineArgs$with$one$or$more$unknown$args$throws$UnknownCmdLineArgException)
	{
		// Arrange
		CmdCalculatorTestUtils::ForwardRangeOf<std::string> auto rawCmdLineArgs{ GetParam() };

		const CmdCalculator::ProcessConfiguration<std::string> defaultConfiguration
		{
			.givenExpression{},
			.calculationConfiguration{ 0, false, false, false, false }
		};

		const CmdCalculator::BasicRawCmdLineArgParser<std::string> instance{};

		const auto action
		{
			[&]()
			{
				instance.parseRawCmdLineArgs(rawCmdLineArgs, defaultConfiguration);
			}
		};


		// Act/Assert
		EXPECT_THROW(action(), CmdCalculator::UnknownCmdLineArgException<std::string>);
	}

#pragma endregion


#pragma region parseRawCmdLineArgs with missing arg values

	class BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithMissingArgValuesTests :
		public testing::TestWithParam<std::vector<std::string>>
	{};

	const std::vector<std::string> BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithMissingArgValues_TestDataValues[]
	{
		{ "-e" },
		{ "-p" }
	};

	INSTANTIATE_TEST_CASE_P
	(
		BasicRawCmdLineArgParserTests,
		BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithMissingArgValuesTests,
		testing::ValuesIn(BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithMissingArgValues_TestDataValues)
	);

	TEST_P(BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithMissingArgValuesTests, calling$parseRawCmdLineArgs$with$one$or$more$missing$arg$values$throws$MissingCmdLineArgValueException)
	{
		// Arrange
		CmdCalculatorTestUtils::ForwardRangeOf<std::string> auto rawCmdLineArgs{ GetParam() };

		const CmdCalculator::ProcessConfiguration<std::string> defaultConfiguration
		{
			.givenExpression{},
			.calculationConfiguration{ 0, false, false, false, false }
		};

		const CmdCalculator::BasicRawCmdLineArgParser<std::string> instance{};

		const auto action
		{
			[&]()
			{
				instance.parseRawCmdLineArgs(rawCmdLineArgs, defaultConfiguration);
			}
		};


		// Act/Assert
		EXPECT_THROW(action(), CmdCalculator::MissingCmdLineArgValueException<std::string>);
	}

#pragma endregion


#pragma region parseRawCmdLineArgs with duplicate args

	class BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithDuplicateArgsTests :
		public testing::TestWithParam<std::vector<std::string>>
	{};

	const std::vector<std::string> BasicRawCmdLineArgParser$parseRawCmdLineArgs_WithDuplicateArgs_TestDataValues[]
	{
		{ "-d", "-d", "-d" },
		{ "-d", "-d" }, { "-D", "-D" },
		{ "-s", "-s" }, { "-S", "-S" },
		{ "-l", "-l" }, { "-L", "-L" },
		{ "-t", "-t" }, { "-T", "-T" },
		{ "-e", "123", "-e", "123" },
		{ "-e", "123", "-e", "456" },
		{ "-p", "123", "-p", "123" },
		{ "-p", "123", "-p", "456" },
		{ "-e", "123", "-p", "0", "-d", "-d", "-S", "-t" },
		{ "-e", "123", "-p", "0", "-d", "-S", "-d", "-t" }
	};

	INSTANTIATE_TEST_CASE_P
	(
		BasicRawCmdLineArgParserTests,
		BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithDuplicateArgsTests,
		testing::ValuesIn(BasicRawCmdLineArgParser$parseRawCmdLineArgs_WithDuplicateArgs_TestDataValues)
	);

	TEST_P(BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithDuplicateArgsTests, calling$parseRawCmdLineArgs$with$one$or$more$duplicate$args$throws$DuplicateCmdLineArgException)
	{
		// Arrange
		CmdCalculatorTestUtils::ForwardRangeOf<std::string> auto rawCmdLineArgs{ GetParam() };

		const CmdCalculator::ProcessConfiguration<std::string> defaultConfiguration
		{
			.givenExpression{},
			.calculationConfiguration{ 0, false, false, false, false }
		};

		const CmdCalculator::BasicRawCmdLineArgParser<std::string> instance{};

		const auto action
		{
			[&]()
			{
				instance.parseRawCmdLineArgs(rawCmdLineArgs, defaultConfiguration);
			}
		};


		// Act/Assert
		EXPECT_THROW(action(), CmdCalculator::DuplicateCmdLineArgException<std::string>);
	}

#pragma endregion


#pragma region parseRawCmdLineArgs with contradicting args

	class BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithContradictingArgsTests :
		public testing::TestWithParam<std::vector<std::string>>
	{};

	const std::vector<std::string> BasicRawCmdLineArgParser$parseRawCmdLineArgs_WithContradictingArgs_TestDataValues[]
	{
		{ "-d", "-D" }, { "-D", "-d" },
		{ "-s", "-S" }, { "-S", "-s" },
		{ "-l", "-L" }, { "-L", "-l" },
		{ "-t", "-T" }, { "-T", "-t" },
		{ "-e", "123", "-p", "456", "-d", "-D", "-S", "t" },
		{ "-e", "123", "-p", "456", "-d", "-S", "-t", "-D" }
	};

	INSTANTIATE_TEST_CASE_P
	(
		BasicRawCmdLineArgParserTests,
		BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithContradictingArgsTests,
		testing::ValuesIn(BasicRawCmdLineArgParser$parseRawCmdLineArgs_WithContradictingArgs_TestDataValues)
	);

	TEST_P(BasicRawCmdLineArgParser$parseRawCmdLineArgs$WithContradictingArgsTests, calling$parseRawCmdLineArgs$with$one$or$more$contradicting$args$throws$ContradictingCmdLineArgException)
	{
		// Arrange
		CmdCalculatorTestUtils::ForwardRangeOf<std::string> auto rawCmdLineArgs{ GetParam() };

		const CmdCalculator::ProcessConfiguration<std::string> defaultConfiguration
		{
			.givenExpression{},
			.calculationConfiguration{ 0, false, false, false, false }
		};

		const CmdCalculator::BasicRawCmdLineArgParser<std::string> instance{};

		const auto action
		{
			[&]()
			{
				instance.parseRawCmdLineArgs(rawCmdLineArgs, defaultConfiguration);
			}
		};


		// Act/Assert
		EXPECT_THROW(action(), CmdCalculator::ContradictingCmdLineArgException<std::string>);
	}

#pragma endregion

#pragma endregion
}