#pragma once

#include <concepts>
#include <ranges>

#include "strings.h"
#include "ProcessConfiguration.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref RawCmdLineArgParser concept.
	struct RawCmdLineArgParser_IntendedSatisfaction
	{};


	/// \brief An object that can parse raw command-line arguments passed to CmdCalculator.
	/// \tparam T The type of the parser.
	/// \tparam ArgsT The type to use for ranges of command-line arguments.
	/// \tparam ExpressionStringT The string type that represents a given expression.
	template<class T, class ArgsT, class ExpressionStringT>
	concept RawCmdLineArgParser =
		std::ranges::input_range<ArgsT>
		&& String<std::ranges::range_value_t<ArgsT>>
		&& requires()
		{
			typename ProcessConfiguration<ExpressionStringT>;
		}
		&& requires(T && instance, ArgsT rawCmdLineArgs, const ProcessConfiguration<ExpressionStringT>& defaultConfiguration)
		{
			{ instance.parseRawCmdLineArgs(rawCmdLineArgs, defaultConfiguration) } -> std::same_as <ProcessConfiguration<ExpressionStringT>>;
		}
	;
}