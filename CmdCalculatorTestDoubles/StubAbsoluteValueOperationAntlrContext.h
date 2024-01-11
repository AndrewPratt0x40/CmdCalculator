#pragma once

#include <optional>

#include "../CmdCalculator/AbsoluteValueOperationAntlrContext.h"
#include "StubAntlrToken.h"

namespace CmdCalculatorTestDoubles
{
	struct StubExpressionAntlrContext;


	struct StubAbsoluteValueOperationAntlrContext :
		public CmdCalculator::AbsoluteValueOperationAntlrContext_IntendedSatisfaction
	{
		using AntlrTokenType = StubAntlrToken<std::string>;
		using ExpressionAntlrContextType = StubExpressionAntlrContext;

		std::optional<AntlrTokenType> innerLeadingTrivia;
		ExpressionAntlrContextType innerExpression;
		std::optional<AntlrTokenType> innerTrailingTrivia;


		std::optional<AntlrTokenType> getInnerLeadingTrivia() const
		{
			return innerLeadingTrivia;
		}


		ExpressionAntlrContextType getInnerExpression() const
		{
			return innerExpression;
		}


		std::optional<AntlrTokenType> getInnerTrailingTrivia() const
		{
			return innerTrailingTrivia;
		}
	};
}