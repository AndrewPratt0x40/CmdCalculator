#pragma once

#include <optional>

#include "../CmdCalculator/NumberLiteralAntlrContext.h"
#include "StubWholefulNumberLiteralAntlrContext.h"
#include "StubWholelessNumberLiteralAntlrContext.h"

namespace CmdCalculatorTestDoubles
{
	struct StubNumberLiteralAntlrContext :
		public ::CmdCalculator::NumberLiteralAntlrContext_IntendedSatisfaction
	{
		using WholefulNumberLiteralAntlrContextType = StubWholefulNumberLiteralAntlrContext;
		using WholelessNumberLiteralAntlrContextType = StubWholelessNumberLiteralAntlrContext;

		::CmdCalculator::ENumberLiteralAntlrContextKind numberLiteralAntlrContextKind;
		std::optional<WholefulNumberLiteralAntlrContextType> wholefulNumberLiteral;
		std::optional<WholelessNumberLiteralAntlrContextType> wholelessNumberLiteral;


		::CmdCalculator::ENumberLiteralAntlrContextKind getNumberLiteralAntlrContextKind() const
		{
			return numberLiteralAntlrContextKind;
		}


		std::optional<WholefulNumberLiteralAntlrContextType> getWholefulNumberLiteral() const
		{
			return wholefulNumberLiteral;
		}



		std::optional<WholelessNumberLiteralAntlrContextType> getWholelessNumberLiteral() const
		{
			return wholelessNumberLiteral;
		}
	};
}