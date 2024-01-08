#pragma once

#include <concepts>

#include "../CmdCalculator/AntlrFullExpressionContextOwner.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::StringView SourceStringViewT>
	struct StubTrackingAntlrFullExpressionContextOwner :
		public CmdCalculator::AntlrFullExpressionContextOwner_IntendedSatisfaction
	{
		using SourceStringViewType = SourceStringViewT;

		SourceStringViewT stringSource;

		CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext value;


		const CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext& getContext() const
		{
			return value;
		}
	};
}