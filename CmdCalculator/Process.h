#pragma once

#include <concepts>
#include <ranges>

#include "NotImplementedException.h"
#include "Calculation.h"
#include "strings.h"
#include "ProcessConfiguration.h"
#include "Console.h"
#include "RawCmdLineArgParser.h"
#include "StringToMathAstConverter.h"
#include "MathAstToExpressionConverter.h"
#include "ExpressionToStringConverter.h"

namespace CmdCalculator
{
	/// \brief A CmdCalculator process.
	template
	<
		Calculation CalculationT,
		class RawCmdLineArgParserT,
		class RawCmdLineArgsT,
		StringToMathAstConverter StringToMathAstConverterT,
		MathAstToExpressionConverter MathAstToExpressionConverterT,
		ExpressionToStringConverter ExpressionToStringConverterT
	>
		requires RawCmdLineArgParser<RawCmdLineArgParserT, RawCmdLineArgsT>
	class Process
	{
	public:

		using CalculationType = CalculationT;
		using RawCmdLineArgParserType = RawCmdLineArgParserT;
		using StringToMathAstConverterType = StringToMathAstConverterT;
		using MathAstToExpressionConverterType = MathAstToExpressionConverterT;
		using ExpressionToStringConverterType = ExpressionToStringConverterT;
		
		/// \brief Executes the process.
		/// \tparam ConsoleT The type of the console object to be used by the process.
		/// \tparam ExpressionStringT The string type that represents a given expression.
		/// \tparam ArgsT The type to use for the range of command-line arguments passed to the process.
		/// \param rawCmdLineArgs A range of the command-line parameters passed to the process.
		/// \param config The process configuration.
		/// \param console The text console to use for input and output.
		/// \returns True if the process ran successfully, false if the process exited due to an error.
		template<Console ConsoleT, String ExpressionStringT, std::ranges::input_range ArgsT>
			requires String<std::ranges::range_value_t<ArgsT>>
		bool run(ArgsT&& rawCmdLineArgs, const ProcessConfiguration<ExpressionStringT> defaultConfig, ConsoleT& console)
		{
			throw NotImplementedException{};
		}


		/// Creates a new instance of the \ref Process class.
		/// \param rawCmdLineArgParser The raw command-line argument parser to use.
		/// \param expressionToStringConverter The object to convert the calculated expression into a human-readable string for output.
		/// \param mathAstToExpressionConverter The object to convert a mathematical abstract syntax tree into an expression object.
		/// \param stringToMathAstConverter The object to parse the input expression into an abstract syntax tree.
		Process
		(
			RawCmdLineArgParserT&& rawCmdLineArgParser,
			StringToMathAstConverterT&& stringToMathAstConverter,
			MathAstToExpressionConverterT&& mathAstToExpressionConverter,
			ExpressionToStringConverterT&& expressionToStringConverter
		)
		{
			throw NotImplementedException{};
		}


		// This overload is deleted to ensure only rvalue references are passed for the above constructor.
		Process
		(
			RawCmdLineArgParserT& rawCmdLineArgParser,
			ExpressionToStringConverterT& expressionToStringConverter,
			MathAstToExpressionConverterT& mathAstToExpressionConverter,
			StringToMathAstConverterT& stringToMathAstConverter
		) = delete;
	};
}