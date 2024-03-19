#pragma once

#include <optional>

#include "../CmdCalculator/WholelessNumberLiteralAntlrContext.h"
#include "StubAntlrToken.h"

namespace CmdCalculatorTestDoubles
{
	struct StubWholelessNumberLiteralAntlrContext :
		public CmdCalculator::WholelessNumberLiteralAntlrContext_IntendedSatisfaction
	{
		using AntlrTokenType = StubAntlrToken<std::string>;

		AntlrTokenType decimalPoint;
		AntlrTokenType fractionalPart;


		AntlrTokenType getDecimalPoint() const
		{
			return decimalPoint;
		}


		AntlrTokenType getFractionalPart() const
		{
			return fractionalPart;
		}
	};
}