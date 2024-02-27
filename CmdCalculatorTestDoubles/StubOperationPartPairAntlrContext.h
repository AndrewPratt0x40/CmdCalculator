#pragma once

#include <optional>

#include "../CmdCalculator/OperationPartPairAntlrContext.h"
#include "StubAntlrToken.h"
#include "StubBinaryOperatorAntlrContext.h"
#include "StubOperandAntlrContext.h"

namespace CmdCalculatorTestDoubles
{
	struct StubOperationPartPairAntlrContext :
		public CmdCalculator::OperationPartPairAntlrContext_IntendedSatisfaction
	{
		using AntlrTokenType = StubAntlrToken<std::string>;
		using BinaryOperatorAntlrContextType = StubBinaryOperatorAntlrContext;
		using OperandAntlrContextType = StubOperandAntlrContext;

		std::optional<AntlrTokenType> operatorLeadingTrivia;
		BinaryOperatorAntlrContextType operatorValue;
		std::optional<AntlrTokenType> operatorTrailingTrivia;
		OperandAntlrContextType operandValue;


		std::optional<AntlrTokenType> getOperatorLeadingTrivia() const
		{
			return operatorLeadingTrivia;
		}


		BinaryOperatorAntlrContextType getOperatorValue() const
		{
			return operatorValue;
		}


		std::optional<AntlrTokenType> getOperatorTrailingTrivia() const
		{
			return operatorTrailingTrivia;
		}


		OperandAntlrContextType getOperandValue() const
		{
			return operandValue;
		}
	};
}