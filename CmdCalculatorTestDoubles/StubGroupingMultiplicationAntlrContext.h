#pragma once

#include <ranges>
#include <vector>

#include "../CmdCalculator/GroupingMultiplicationAntlrContext.h"
#include "StubNonGroupingMultiplicationAntlrContext.h"
#include "StubGroupingTailMultiplicandAntlrContext.h"

namespace CmdCalculatorTestDoubles
{
	struct StubGroupingMultiplicationAntlrContext :
		public ::CmdCalculator::GroupingMultiplicationAntlrContext_IntendedSatisfaction
	{
		using NonGroupingMultiplicationAntlrContextType = StubNonGroupingMultiplicationAntlrContext;
		using GroupingTailMultiplicandAntlrContextType = StubGroupingTailMultiplicandAntlrContext;

		NonGroupingMultiplicationAntlrContextType headMultiplicand;
		std::vector<GroupingTailMultiplicandAntlrContextType> tailMultiplicands;


		NonGroupingMultiplicationAntlrContextType getHeadMultiplicand() const
		{
			return headMultiplicand;
		}


		auto getTailMultiplicands() const
		{
			return tailMultiplicands | std::views::all;
		}
	};
}