#pragma once

#include <ranges>
#include <span>

#include "../CmdCalculator/GroupingMultiplicationAntlrContext.h"
#include "StubNonGroupingMultiplicationAntlrContext.h"
#include "StubGroupingTailMultiplicandAntlrContext.h"

namespace CmdCalculatorTestDoubles
{
	struct StubGroupingMultiplicationAntlrContext :
		public CmdCalculator::GroupingMultiplicationAntlrContext_IntendedSatisfaction
	{
		using NonGroupingMultiplicationAntlrContextType = StubNonGroupingMultiplicationAntlrContext;
		using GroupingTailMultiplicandAntlrContextType = StubGroupingTailMultiplicandAntlrContext;

		NonGroupingMultiplicationAntlrContextType headMultiplicand;
		std::span<GroupingTailMultiplicandAntlrContextType> tailMultiplicands;


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