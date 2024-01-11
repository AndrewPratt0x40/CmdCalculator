#pragma once

#include <optional>

#include "../CmdCalculator/SignOperatorAntlrContext.h"
#include "StubAntlrToken.h"

namespace CmdCalculatorTestDoubles
{
	struct StubSignOperatorAntlrContext :
		public CmdCalculator::SignOperatorAntlrContext_IntendedSatisfaction
	{
		using AntlrTokenType = StubAntlrToken<std::string>;

		CmdCalculator::ESignOperatorAntlrContextKind signOperatorAntlrContextKind;
		AntlrTokenType token;


		CmdCalculator::ESignOperatorAntlrContextKind getSignOperatorAntlrContextKind() const
		{
			return signOperatorAntlrContextKind;
		}


		AntlrTokenType getToken() const
		{
			return token;
		}
	};
}