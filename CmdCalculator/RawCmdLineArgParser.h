#pragma once

#include <concepts>
#include <ranges>

#include "strings.h"
#include "utilities.h"
#include "ProcessConfiguration.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref RawCmdLineArgParser concept.
	struct RawCmdLineArgParser_IntendedSatisfaction
	{};


	/// \brief An object that can parse raw command-line arguments passed to CmdCalculator.
	/// \tparam T The type of the parser.
	/// \tparam ArgsT The type of ranges of command-line arguments to parse.
	template<class T, class ArgsT>
	concept RawCmdLineArgParser =
		IntendsToSatisfy<T, RawCmdLineArgParser_IntendedSatisfaction>
		&& std::ranges::input_range<ArgsT>
		&& String<std::ranges::range_value_t<ArgsT>>
		&& String<typename T::ExpressionStringType>
		&& requires()
		{
			typename ProcessConfiguration<typename T::ExpressionStringType>;
		}
		&& requires(T && instance, ArgsT rawCmdLineArgs, const ProcessConfiguration<typename T::ExpressionStringType>& defaultConfiguration)
		{
			{ instance.parseRawCmdLineArgs(rawCmdLineArgs, defaultConfiguration) } -> std::same_as <ProcessConfiguration<typename T::ExpressionStringType>>;
		}
	;
}