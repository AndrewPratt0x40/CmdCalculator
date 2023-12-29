#pragma once

#include "../CmdCalculator/ExpressionToStringConverter.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/strings.h"
#include "StubTrackingConvertedString.h"

namespace CmdCalculatorTestDoubles
{
	template
	<
		CmdCalculator::Expressions::Expression ExpressionT,
		CmdCalculator::String InnerStringT
	>
	struct StubTrackingExpressionToStringConverter :
		public CmdCalculator::ExpressionToStringConverter_IntendedSatisfaction
	{
		using ExpressionType = ExpressionT;
		using StringType = StubTrackingConvertedString
		<
			InnerStringT,
			ExpressionT
		>;

		InnerStringT stringifiedExpression;

		StringType stringifyExpression(const ExpressionT& source, const CmdCalculator::CalculationConfiguration configuration) const
		{
			return StringType
			{
				.value{ stringifiedExpression },
				.expressionSource{ source },
				.configurationUsed{ configuration }
			};
		}
	};
}