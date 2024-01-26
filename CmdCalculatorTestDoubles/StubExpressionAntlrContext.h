#pragma once

#include <optional>
#include <vector>

#include "../CmdCalculator/ExpressionAntlrContext.h"
#include "StubOperandAntlrContext.h"
#include "StubOperationPartPairAntlrContext.h"

namespace CmdCalculatorTestDoubles
{
	struct StubExpressionAntlrContext :
		public CmdCalculator::ExpressionAntlrContext_IntendedSatisfaction
	{
		using OperandAntlrContextType = StubOperandAntlrContext;
		using OperationPartPairAntlrContexType = StubOperationPartPairAntlrContext;

		OperandAntlrContextType headOperand;
		std::vector<OperationPartPairAntlrContexType> operationPartPairs;


		OperandAntlrContextType getHeadOperand() const
		{
			return headOperand;
		}


		auto getOperationPartPairs() const
		{
			return operationPartPairs | std::views::all;
		}
	};
}