#pragma once

#include <optional>

#include "../CmdCalculator/FullExpressionAntlrContext.h"
#include "../CmdCalculator/ExpressionAntlrContext.h"
#include "../CmdCalculator/AntlrToken.h"
#include "../CmdCalculator/strings.h"
#include "StubExpressionAntlrContext.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::StringView SourceStringViewT>
	struct StubTrackingFullExpressionAntlrContext :
		public CmdCalculator::FullExpressionAntlrContext_IntendedSatisfaction
	{
		using SourceStringViewType = SourceStringViewT;
		using AntlrTokenType = StubAntlrToken<std::string>;
		using ExpressionAntlrContextType = StubExpressionAntlrContext;

		SourceStringViewType stringSource;
		
		std::optional<AntlrTokenType> leadingTrivia;
		ExpressionAntlrContextType expressionValue;
		std::optional<AntlrTokenType> trailingTrivia;


		std::optional<AntlrTokenType> getLeadingTrivia() const
		{
			return leadingTrivia;
		}


		ExpressionAntlrContextType getexpressionValue() const
		{
			return expressionValue;
		}


		std::optional<AntlrTokenType> getTrailingTrivia() const
		{
			return trailingTrivia;
		}
	};
}