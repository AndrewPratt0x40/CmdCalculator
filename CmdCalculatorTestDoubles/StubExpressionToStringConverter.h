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
		StringT stringifiedExpression;

		StringT stringifyExpression() const
		{
			return stringifiedExpression;
		}
	};
}