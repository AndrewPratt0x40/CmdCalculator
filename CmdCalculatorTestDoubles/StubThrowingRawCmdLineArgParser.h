#pragma once

#include <concepts>
#include <ranges>

#include "../CmdCalculator/RawCmdLineArgParser.h"
#include "../CmdCalculator/ProcessConfiguration.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles
{
	template<class ExceptionT, CmdCalculator::String ExpressionStringT>
	struct StubThrowingRawCmdLineArgParser :
		public CmdCalculator::RawCmdLineArgParser_IntendedSatisfaction
	{
		using ExceptionType = ExceptionT;
		using ExpressionStringType = ExpressionStringT;

		ExceptionT exceptionToThrow;


		CmdCalculator::ProcessConfiguration<ExpressionStringT> parseRawCmdLineArgs
		(
			auto&& rawCmdLineArgs,
			const CmdCalculator::ProcessConfiguration<ExpressionStringT>& defaultConfiguration
		) const
			requires std::ranges::forward_range<decltype(rawCmdLineArgs)>
		&& CmdCalculator::String<std::ranges::range_value_t<decltype(rawCmdLineArgs)>>
		{
			throw exceptionToThrow;
		}
	};
}