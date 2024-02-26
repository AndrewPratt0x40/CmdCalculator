#pragma once

#include <optional>

#include "../CmdCalculator/WholefulNumberLiteralAntlrContext.h"
#include "StubAntlrToken.h"

namespace CmdCalculatorTestDoubles
{
	struct StubWholefulNumberLiteralAntlrContext :
		public ::CmdCalculator::WholefulNumberLiteralAntlrContext_IntendedSatisfaction
	{
		using AntlrTokenType = StubAntlrToken<std::string>;

		AntlrTokenType wholePart;
		std::optional<AntlrTokenType> decimalPoint;
		std::optional<AntlrTokenType> fractionalPart;


		AntlrTokenType getWholePart() const
		{
			return wholePart;
		}


		std::optional<AntlrTokenType> getDecimalPoint() const
		{
			return decimalPoint;
		}


		std::optional<AntlrTokenType> getFractionalPart() const
		{
			return fractionalPart;
		}
	};
}