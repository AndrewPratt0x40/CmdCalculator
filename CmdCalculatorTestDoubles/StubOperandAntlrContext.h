#pragma once

#include <optional>

#include "../CmdCalculator/OperandAntlrContext.h"
#include "StubNonGroupingMultiplicationAntlrContext.h"
#include "StubGroupingMultiplicationAntlrContext.h"

namespace CmdCalculatorTestDoubles
{
	struct StubOperandAntlrContext :
		public CmdCalculator::OperandAntlrContext_IntendedSatisfaction
	{
		using NonGroupingMultiplicationAntlrContextType = StubNonGroupingMultiplicationAntlrContext;
		using GroupingMultiplicationAntlrContextType = StubGroupingMultiplicationAntlrContext;

		bool isGroupingMultiplicationValue;
		std::optional<NonGroupingMultiplicationAntlrContextType> nonGroupingMultiplicationOperand;
		std::optional<GroupingMultiplicationAntlrContextType> groupingMultiplicationOperand;


		bool isGroupingMultiplication() const
		{
			return isGroupingMultiplicationValue;
		}


		std::optional<NonGroupingMultiplicationAntlrContextType> getNonGroupingMultiplicationOperand() const
		{
			return nonGroupingMultiplicationOperand;
		}


		std::optional<GroupingMultiplicationAntlrContextType> getGroupingMultiplicationOperand() const
		{
			return groupingMultiplicationOperand;
		}
	};
}