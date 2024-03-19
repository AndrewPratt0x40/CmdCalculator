#include <concepts>
#include <ranges>
#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <span>
#include <sstream>
#include <vector>
#include <assert.h>

#include "../CmdCalculator/Process.h"
#include "../CmdCalculator/BasicCalculation.h"
#include "../CmdCalculator/AntlrBasedStringToMathAstConverter.h"
#include "../CmdCalculator/AntlrInvokingStringToAntlrContextConverter.h"
#include "../CmdCalculator/AntlrContextToDynamicMathAstConverter.h"
#include "../CmdCalculator/OwningTrueFullExpressionAntlrContext.h"
#include "../CmdCalculator/BasicDynamicMathAstToDynamicExpressionConverter.h"
#include "../CmdCalculator/SingularInvokingDEPSplitter.h"
#include "../CmdCalculator/BasicDEPSingleSplitter.h"
#include "../CmdCalculator/BasicRSRToDynamicExpressionConverter.h"
#include "../CmdCalculator/BasicDynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculator/ExpressionEvaluationToStringConverter.h"
#include "../CmdCalculator/BasicRawCmdLineArgParser.h"
#include "../CmdCalculator/StreamBasedConsole.h"
#include "../CmdCalculator/ProcessConfiguration.h"

template<class CharT>
inline int mainImpl
(
	CharT argc,
	CharT* argv[],
	std::basic_istream<CharT>& inputStream,
	std::basic_ostream<CharT>& infoStream,
	std::basic_ostream<CharT>& errorStream,
	std::basic_ostream<CharT>& debugStream
);


#ifdef _UNICODE
int wmain(int argc, wchar_t* argv[])
{
#ifdef NDEBUG
	std::wostream& debugStream{ std::wcout };
#else
	std::wstringstream debugStream{};
#endif

	return mainImpl<wchar_t>
	(
		argc,
		argv,
		std::wcin,
		std::wcout,
		std::wcerr,
		debugStream
	);
}
#else
int main(int argc, char* argv[])
{
#ifdef NDEBUG
	std::ostream& debugStream{ std::cout };
#else
	std::stringstream debugStream{};
#endif

	return mainImpl<char>
	(
		argc,
		argv,
		std::cin,
		std::cout,
		std::cerr,
		debugStream
	);
}
#endif


template<class CharT>
inline int mainImpl
(
	CharT argc,
	CharT* argv[],
	std::basic_istream<CharT>& inputStream,
	std::basic_ostream<CharT>& infoStream,
	std::basic_ostream<CharT>& errorStream,
	std::basic_ostream<CharT>& debugStream
)
{
	using CharType = CharT;
	using StringType = std::basic_string<CharType>;
	using StringViewType = std::basic_string_view<CharType>;

	const std::span cmdLineArgsSpan{ argv, argc };
	std::ranges::forward_range auto cmdLineArgsView
	{
		cmdLineArgsSpan
		| std::views::drop(1) // Drop the first argument, since it's just the name of the executable.
		| std::views::transform
		(
			[](CharT* argCStr)
			{ return StringType{argCStr}; }
		)
	};

#pragma region Types
	// TODO: Consider defining aliases in the CmdCalculator project so that so many types don't need to be given.

	using StringToAntlrContextConverterType = CmdCalculator::AntlrInvokingStringToAntlrContextConverter<StringViewType>;
	using AntlrContextToMathAstConverterType = CmdCalculator::AntlrContextToDynamicMathAstConverter
	<
		CmdCalculator::OwningTrueFullExpressionAntlrContext,
		CharType
	>;
	using StringToMathAstConverterType = CmdCalculator::AntlrBasedStringToMathAstConverter
	<
		StringViewType,
		StringToAntlrContextConverterType,
		AntlrContextToMathAstConverterType
	>;

	using DynamicExpressionPartSingleSplitterType = CmdCalculator::BasicDEPSingleSplitter<StringType>;
	using DynamicExpressionPartRecursiveSplitterType = CmdCalculator::SingularInvokingDEPSplitter<DynamicExpressionPartSingleSplitterType>;
	using OperandConverterType = CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<StringType>;
	using RecursiveSplitResultToDyamicExpressionConverterType = CmdCalculator::BasicRSRToDynamicExpressionConverter
	<
		CmdCalculator::SplitResultType<DynamicExpressionPartRecursiveSplitterType>,
		OperandConverterType,
		StringType
	>;
	using MathAstToExpressionConverterType = CmdCalculator::BasicDynamicMathAstToDynamicExpressionConverter
	<
		DynamicExpressionPartRecursiveSplitterType,
		RecursiveSplitResultToDyamicExpressionConverterType
	>;

	using ExpressionToStringConverterType = CmdCalculator::ExpressionEvaluationToStringConverter
	<
		typename MathAstToExpressionConverterType::OutputExpressionType
	>;
	
	using CalculationType = CmdCalculator::BasicCalculation
	<
		StringType,
		StringToMathAstConverterType,
		MathAstToExpressionConverterType,
		ExpressionToStringConverterType
	>;

	using RawCmdLineArgParserType = CmdCalculator::BasicRawCmdLineArgParser<StringType>;

	using ConsoleType = CmdCalculator::StreamBasedConsole<CharT>;

	using ProcessType = CmdCalculator::Process
	<
		CalculationType,
		RawCmdLineArgParserType,
		decltype(cmdLineArgsView),
		StringToMathAstConverterType,
		MathAstToExpressionConverterType,
		ExpressionToStringConverterType
	>;
#pragma endregion


#pragma region Process components

	RawCmdLineArgParserType rawCmdLineArgParser{};

	StringToAntlrContextConverterType stringToAntlrContextConverter{};
	AntlrContextToMathAstConverterType antlrContextToMathAstConverter{};
	StringToMathAstConverterType stringToMathAstConverter
	{
		std::move(stringToAntlrContextConverter),
		std::move(antlrContextToMathAstConverter)
	};

	DynamicExpressionPartSingleSplitterType dynamicExpressionPartSingleSplitter{};
	DynamicExpressionPartRecursiveSplitterType dynamicExpressionPartRecursiveSplitter
	{
		std::move(dynamicExpressionPartSingleSplitter)
	};

	std::optional<typename OperandConverterType::InnerConverterFunctorType> innerOperandConverterWrapper{};
	OperandConverterType operandConverter
	{
		[&innerOperandConverterWrapper](const CmdCalculator::MathAst::DynamicExpressionNode<StringType>& sourceRootNode)
		{
			assert(innerOperandConverterWrapper.has_value());
			return innerOperandConverterWrapper.value()(sourceRootNode);
		}
	};
	RecursiveSplitResultToDyamicExpressionConverterType recursiveSplitResultToDyamicExpressionConverter
	{
		operandConverter
	};

	MathAstToExpressionConverterType mathAstToExpressionConverter
	{
		std::move(dynamicExpressionPartRecursiveSplitter),
		std::move(recursiveSplitResultToDyamicExpressionConverter)
	};

	// TODO: Modify math AST to expression conversions so that operandConverter can have it's inner converter automatically set.
	//	Due to the fact that mathAstToExpressionConverter needs to be moved into the process instance, a
	//	duplicate MathAstToExpressionConverterType instance needs to be created so that operandConverter's
	//	inner converter doesn't use a dangling reference.
#pragma region Ugly operand inner converter work-around
	DynamicExpressionPartSingleSplitterType dynamicExpressionPartSingleSplitter2{};
	DynamicExpressionPartRecursiveSplitterType dynamicExpressionPartRecursiveSplitter2
	{
		std::move(dynamicExpressionPartSingleSplitter2)
	};

	RecursiveSplitResultToDyamicExpressionConverterType recursiveSplitResultToDyamicExpressionConverter2
	{
		operandConverter
	};

	MathAstToExpressionConverterType mathAstToExpressionConverter2
	{
		std::move(dynamicExpressionPartRecursiveSplitter2),
		std::move(recursiveSplitResultToDyamicExpressionConverter2)
	};

	innerOperandConverterWrapper = [&mathAstToExpressionConverter2](const CmdCalculator::MathAst::DynamicExpressionNode<StringType>& sourceRootNode)
	{
		return mathAstToExpressionConverter2.getMathAstAsExpression(sourceRootNode);
	};
#pragma endregion

	ExpressionToStringConverterType expressionToStringConverter{};

	const CmdCalculator::ProcessConfiguration<StringType> defaultConfig
	{
		.givenExpression{},
		.calculationConfiguration{ 8, false, false, true, true }
	};

	ConsoleType console
	{
		inputStream,
		infoStream,
		errorStream,
		debugStream
	};

#pragma endregion

	ProcessType process
	{
		std::move(rawCmdLineArgParser),
		std::move(stringToMathAstConverter),
		std::move(mathAstToExpressionConverter),
		std::move(expressionToStringConverter)
	};

	if (process.run(cmdLineArgsView, defaultConfig, console))
		return EXIT_SUCCESS;
	return EXIT_FAILURE;
}