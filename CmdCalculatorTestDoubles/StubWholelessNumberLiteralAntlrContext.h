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

		std::optional<AntlrTokenType> wholePart;
		std::optional<AntlrTokenType> decimalPoint;
		AntlrTokenType fractionalPart;


		std::optional<AntlrTokenType> getWholePart() const
		{
			return wholePart;
		}


		std::optional<AntlrTokenType> getDecimalPoint() const
		{
			return decimalPoint;
		}


		AntlrTokenType getFractionalPart() const
		{
			return fractionalPart;
		}
	};
}