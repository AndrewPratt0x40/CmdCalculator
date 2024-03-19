#pragma once

#include <optional>
#include <memory>
#include <assert.h>

#include "../CmdCalculator/SignOperationAntlrContext.h"
#include "StubSignOperatorAntlrContext.h"
#include "StubAntlrToken.h"

namespace CmdCalculatorTestDoubles
{
	struct StubOperandAntlrContext;


	struct StubSignOperationAntlrContext :
		public CmdCalculator::SignOperationAntlrContext_IntendedSatisfaction
	{
		using SignOperatorAntlrContextType = StubSignOperatorAntlrContext;
		using AntlrTokenType = StubAntlrToken<std::string>;
		using OperandAntlrContextType = StubOperandAntlrContext;

		SignOperatorAntlrContextType signOperator;
		std::optional<AntlrTokenType> innerTrivia;
		std::shared_ptr<OperandAntlrContextType> operandValue;


		SignOperatorAntlrContextType getSignOperator() const
		{
			return signOperator;
		}


		std::optional<AntlrTokenType> getInnerTrivia() const
		{
			return innerTrivia;
		}


		OperandAntlrContextType& getOperandValue() const
		{
			assert(operandValue);
			return *operandValue;
		}
	};
}