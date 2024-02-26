#pragma once

#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/CalculationConfiguration.h"

namespace CmdCalculatorTestDoubles
{
	template
	<
		::CmdCalculator::String StringT,
		::CmdCalculator::Expressions::Expression SourceExpressionT
	>
	struct StubTrackingConvertedString
	{
		using value_type = StringT::value_type;
		using traits_type = StringT::traits_type;
		using allocator_type = StringT::allocator_type;


		StringT value;
		SourceExpressionT expressionSource;
		::CmdCalculator::CalculationConfiguration configurationUsed;

		
		operator StringT() const
		{
			return value;
		}
	};
}