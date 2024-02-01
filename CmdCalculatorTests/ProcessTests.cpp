#include "pch.h"

#include <string>
#include <string_view>
#include <vector>
#include <ranges>

#include "..\CmdCalculator\Process.h"
#include "..\CmdCalculatorTestDoubles/FakeConsole.h"
#include "..\CmdCalculatorTestDoubles/StubCalculation.h"
#include "..\CmdCalculatorTestDoubles/StubThrowingCalculation.h"
#include "..\CmdCalculatorTestDoubles/StubRawCmdLineArgParser.h"
#include "..\CmdCalculatorTestDoubles/StubThrowingRawCmdLineArgParser.h"
#include "..\CmdCalculatorTestDoubles/StubMathAstNode.h"
#include "..\CmdCalculatorTestDoubles/FakeRealNumber.h"
#include "..\CmdCalculatorTestDoubles/StubExpression.h"
#include "..\CmdCalculatorTestDoubles/StubStringToMathAstConverter.h"
#include "..\CmdCalculatorTestDoubles/StubValidatingStringToMathAstConverter.h"
#include "..\CmdCalculatorTestDoubles/StubMathAstToExpressionConverter.h"
#include "..\CmdCalculatorTestDoubles/StubExpressionToStringConverter.h"
#include "..\CmdCalculatorTestDoubles/DummyInvalidInputExpressionException.h"
#include "..\CmdCalculatorTestDoubles\FakeCalculation.h"

using namespace std::string_literals;
using namespace std::string_view_literals;

namespace CmdCalculatorTests
{
#pragma region Shared data

	namespace OutputExpressionProvidersForProcess
	{
		struct OutputExpressionProvider
		{
			using OutputExpressionType = std::string;

			static std::string getOutputExpression()
			{
				return "12345";
			}
		};

		struct OtherOutputExpressionProvider
		{
			using OutputExpressionType = std::string;

			static std::string getOutputExpression()
			{
				return "- 678.321";
			}
		};
	}


	namespace NonThrowingProcessTParams
	{
		using StringToMathAstConverterType = CmdCalculatorTestDoubles::StubStringToMathAstConverter
		<
			std::string_view,
			CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>
		>;

		using MathAstToExpressionConverterType = CmdCalculatorTestDoubles::StubMathAstToExpressionConverter
		<
			CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>,
			CmdCalculatorTestDoubles::Expressions::StubExpression<CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber>
		>;

		using ExpressionToStringConverterType = CmdCalculatorTestDoubles::StubExpressionToStringConverter
		<
			CmdCalculatorTestDoubles::Expressions::StubExpression<CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber>,
			std::string
		>;


		using CalculationType = CmdCalculatorTestDoubles::StubCalculation
		<
			CmdCalculatorTestDoubles::StubCalculation_TParams
			<
				std::string,
				std::string,
				StringToMathAstConverterType,
				MathAstToExpressionConverterType,
				ExpressionToStringConverterType
			>,
			OutputExpressionProvidersForProcess::OutputExpressionProvider
		>;


		using RawCmdLineArgParserType = CmdCalculatorTestDoubles::StubRawCmdLineArgParser<std::string>;
		using RawCmdLineArgsType = std::ranges::ref_view<std::vector<std::string>>;


		using ProcessType = CmdCalculator::Process
		<
			CalculationType,
			RawCmdLineArgParserType,
			RawCmdLineArgsType,
			StringToMathAstConverterType,
			MathAstToExpressionConverterType,
			ExpressionToStringConverterType
		>;


		CmdCalculator::ProcessConfiguration<std::string> makeProcessConfigurationInstance()
		{
			return CmdCalculator::ProcessConfiguration<std::string>
			{
				.givenExpression{ std::make_optional<std::string>("0"s) },
				.calculationConfiguration{4, false, false, false, false}
			};
		}
	}

#pragma endregion


#pragma region Calling run with valid args

	template<CmdCalculatorTestDoubles::StubCalculationOutputExpressionProvider OutputExpressionProviderT>
		requires std::same_as<std::string, typename OutputExpressionProviderT::OutputExpressionType>
	struct ProcessRunWithValidArgsTestDataItem
	{
		using ProcessType = CmdCalculator::Process
		<
			CmdCalculatorTestDoubles::StubCalculation
			<
				CmdCalculatorTestDoubles::StubCalculation_TParams
				<
					std::string,
					std::string,
					NonThrowingProcessTParams::StringToMathAstConverterType,
					NonThrowingProcessTParams::MathAstToExpressionConverterType,
					NonThrowingProcessTParams::ExpressionToStringConverterType
				>,
				OutputExpressionProviderT
			>,
			NonThrowingProcessTParams::RawCmdLineArgParserType,
			NonThrowingProcessTParams::RawCmdLineArgsType,
			NonThrowingProcessTParams::StringToMathAstConverterType,
			NonThrowingProcessTParams::MathAstToExpressionConverterType,
			NonThrowingProcessTParams::ExpressionToStringConverterType
		>;


		CmdCalculatorTestDoubles::FakeConsole<char> console{};
		
		CmdCalculator::ProcessConfiguration<std::string> defaultConfig{ NonThrowingProcessTParams::makeProcessConfigurationInstance() };

		std::vector<std::string> rawCmdLineArgs{};

		ProcessType::RawCmdLineArgParserType rawCmdLineArgParser
		{
			.parsedRawCmdLineArgs
			{
				.givenExpression{},
				.calculationConfiguration{0, false, false, false, false}
			}
		};
		ProcessType::StringToMathAstConverterType stringToMathAstConverter{};
		ProcessType::MathAstToExpressionConverterType mathAstToExpressionConverter{};
		ProcessType::ExpressionToStringConverterType expressionToStringConverter{};
		
		std::string expectedOutput{ OutputExpressionProviderT::getOutputExpression() };
	};

	template<class T>
	class ProcessRunWithValidArgsTests :
		public testing::Test
	{};

	using ProcessRunWithValidArgsTests_Types = testing::Types
	<
		OutputExpressionProvidersForProcess::OutputExpressionProvider,
		OutputExpressionProvidersForProcess::OtherOutputExpressionProvider
	>;

	TYPED_TEST_CASE(ProcessRunWithValidArgsTests, ProcessRunWithValidArgsTests_Types);
	
	TYPED_TEST(ProcessRunWithValidArgsTests, Calling$run$with$valid$args$returns$true)
	{
		// Arrange
		using TestDataType = ProcessRunWithValidArgsTestDataItem<TypeParam>;
		TestDataType testData{};

		typename TestDataType::ProcessType::RawCmdLineArgParserType rawCmdLineArgParser{ testData.rawCmdLineArgParser };
		typename TestDataType::ProcessType::StringToMathAstConverterType stringToMathAstConverter{ testData.stringToMathAstConverter };
		typename TestDataType::ProcessType::MathAstToExpressionConverterType mathAstToExpressionConverter{ testData.mathAstToExpressionConverter };
		typename TestDataType::ProcessType::ExpressionToStringConverterType expressionToStringConverter{ testData.expressionToStringConverter };

		typename TestDataType::ProcessType instance
		{
			std::move(rawCmdLineArgParser),
			std::move(stringToMathAstConverter),
			std::move(mathAstToExpressionConverter),
			std::move(expressionToStringConverter)
		};

		auto rawCmdLineArgs{ testData.rawCmdLineArgs };
		const CmdCalculator::ProcessConfiguration<std::string> defaultConfig{ testData.defaultConfig };
		CmdCalculatorTestDoubles::FakeConsole<char> console{};

		bool returnValue;

		// Act
		returnValue = instance.run(std::move(rawCmdLineArgs), defaultConfig, console);

		// Assert
		EXPECT_TRUE(returnValue);
	}
	
	
	TYPED_TEST(ProcessRunWithValidArgsTests, Calling$run$with$valid$args$prints$expected$answer)
	{
		// Arrange
		using TestDataType = ProcessRunWithValidArgsTestDataItem<TypeParam>;
		TestDataType testData{};

		typename TestDataType::ProcessType::RawCmdLineArgParserType rawCmdLineArgParser{ testData.rawCmdLineArgParser };
		typename TestDataType::ProcessType::StringToMathAstConverterType stringToMathAstConverter{ testData.stringToMathAstConverter };
		typename TestDataType::ProcessType::MathAstToExpressionConverterType mathAstToExpressionConverter{ testData.mathAstToExpressionConverter };
		typename TestDataType::ProcessType::ExpressionToStringConverterType expressionToStringConverter{ testData.expressionToStringConverter };

		typename TestDataType::ProcessType instance
		{
			std::move(rawCmdLineArgParser),
			std::move(stringToMathAstConverter),
			std::move(mathAstToExpressionConverter),
			std::move(expressionToStringConverter)
		};

		auto rawCmdLineArgs{ testData.rawCmdLineArgs };
		const CmdCalculator::ProcessConfiguration<std::string> defaultConfig{ testData.defaultConfig };
		CmdCalculatorTestDoubles::FakeConsole<char> console{};

		std::string expectedAnswer{ testData.expectedOutput };

		// Act
		instance.run(std::move(rawCmdLineArgs), defaultConfig, console);

		// Assert
		EXPECT_TRUE
		(
			std::ranges::any_of
			(
				console.FAKE_getTextSpans(),
				[&expectedAnswer](const CmdCalculatorTestDoubles::FakeConsole<char>::TextSpan& textSpan)
				{
					return
						textSpan.writeMode == CmdCalculator::EWriteMode::Info
						&& textSpan.text.find(expectedAnswer) != std::string::npos
					;
				}
			)
		);
	}

#pragma endregion


#pragma region Calling run with throwing component(s)

	namespace ProcessRunWithThrowingComponentsTestData
	{
		struct ProcessRunWithThrowingCalculationTestData
		{
			using ProcessType = CmdCalculator::Process
			<
				CmdCalculatorTestDoubles::StubThrowingCalculation
				<
					CmdCalculatorTestDoubles::StubCalculation_TParams
					<
						std::string,
						std::string,
						NonThrowingProcessTParams::StringToMathAstConverterType,
						NonThrowingProcessTParams::MathAstToExpressionConverterType,
						NonThrowingProcessTParams::ExpressionToStringConverterType
					>,
					std::exception
				>,
				NonThrowingProcessTParams::RawCmdLineArgParserType,
				NonThrowingProcessTParams::RawCmdLineArgsType,
				NonThrowingProcessTParams::StringToMathAstConverterType,
				NonThrowingProcessTParams::MathAstToExpressionConverterType,
				NonThrowingProcessTParams::ExpressionToStringConverterType
			>;


			static ProcessType::RawCmdLineArgParserType createRawCmdLineArgParser()
			{
				return typename ProcessType::RawCmdLineArgParserType
				{
					.parsedRawCmdLineArgs{ NonThrowingProcessTParams::makeProcessConfigurationInstance() }
				};
			}
		};


		struct ProcessRunWithThrowingRawCmdLineArgParserTestData
		{
			using ProcessType = CmdCalculator::Process
			<
				NonThrowingProcessTParams::CalculationType,
				CmdCalculatorTestDoubles::StubThrowingRawCmdLineArgParser<std::exception, std::string>,
				NonThrowingProcessTParams::RawCmdLineArgsType,
				NonThrowingProcessTParams::StringToMathAstConverterType,
				NonThrowingProcessTParams::MathAstToExpressionConverterType,
				NonThrowingProcessTParams::ExpressionToStringConverterType
			>;


			static ProcessType::RawCmdLineArgParserType createRawCmdLineArgParser()
			{
				return typename ProcessType::RawCmdLineArgParserType{};
			}
		};
	}
	
	template<class T>
	class ProcessRunWithThrowingComponentsTests :
		public testing::Test
	{};

	using ProcessRunWithThrowingComponentsTests_Types = testing::Types
	<
		ProcessRunWithThrowingComponentsTestData::ProcessRunWithThrowingCalculationTestData,
		ProcessRunWithThrowingComponentsTestData::ProcessRunWithThrowingRawCmdLineArgParserTestData
	>;

	TYPED_TEST_CASE(ProcessRunWithThrowingComponentsTests, ProcessRunWithThrowingComponentsTests_Types);

	TYPED_TEST(ProcessRunWithThrowingComponentsTests, Calling$run$with$throwing$component$prints$error)
	{
		// Arrange
		TypeParam testData{};

		typename TypeParam::ProcessType::RawCmdLineArgParserType rawCmdLineArgParser{ testData.createRawCmdLineArgParser() };
		typename TypeParam::ProcessType::StringToMathAstConverterType stringToMathAstConverter{};
		typename TypeParam::ProcessType::MathAstToExpressionConverterType mathAstToExpressionConverter{};
		typename TypeParam::ProcessType::ExpressionToStringConverterType expressionToStringConverter{};

		typename TypeParam::ProcessType instance
		{
			std::move(rawCmdLineArgParser),
			std::move(stringToMathAstConverter),
			std::move(mathAstToExpressionConverter),
			std::move(expressionToStringConverter)
		};

		std::vector<std::string> rawCmdLineArgs{};
		const CmdCalculator::ProcessConfiguration<std::string> defaultConfig{ NonThrowingProcessTParams::makeProcessConfigurationInstance() };
		CmdCalculatorTestDoubles::FakeConsole<char> console{};

		// Act
		instance.run(std::move(rawCmdLineArgs), defaultConfig, console);

		// Assert
		EXPECT_TRUE
		(
			std::ranges::any_of
			(
				console.FAKE_getTextSpans(),
				[](const CmdCalculatorTestDoubles::FakeConsole<char>::TextSpan& textSpan)
				{
					return textSpan.writeMode == CmdCalculator::EWriteMode::Error;
				}
			)
		);
	}


	TEST(ProcessRunTests, Calling$run$with$throwing$RawCmdLineArgParser$returns$false)
	{
		// Arrange
		using TestDataType = ProcessRunWithThrowingComponentsTestData::ProcessRunWithThrowingRawCmdLineArgParserTestData;
		TestDataType testData{};

		typename TestDataType::ProcessType::RawCmdLineArgParserType rawCmdLineArgParser{ testData.createRawCmdLineArgParser() };
		typename TestDataType::ProcessType::StringToMathAstConverterType stringToMathAstConverter{};
		typename TestDataType::ProcessType::MathAstToExpressionConverterType mathAstToExpressionConverter{};
		typename TestDataType::ProcessType::ExpressionToStringConverterType expressionToStringConverter{};

		typename TestDataType::ProcessType instance
		{
			std::move(rawCmdLineArgParser),
			std::move(stringToMathAstConverter),
			std::move(mathAstToExpressionConverter),
			std::move(expressionToStringConverter)
		};

		std::vector<std::string> rawCmdLineArgs{};
		const CmdCalculator::ProcessConfiguration<std::string> defaultConfig{ NonThrowingProcessTParams::makeProcessConfigurationInstance() };
		CmdCalculatorTestDoubles::FakeConsole<char> console{};

		bool returnValue;

		// Act
		returnValue = instance.run(rawCmdLineArgs, defaultConfig, console);

		// Assert
		EXPECT_FALSE(returnValue);
	}


	TEST(ProcessRunTests, Calling$run$with$throwing$RawCmdLineArgParser$doesnt$prompt$user)
	{
		// Arrange
		using TestDataType = ProcessRunWithThrowingComponentsTestData::ProcessRunWithThrowingRawCmdLineArgParserTestData;
		TestDataType testData{};

		typename TestDataType::ProcessType::RawCmdLineArgParserType rawCmdLineArgParser{ testData.createRawCmdLineArgParser() };
		typename TestDataType::ProcessType::StringToMathAstConverterType stringToMathAstConverter{};
		typename TestDataType::ProcessType::MathAstToExpressionConverterType mathAstToExpressionConverter{};
		typename TestDataType::ProcessType::ExpressionToStringConverterType expressionToStringConverter{};

		typename TestDataType::ProcessType instance
		{
			std::move(rawCmdLineArgParser),
			std::move(stringToMathAstConverter),
			std::move(mathAstToExpressionConverter),
			std::move(expressionToStringConverter)
		};

		std::vector<std::string> rawCmdLineArgs{};
		const CmdCalculator::ProcessConfiguration<std::string> defaultConfig{ NonThrowingProcessTParams::makeProcessConfigurationInstance() };
		CmdCalculatorTestDoubles::FakeConsole<char> console{};

		// Act
		instance.run(rawCmdLineArgs, defaultConfig, console);

		// Assert
		EXPECT_EQ(0, console.FAKE_getNumberOfCallsTo_getInput());
	}

#pragma endregion


#pragma region Calling run with/without given expression

	TEST(ProcessTests, Calling$run$with$given$expression$doesnt$prompt$user)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> console{};
		CmdCalculator::ProcessConfiguration<std::string> defaultConfig{ NonThrowingProcessTParams::makeProcessConfigurationInstance() };
		CmdCalculatorTestDoubles::StubRawCmdLineArgParser<std::string> rawCmdLineArgParser
		{
			.parsedRawCmdLineArgs
			{
				.givenExpression{ std::make_optional<std::string>("Given expression"s) },
				.calculationConfiguration{0, false, false, false, false}
			}
		};
		auto rawCmdLineArgs{ std::views::empty<std::string> };
		NonThrowingProcessTParams::StringToMathAstConverterType stringToMathAstConverter{};
		NonThrowingProcessTParams::MathAstToExpressionConverterType mathAstToExpressionConverter{};
		NonThrowingProcessTParams::ExpressionToStringConverterType expressionToStringConverter{};
		
		CmdCalculator::Process
		<
			NonThrowingProcessTParams::CalculationType,
			decltype(rawCmdLineArgParser),
			decltype(rawCmdLineArgs),
			decltype(stringToMathAstConverter),
			decltype(mathAstToExpressionConverter),
			decltype(expressionToStringConverter)
		> instance
		{
			std::move(rawCmdLineArgParser),
			std::move(stringToMathAstConverter),
			std::move(mathAstToExpressionConverter),
			std::move(expressionToStringConverter)
		};

		// Act
		instance.run(std::move(rawCmdLineArgs), defaultConfig, console);

		// Assert
		EXPECT_EQ(0, console.FAKE_getNumberOfCallsTo_getInput());
	}


	TEST(ProcessTests, Calling$run$without$given$expression$prompts$user)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> console{};
		CmdCalculator::ProcessConfiguration<std::string> defaultConfig{ NonThrowingProcessTParams::makeProcessConfigurationInstance() };
		CmdCalculatorTestDoubles::StubRawCmdLineArgParser<std::string> rawCmdLineArgParser
		{
			.parsedRawCmdLineArgs
			{
				.givenExpression{},
				.calculationConfiguration{0, false, false, false, false}
			}
		};
		auto rawCmdLineArgs{ std::views::empty<std::string> };
		NonThrowingProcessTParams::StringToMathAstConverterType stringToMathAstConverter{};
		NonThrowingProcessTParams::MathAstToExpressionConverterType mathAstToExpressionConverter{};
		NonThrowingProcessTParams::ExpressionToStringConverterType expressionToStringConverter{};

		CmdCalculator::Process
		<
			NonThrowingProcessTParams::CalculationType,
			decltype(rawCmdLineArgParser),
			decltype(rawCmdLineArgs),
			decltype(stringToMathAstConverter),
			decltype(mathAstToExpressionConverter),
			decltype(expressionToStringConverter)
		> instance
		{
			std::move(rawCmdLineArgParser),
			std::move(stringToMathAstConverter),
			std::move(mathAstToExpressionConverter),
			std::move(expressionToStringConverter)
		};

		// Act
		instance.run(std::move(rawCmdLineArgs), defaultConfig, console);

		// Assert
		EXPECT_EQ(1, console.FAKE_getNumberOfCallsTo_getInput());
	}

#pragma endregion


#pragma region Calling run with invalid expression input(s)

	class ProcessRunWithInvalidExpressionInputsTests :
		public testing::TestWithParam<size_t>
	{};

	INSTANTIATE_TEST_CASE_P
	(
		ProcessTests,
		ProcessRunWithInvalidExpressionInputsTests,
		testing::Values(1, 2, 3)
	);

	TEST_P(ProcessRunWithInvalidExpressionInputsTests, Invalid$expression$input$from$user$causes$reprompt)
	{
		// Arrange
		std::string validSourceExpression{ "Valid source" };
		std::string invalidSourceExpression{ "Invalid source" };
		std::vector<std::string> consoleNextInputs{};
		for (size_t i{ 0 }; i < GetParam(); i++)
			consoleNextInputs.push_back(invalidSourceExpression);
		CmdCalculatorTestDoubles::FakeConsole<char> console
		{
			validSourceExpression,
			consoleNextInputs | std::views::all,
			{}
		};
		CmdCalculator::ProcessConfiguration<std::string> defaultConfig{ NonThrowingProcessTParams::makeProcessConfigurationInstance() };
		CmdCalculatorTestDoubles::StubRawCmdLineArgParser<std::string> rawCmdLineArgParser
		{
			.parsedRawCmdLineArgs
			{
				.givenExpression{},
				.calculationConfiguration{0, false, false, false, false}
			}
		};
		auto rawCmdLineArgs{ std::views::empty<std::string> };
		CmdCalculatorTestDoubles::StubValidatingStringToMathAstConverter
		<
			std::string_view,
			NonThrowingProcessTParams::StringToMathAstConverterType::MathAstNodeType,
			CmdCalculatorTestDoubles::DummyInvalidInputExpressionException
		> stringToMathAstConverter
		{
			.validSource{ validSourceExpression }
		};
		NonThrowingProcessTParams::MathAstToExpressionConverterType mathAstToExpressionConverter{};
		NonThrowingProcessTParams::ExpressionToStringConverterType expressionToStringConverter{};

		CmdCalculator::Process
		<
			CmdCalculatorTestDoubles::FakeCalculation
			<
				std::string,
				decltype(stringToMathAstConverter),
				decltype(mathAstToExpressionConverter),
				decltype(expressionToStringConverter)
			>,
			decltype(rawCmdLineArgParser),
			decltype(rawCmdLineArgs),
			decltype(stringToMathAstConverter),
			decltype(mathAstToExpressionConverter),
			decltype(expressionToStringConverter)
		> instance
		{
			std::move(rawCmdLineArgParser),
			std::move(stringToMathAstConverter),
			std::move(mathAstToExpressionConverter),
			std::move(expressionToStringConverter)
		};

		size_t expectedPrompts{ consoleNextInputs.size() + 1 };

		// Act
		instance.run(std::move(rawCmdLineArgs), defaultConfig, console);

		// Assert
		EXPECT_EQ(expectedPrompts, console.FAKE_getNumberOfCallsTo_getInput());
	}

#pragma endregion


#pragma region Calling run with invalid given expression

	TEST(ProcessRunWithInvalidGivenExpressionTests, Invalid$given$expression$prints$error)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> console{};
		CmdCalculator::ProcessConfiguration<std::string> defaultConfig{ NonThrowingProcessTParams::makeProcessConfigurationInstance() };
		CmdCalculatorTestDoubles::StubRawCmdLineArgParser<std::string> rawCmdLineArgParser
		{
			.parsedRawCmdLineArgs
			{
				.givenExpression{ std::make_optional<std::string>("Invalid source") },
				.calculationConfiguration{ 0, false, false, false, false }
			}
		};
		auto rawCmdLineArgs{ std::views::empty<std::string> };
		CmdCalculatorTestDoubles::StubValidatingStringToMathAstConverter
		<
			std::string_view,
			NonThrowingProcessTParams::StringToMathAstConverterType::MathAstNodeType,
			CmdCalculatorTestDoubles::DummyInvalidInputExpressionException
		> stringToMathAstConverter
		{
			.validSource{ "Valid source"sv }
		};
		NonThrowingProcessTParams::MathAstToExpressionConverterType mathAstToExpressionConverter{};
		NonThrowingProcessTParams::ExpressionToStringConverterType expressionToStringConverter{};

		CmdCalculator::Process
		<
			CmdCalculatorTestDoubles::FakeCalculation
			<
				std::string,
				decltype(stringToMathAstConverter),
				decltype(mathAstToExpressionConverter),
				decltype(expressionToStringConverter)
			>,
			decltype(rawCmdLineArgParser),
			decltype(rawCmdLineArgs),
			decltype(stringToMathAstConverter),
			decltype(mathAstToExpressionConverter),
			decltype(expressionToStringConverter)
		> instance
		{
			std::move(rawCmdLineArgParser),
			std::move(stringToMathAstConverter),
			std::move(mathAstToExpressionConverter),
			std::move(expressionToStringConverter)
		};

		// Act
		instance.run(std::move(rawCmdLineArgs), defaultConfig, console);

		// Assert
		EXPECT_TRUE
		(
			std::ranges::any_of
			(
				console.FAKE_getTextSpans(),
				[](const auto textSpan)
				{
					return textSpan.writeMode == CmdCalculator::EWriteMode::Error;
				}
			)
		);
	}


	TEST(ProcessRunWithInvalidGivenExpressionTests, Invalid$given$expression$doesnt$prompt$user)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> console{};
		CmdCalculator::ProcessConfiguration<std::string> defaultConfig{ NonThrowingProcessTParams::makeProcessConfigurationInstance() };
		CmdCalculatorTestDoubles::StubRawCmdLineArgParser<std::string> rawCmdLineArgParser
		{
			.parsedRawCmdLineArgs
			{
				.givenExpression{ std::make_optional<std::string>("Invalid source") },
				.calculationConfiguration{ 0, false, false, false, false }
			}
		};
		auto rawCmdLineArgs{ std::views::empty<std::string> };
		CmdCalculatorTestDoubles::StubValidatingStringToMathAstConverter
		<
			std::string_view,
			NonThrowingProcessTParams::StringToMathAstConverterType::MathAstNodeType,
			std::exception
		> stringToMathAstConverter
		{
			.validSource{ "Valid source"sv }
		};
		NonThrowingProcessTParams::MathAstToExpressionConverterType mathAstToExpressionConverter{};
		NonThrowingProcessTParams::ExpressionToStringConverterType expressionToStringConverter{};

		CmdCalculator::Process
		<
			CmdCalculatorTestDoubles::StubCalculation
			<
				CmdCalculatorTestDoubles::StubCalculation_TParams
				<
					std::string,
					std::string,
					decltype(stringToMathAstConverter),
					decltype(mathAstToExpressionConverter),
					decltype(expressionToStringConverter)
				>,
				OutputExpressionProvidersForProcess::OutputExpressionProvider
			>,
			decltype(rawCmdLineArgParser),
			decltype(rawCmdLineArgs),
			decltype(stringToMathAstConverter),
			decltype(mathAstToExpressionConverter),
			decltype(expressionToStringConverter)
		> instance
		{
			std::move(rawCmdLineArgParser),
			std::move(stringToMathAstConverter),
			std::move(mathAstToExpressionConverter),
			std::move(expressionToStringConverter)
		};

		// Act
		instance.run(std::move(rawCmdLineArgs), defaultConfig, console);

		// Assert
		EXPECT_EQ(0, console.FAKE_getNumberOfCallsTo_getInput());
	}

#pragma endregion
}