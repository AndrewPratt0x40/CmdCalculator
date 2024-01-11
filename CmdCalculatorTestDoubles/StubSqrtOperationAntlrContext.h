#pragma once

#include <optional>

#include "../CmdCalculator/SqrtOperationAntlrContext.h"
#include "StubAntlrToken.h"

namespace CmdCalculatorTestDoubles
{
	struct StubOperandAntlrContext;


	struct StubSqrtOperationAntlrContext :
		public CmdCalculator::SqrtOperationAntlrContext_IntendedSatisfaction
	{
		using AntlrTokenType = StubAntlrToken<std::string>;
		using OperandAntlrContextType = StubOperandAntlrContext;

		std::optional<AntlrTokenType> innerTrivia;
		OperandAntlrContextType operandValue;


		std::optional<AntlrTokenType> getInnerTrivia() const
		{
			return innerTrivia;
		}


		OperandAntlrContextType getOperandValue() const
		{
			return operandValue;
		}
	};
}