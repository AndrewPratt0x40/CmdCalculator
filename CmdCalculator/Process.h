#pragma once

#include <string>
#include <string_view>
#include <format>
#include <concepts>
#include <utility>
#include <ranges>
#include <assert.h>

#include "NotImplementedException.h"
#include "Calculation.h"
#include "strings.h"
#include "ProcessConfiguration.h"
#include "Console.h"
#include "RawCmdLineArgParser.h"
#include "StringToMathAstConverter.h"
#include "MathAstToExpressionConverter.h"
#include "ExpressionToStringConverter.h"
#include "UnknownCmdLineArgException.h"
#include "MissingCmdLineArgValueException.h"
#include "InvalidInputExpressionException.h"

using namespace std::string_literals;
using namespace std::string_view_literals;

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
		requires
			RawCmdLineArgParser<RawCmdLineArgParserT, RawCmdLineArgsT>
			&& std::same_as<StringToMathAstConverterT, typename CalculationT::StringToMathAstConverterType>
			&& std::same_as<MathAstToExpressionConverterT, typename CalculationT::MathAstToExpressionConverterType>
			&& std::same_as<ExpressionToStringConverterT, typename CalculationT::ExpressionToStringConverterType>
	class Process
	{
	public:

		using CalculationType = CalculationT;
		using RawCmdLineArgParserType = RawCmdLineArgParserT;
		using StringToMathAstConverterType = StringToMathAstConverterT;
		using MathAstToExpressionConverterType = MathAstToExpressionConverterT;
		using ExpressionToStringConverterType = ExpressionToStringConverterT;


	private:

		RawCmdLineArgParserType m_rawCmdLineArgParser;
		StringToMathAstConverterType m_stringToMathAstConverter;
		MathAstToExpressionConverterType m_mathAstToExpressionConverter;
		ExpressionToStringConverterType m_expressionToStringConverter;

		template<String ExpressionT>
		struct CalculationResult
		{
			std::optional<ExpressionT> outputExpression;
			bool shouldReprompt;
		};

	public:
		
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
			static_assert(std::convertible_to<typename ConsoleT::StringType, ExpressionStringT>);

			const std::optional<ProcessConfiguration<ExpressionStringT>> processConfiguration
			{
				parseCmdLineArgs(std::forward<decltype(rawCmdLineArgs)>(rawCmdLineArgs), defaultConfig, console)
			};
			if (!processConfiguration.has_value())
				return false;

			typename ConsoleT::StringType inputExpression
			{
				getinputExpression(processConfiguration.value(), console)
			};

			CalculationResult<ExpressionStringT> result;

			do
			{
				result =
					tryCalculate
					<
						ConsoleT,
						ExpressionStringT
					>
					(
						inputExpression, 
						processConfiguration.value().calculationConfiguration,
						console
					)
				;
			} while (result.shouldReprompt);

			if (result.outputExpression.has_value())
			{
				console.write(std::format("= {}", result.outputExpression.value()), EWriteMode::Info);
				return true;
			}

			return false;
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
		) :
			m_rawCmdLineArgParser{ rawCmdLineArgParser },
			m_stringToMathAstConverter{ stringToMathAstConverter },
			m_mathAstToExpressionConverter{ mathAstToExpressionConverter },
			m_expressionToStringConverter{ expressionToStringConverter }
		{}


		// This overload is deleted to ensure only rvalue references are passed for the above constructor.
		Process
		(
			RawCmdLineArgParserT& rawCmdLineArgParser,
			StringToMathAstConverterT& stringToMathAstConverter,
			MathAstToExpressionConverterT& mathAstToExpressionConverter,
			ExpressionToStringConverterT& expressionToStringConverter
		) = delete;


	private:

		/// \brief Attempts to parse the raw command-line arguments given to the process.
		/// \tparam ConsoleT The type of the console object to be used by the process.
		/// \tparam ExpressionStringT The string type that represents a given expression.
		/// \tparam ArgsT The type to use for the range of command-line arguments passed to the process.
		/// \param rawCmdLineArgs A range of the command-line parameters passed to the process.
		/// \param defaultConfig The default process configuration to use.
		/// \param console The text console to use for input and output.
		/// \returns The process configuration resulting from the parsed command-line arguments, or an empty value if parsing failed.
		template<Console ConsoleT, String ExpressionStringT, std::ranges::input_range ArgsT>
			requires String<std::ranges::range_value_t<ArgsT>>
		std::optional<ProcessConfiguration<ExpressionStringT>> parseCmdLineArgs
		(
			ArgsT&& rawCmdLineArgs,
			const ProcessConfiguration<ExpressionStringT> defaultConfig,
			ConsoleT& console
		)
		{
			using ArgType = std::ranges::range_value_t<ArgsT>;

			std::optional<ProcessConfiguration<ExpressionStringT>> processConfiguration;

			try
			{
				processConfiguration = m_rawCmdLineArgParser.parseRawCmdLineArgs(std::forward<decltype(rawCmdLineArgs)>(rawCmdLineArgs), defaultConfig);
			}
			catch (const UnknownCmdLineArgException<ArgType>& exception)
			{
				console.writeLine(std::format("Unknown argument, \"{}\"", exception.getArg()), EWriteMode::Error);
				return {};
			}
			catch (const MissingCmdLineArgValueException<ArgType>& exception)
			{
				console.writeLine(std::format("Missing value for argument, \"{}\"", exception.getArg()), EWriteMode::Error);
				return {};
			}
			catch (...)
			{
				console.writeLine("An unknown error occurred while reading the command-line arguments.", EWriteMode::Error);
				return {};
			}

			assert(processConfiguration.has_value());
			return processConfiguration;
		}


		/// \brief Determines the string representing the expression to be calculated.
		/// \tparam ConsoleT The type of the console object to be used by the process.
		/// \tparam ExpressionStringT The string type that represents a given expression.
		/// \param config The process configuration to use.
		/// \param console The text console to use for input and output.
		/// \returns The string representation of the expression to calculate.
		template<Console ConsoleT, String ExpressionStringT>
		ExpressionStringT getinputExpression
		(
			const ProcessConfiguration<ExpressionStringT> config,
			ConsoleT& console
		)
		{
			return config.givenExpression.has_value()
				? config.givenExpression.value()
				: promptForExpression(console)
			;
		}


		/// \brief Attempts to calculate an expression.
		/// \tparam ConsoleT The type of the console object to be used by the process.
		/// \tparam OutputExpressionT The string type that represents a calculated expression.
		/// \param inputExpression The expression to calculate.
		/// \param config The calculation configuration to use.
		/// \param console The text console to use for input and output.
		/// \returns The result .
		template<Console ConsoleT, String OutputExpressionT>
		CalculationResult<OutputExpressionT> tryCalculate
		(
			typename CalculationType::InputExpressionType inputExpression,
			CalculationConfiguration config,
			ConsoleT& console
		)
		{
			CalculationType calculation
			{
				CalculationType
				(
					inputExpression,
					config,
					m_stringToMathAstConverter,
					m_mathAstToExpressionConverter,
					m_expressionToStringConverter
				)
			};

			try
			{
				OutputExpressionT outputExpression{ calculation.getOutputExpression() };
				return CalculationResult<OutputExpressionT>
				{
					.outputExpression{ std::make_optional<OutputExpressionT>(outputExpression) },
					.shouldReprompt{ false }
				};
			}
			// TODO: Catch other errors
			catch (const InvalidInputExpressionException&)
			{
				console.writeLine("Expression is invalid for unknown reasons.", EWriteMode::Error);
			}
			catch (...)
			{
				console.writeLine("An unknown error occurred while calculating.", EWriteMode::Error);
			}

			return CalculationResult<OutputExpressionT>
			{
				.outputExpression{},
				.shouldReprompt{ false }
			};
		}


		/// \brief Prompts the user for an expression to calculate.
		/// \tparam ConsoleT The type of the console object to be used by the process.
		/// \param console The text console to use for input and output.
		/// \returns The expression inputted by the user.
		template<Console ConsoleT>
		ConsoleT::StringType promptForExpression(ConsoleT& console)
		{
			console.write("Enter an expression: ", EWriteMode::Info);
			return console.getInput();
		}
	};
}