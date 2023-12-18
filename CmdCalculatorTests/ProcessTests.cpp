#include "pch.h"

#include <string>
#include <string_view>
#include <vector>

#include "..\CmdCalculator\Process.h"
#include "..\CmdCalculatorTestDoubles/FakeConsole.h"
#include "..\CmdCalculatorTestDoubles/StubCalculation.h"
#include "..\CmdCalculatorTestDoubles/StubRawCmdLineArgParser.h"
#include "..\CmdCalculatorTestDoubles/StubMathAstNode.h"
#include "..\CmdCalculatorTestDoubles/StubExpression.h"
#include "..\CmdCalculatorTestDoubles/StubStringToMathAstConverter.h"
#include "..\CmdCalculatorTestDoubles/StubMathAstToExpressionConverter.h"
#include "..\CmdCalculatorTestDoubles/StubExpressionToStringConverter.h"

namespace CmdCalculatorTests
{
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
					CmdCalculatorTestDoubles::StubStringToMathAstConverter
					<
						std::string_view,
						CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>
					>,
					CmdCalculatorTestDoubles::StubMathAstToExpressionConverter
					<
						CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>,
						CmdCalculatorTestDoubles::Expressions::StubExpression
					>,
					CmdCalculatorTestDoubles::StubExpressionToStringConverter
					<
						CmdCalculatorTestDoubles::Expressions::StubExpression,
						std::string
					>
				>
			>,
			CmdCalculatorTestDoubles::StubRawCmdLineArgParser<std::string>,
			std::ranges::ref_view<std::vector<std::string>>,
			CmdCalculatorTestDoubles::StubStringToMathAstConverter
			<
				std::string_view,
				CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>
			>,
			CmdCalculatorTestDoubles::StubMathAstToExpressionConverter
			<
				CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>,
				CmdCalculatorTestDoubles::Expressions::StubExpression
			>,
			CmdCalculatorTestDoubles::StubExpressionToStringConverter
			<
				CmdCalculatorTestDoubles::Expressions::StubExpression,
				std::string
			>
		>;


		CmdCalculatorTestDoubles::FakeConsole<char> console{};
		
		CmdCalculator::ProcessConfiguration<std::string> defaultConfig;
		std::vector<std::string> rawCmdLineArgs;

		ProcessType::RawCmdLineArgParserType rawCmdLineArgParser;
		ProcessType::StringToMathAstConverterType stringToMathAstConverter;
		ProcessType::MathAstToExpressionConverterType mathAstToExpressionConverter;
		ProcessType::ExpressionToStringConverterType expressionToStringConverter;
		
		std::string expectedOutput;
	};

	class ProcessRunWithValidArgsTests :
		public testing::TestWithParam<ProcessRunWithValidArgsTestDataItem>
	{};

	const ProcessRunWithValidArgsTestDataItem ProcessRunWithValidArgsTestDataItems[]
	{
		ProcessRunWithValidArgsTestDataItem
		{
			.defaultConfig
			{
				.givenExpression{ std::make_optional<std::string>("0") },
				.calculationConfiguration{4, false, false, false, false}
			},
			.rawCmdLineArgs{},
			.rawCmdLineArgParser
			{
				.parsedRawCmdLineArgs
				{
					.givenExpression{ std::make_optional<std::string>("0") },
					.calculationConfiguration{4, false, false, false, false}
				}
			},
			.stringToMathAstConverter{},
			.mathAstToExpressionConverter{},
			.expressionToStringConverter{},
			.expectedOutput{ "\"0\"4,false,false,false,false,\"0\"" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		ProcessTests,
		ProcessRunWithValidArgsTests,
		testing::ValuesIn(ProcessRunWithValidArgsTestDataItems)
	);
	
	TEST_P(ProcessRunWithValidArgsTests, Calling$run$with$valid$args$prints$expected$answer)
	{
		throw CmdCalculator::NotImplementedException{};
	}

	// Calling$run$with$invalid$args$prints$error

	// Calling$run$with$invalid$args$doesnt$prompt$user

	// Calling$run$with$given$expression$doesnt$prompt$user
	
	// Calling$run$without$given$expression$prompts$user

	// Invalid$expression$input$from$user$causes$reprompt

	// Invalid$given$expression$prints$error

	// Invalid$given$expression$doesnt$prompt$user
}