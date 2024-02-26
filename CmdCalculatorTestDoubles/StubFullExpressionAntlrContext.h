#pragma once

#include <optional>

#include "../CmdCalculator/FullExpressionAntlrContext.h"
#include "../CmdCalculator/ExpressionAntlrContext.h"
#include "../CmdCalculator/AntlrToken.h"
#include "../CmdCalculator/strings.h"
#include "StubExpressionAntlrContext.h"

namespace CmdCalculatorTestDoubles
{
	template
	<
		::CmdCalculator::AntlrToken AntlrTokenT = StubAntlrToken<std::string>,
		::CmdCalculator::ExpressionAntlrContext ExpressionAntlrContextT = StubExpressionAntlrContext
	>
	struct StubFullExpressionAntlrContext :
		public ::CmdCalculator::FullExpressionAntlrContext_IntendedSatisfaction
	{
		using AntlrTokenType = AntlrTokenT;
		using ExpressionAntlrContextType = ExpressionAntlrContextT;

		
		std::optional<AntlrTokenType> leadingTrivia;
		ExpressionAntlrContextType expressionValue;
		std::optional<AntlrTokenType> trailingTrivia;


		std::optional<AntlrTokenType> getLeadingTrivia() const
		{
			return leadingTrivia;
		}


		ExpressionAntlrContextType getExpressionValue() const
		{
			return expressionValue;
		}


		std::optional<AntlrTokenType> getTrailingTrivia() const
		{
			return trailingTrivia;
		}
	};
}