#pragma once

#include "../CmdCalculator/ExpressionToStringConverter.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::Expressions::Expression ExpressionT, CmdCalculator::String StringT>
	struct StubExpressionToStringConverter :
		public CmdCalculator::ExpressionToStringConverter_IntendedSatisfaction
	{
		using StringType = StringT;

		StringT stringifiedExpression;

		StringT stringifyExpression(const ExpressionT& source) const
		{
			return stringifiedExpression;
		}
	};
}