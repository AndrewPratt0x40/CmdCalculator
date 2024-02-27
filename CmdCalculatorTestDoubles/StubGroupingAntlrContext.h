#pragma once

#include <optional>
#include <memory>
#include <assert.h>

#include "../CmdCalculator/GroupingAntlrContext.h"
#include "StubAntlrToken.h"

namespace CmdCalculatorTestDoubles
{
	struct StubExpressionAntlrContext;


	struct StubGroupingAntlrContext :
		public CmdCalculator::GroupingAntlrContext_IntendedSatisfaction
	{
		using AntlrTokenType = StubAntlrToken<std::string>;
		using ExpressionAntlrContextType = StubExpressionAntlrContext;

		std::optional<AntlrTokenType> innerLeadingTrivia;
		std::shared_ptr<ExpressionAntlrContextType> innerExpression;
		std::optional<AntlrTokenType> innerTrailingTrivia;


		std::optional<AntlrTokenType> getInnerLeadingTrivia() const
		{
			return innerLeadingTrivia;
		}


		ExpressionAntlrContextType& getInnerExpression() const
		{
			assert(innerExpression);
			return *innerExpression;
		}


		std::optional<AntlrTokenType> getInnerTrailingTrivia() const
		{
			return innerTrailingTrivia;
		}
	};
}