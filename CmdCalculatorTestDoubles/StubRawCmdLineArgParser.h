#pragma once

#include <concepts>
#include <ranges>

#include "../CmdCalculator/RawCmdLineArgParser.h"
#include "../CmdCalculator/ProcessConfiguration.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::String ExpressionStringT>
	struct StubRawCmdLineArgParser :
		public CmdCalculator::RawCmdLineArgParser_IntendedSatisfaction
	{
		CmdCalculator::ProcessConfiguration<ExpressionStringT> parsedRawCmdLineArgs;

		
		CmdCalculator::ProcessConfiguration<ExpressionStringT> parseRawCmdLineArgs
		(
			auto&& rawCmdLineArgs,
			const CmdCalculator::ProcessConfiguration<ExpressionStringT>& defaultConfiguration
		) const
			requires std::ranges::input_range<decltype(rawCmdLineArgs)>
			&& CmdCalculator::String<std::ranges::range_value_t<decltype(rawCmdLineArgs)>>
		{
			return parsedRawCmdLineArgs;
		}
	};
}