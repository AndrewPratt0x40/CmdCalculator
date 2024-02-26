#pragma once

#include <optional>

#include "../CmdCalculator/GroupingTailMultiplicandAntlrContext.h"
#include "StubAntlrToken.h"
#include "StubGroupingAntlrContext.h"

namespace CmdCalculatorTestDoubles
{
	struct StubGroupingTailMultiplicandAntlrContext :
		public ::CmdCalculator::GroupingTailMultiplicandAntlrContext_IntendedSatisfaction
	{
		using AntlrTokenType = StubAntlrToken<std::string>;
		using GroupingAntlrContextType = StubGroupingAntlrContext;

		std::optional<AntlrTokenType> innerTrivia;
		GroupingAntlrContextType groupingValue;


		std::optional<AntlrTokenType> getInnerTrivia() const
		{
			return innerTrivia;
		}


		GroupingAntlrContextType getGroupingValue() const
		{
			return groupingValue;
		}
	};
}