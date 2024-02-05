#pragma once

#include <string>
#include <string_view>
#include <format>
#include <concepts>
#include <algorithm>
#include <utility>
#include <ranges>
#include <assert.h>

#include "NotImplementedException.h"
#include "Calculation.h"
#include "strings.h"
#include "ProcessConfiguration.h"
#include "Console.h"
#include "RealNumber.h"
#include "RawCmdLineArgParser.h"
#include "StringToMathAstConverter.h"
#include "MathAstToExpressionConverter.h"
#include "ExpressionToStringConverter.h"
#include "UnknownCmdLineArgException.h"
#include "MissingCmdLineArgValueException.h"
#include "InvalidInputExpressionException.h"
#include "EmptyInputExpressionException.h"
#include "UnexpectedInputExpressionCharException.h"
#include "ExpressionEvaluationException.h"
#include "DivisionByZeroException.h"

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
			using ExpressionType = ExpressionT;

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
						getinputExpression(processConfiguration.value(), console),
						processConfiguration.value().calculationConfiguration,
						console
					)
				;
			} while (result.shouldReprompt && !processConfiguration.value().givenExpression.has_value());

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


		void writeToConsole(Console auto& console, const String auto text, const EWriteMode writeMode)
		{
			const auto convertedString
			{
				convertString<typename std::remove_reference_t<decltype(console)>::StringType::value_type>
				(text)
			};
			console.write(convertedString, writeMode);
		}


		void writeLineToConsole(Console auto& console, const String auto text, const EWriteMode writeMode)
		{
			const auto convertedString
			{
				convertString<typename std::remove_reference_t<decltype(console)>::StringType::value_type>
				(text)
			};
			console.writeLine(convertedString, writeMode);
		}


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
				writeLineToConsole
				(
					console,
					std::format
					(
						"Unknown argument, \"{}\"",
						convertString<char>(exception.getArg())
					),
					EWriteMode::Error
				);
				return {};
			}
			catch (const MissingCmdLineArgValueException<ArgType>& exception)
			{
				writeLineToConsole
				(
					console,
					std::format
					(
						"Missing value for argument, \"{}\"",
						convertString<char>(exception.getArg())
					),
					EWriteMode::Error
				);
				return {};
			}
			catch (...)
			{
				writeLineToConsole
				(
					console,
					"An unknown error occurred while reading the command-line arguments."s,
					EWriteMode::Error
				);
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

			bool shouldRepromptOnFailure{};

			// TODO: Error message generation should be handled by a separate component.
			try
			{
				OutputExpressionT outputExpression{ calculation.getOutputExpression() };
				return CalculationResult<OutputExpressionT>
				{
					.outputExpression{ std::make_optional<OutputExpressionT>(outputExpression) },
					.shouldReprompt{ false }
				};
			}
			catch (const EmptyInputExpressionException&)
			{
				writeLineToConsole
				(
					console,
					"Expression cannot be empty."s,
					EWriteMode::Error
				);
				shouldRepromptOnFailure = true;
			}
			catch (const UnexpectedInputExpressionCharException& exception)
			{
				const size_t charIndex{ exception.getCharIndex() };
				const std::basic_string<typename decltype(inputExpression)::value_type> convertedInputExpression{ inputExpression };

				writeLineToConsole
				(
					console,
					std::format
					(
						"Unexpected character, \"{}\" at column {}.",
						convertChar<char>(convertedInputExpression.at(charIndex)),
						charIndex
					),
					EWriteMode::Error
				);

				if (!exception.getExpectedValues().empty())
				{
					writeLineToConsole
					(
						console,
						"\tExpected any of:"s,
						EWriteMode::Error
					);
					for (const auto& expectedValue : exception.getExpectedValues())
					{
						writeLineToConsole
						(
							console,
							std::format
							(
								"\t  - {}",
								expectedValue
							),
							EWriteMode::Error
						);
					}
				}

				constexpr size_t maxSpanLength{ 8 };

				if (charIndex > maxSpanLength)
				{
					writeLineToConsole
					(
						console,
						std::format
						(
							"\tAfter: ...{}",
							convertString<char>
							(
								convertedInputExpression.substr
								(
									charIndex - maxSpanLength,
									maxSpanLength
								)
							)
						),
						EWriteMode::Error
					);
				}
				else if (charIndex > 0)
				{
					writeLineToConsole
					(
						console,
						std::format
						(
							"\tAfter: {}",
							convertString<char>
							(
								convertedInputExpression.substr
								(
									0,
									charIndex
								)
							)
						),
						EWriteMode::Error
					);
				}

				const size_t maxIndex{ convertedInputExpression.size() - 1 };

				if (charIndex < maxIndex - maxSpanLength)
				{
					writeLineToConsole
					(
						console,
						std::format
						(
							"\tBefore: {}...",
							convertString<char>
							(
								convertedInputExpression.substr
								(
									charIndex + 1,
									maxSpanLength
								)
							)
						),
						EWriteMode::Error
					);
				}
				else if (charIndex < maxIndex - 1)
				{
					writeLineToConsole
					(
						console,
						std::format
						(
							"\tBefore: {}",
							convertString<char>
							(
								convertedInputExpression.substr
								(
									charIndex + 1,
									maxIndex - charIndex
								)
							)
						),
						EWriteMode::Error
					);
				}

				shouldRepromptOnFailure = true;
			}
			catch (const InvalidInputExpressionException&)
			{
				writeLineToConsole
				(
					console,
					"Expression is invalid for unknown reasons."s,
					EWriteMode::Error
				);
				shouldRepromptOnFailure = true;
			}
			catch (const DivisionByZeroException& exception)
			{
				writeLineToConsole
				(
					console,
					std::format
					(
						"Attempted to divide {} by zero while evaluating expression.",
						exception.getDividend()
					),
					EWriteMode::Error
				);
			}
			catch (const ExpressionEvaluationException&)
			{
				writeLineToConsole
				(
					console,
					"An unknown error occurred while evaluating the expression."s,
					EWriteMode::Error
				);
				shouldRepromptOnFailure = true;
			}
			catch (...)
			{
				writeLineToConsole
				(
					console,
					"An unknown error occurred while calculating."s,
					EWriteMode::Error
				);
				shouldRepromptOnFailure = false;
			}

			return CalculationResult<OutputExpressionT>
			{
				.outputExpression{},
				.shouldReprompt{ shouldRepromptOnFailure }
			};
		}


		/// \brief Prompts the user for an expression to calculate.
		/// \param console The text console to use for input and output.
		/// \returns The expression inputted by the user.
		String auto promptForExpression(Console auto& console)
		{
			writeToConsole
			(
				console,
				"Enter an expression: "s,
				EWriteMode::Info
			);
			return console.getInput();
		}
	};
}