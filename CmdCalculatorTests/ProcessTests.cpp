#include "pch.h"

#include <string>
#include <string_view>
#include <vector>

#include "..\CmdCalculator\Process.h"
#include "..\CmdCalculatorTestDoubles/FakeConsole.h"
#include "..\CmdCalculatorTestDoubles/StubCalculation.h"
#include "..\CmdCalculatorTestDoubles/StubThrowingCalculation.h"
#include "..\CmdCalculatorTestDoubles/StubRawCmdLineArgParser.h"
#include "..\CmdCalculatorTestDoubles/StubThrowingRawCmdLineArgParser.h"
#include "..\CmdCalculatorTestDoubles/StubMathAstNode.h"
#include "..\CmdCalculatorTestDoubles/StubExpression.h"
#include "..\CmdCalculatorTestDoubles/StubStringToMathAstConverter.h"
#include "..\CmdCalculatorTestDoubles/StubMathAstToExpressionConverter.h"
#include "..\CmdCalculatorTestDoubles/StubExpressionToStringConverter.h"

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
			CmdCalculatorTestDoubles::Expressions::StubExpression
		>;

		using ExpressionToStringConverterType = CmdCalculatorTestDoubles::StubExpressionToStringConverter
		<
			CmdCalculatorTestDoubles::Expressions::StubExpression,
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


		CmdCalculator::ProcessConfiguration<std::string> makeProcessConfigurationInstance()
		{
			return CmdCalculator::ProcessConfiguration<std::string>
			{
				.givenExpression{ std::make_optional<std::string>("0") },
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

		ProcessType::RawCmdLineArgParserType rawCmdLineArgParser{};
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
	
	TYPED_TEST(ProcessRunWithValidArgsTests, Calling$run$with$valid$args$prints$expected$answer)
	{
		throw CmdCalculator::NotImplementedException{};
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
		throw CmdCalculator::NotImplementedException{};
	}

#pragma endregion

	// Calling$run$with$throwing$component$doesnt$prompt$user

	// Calling$run$with$given$expression$doesnt$prompt$user
	
	// Calling$run$without$given$expression$prompts$user

	// Invalid$expression$input$from$user$causes$reprompt

	// Invalid$given$expression$prints$error

	// Invalid$given$expression$doesnt$prompt$user
}