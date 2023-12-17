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
	template<class T>
	concept RawCmdLineArgParser =
		std::ranges::input_range<typename T::ArgsType>
		&& String<std::ranges::range_value_t<typename T::ArgsType>>
		&& Expressions::Expression<typename T::ExpressionStringType>
		&& requires()
		{
			typename ProcessConfiguration<typename T::ExpressionStringType>;
		}
		&& requires(T && instance, typename T::ArgsType rawCmdLineArgs, const ProcessConfiguration<typename T::ExpressionStringT>& defaultConfiguration)
		{
			{ instance.parseRawCmdLineArgs(rawCmdLineArgs, defaultConfiguration) } -> std::same_as <ProcessConfiguration<typename T::ExpressionStringType>>;
		}
	;
}