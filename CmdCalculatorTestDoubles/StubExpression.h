#pragma once

#include <concepts>
#include <memory>

#include "../CmdCalculator/Expression.h"

namespace CmdCalculatorTestDoubles::Expressions
{
	struct StubExpression :
		public CmdCalculator::Expressions::Expression_IntendedSatisfaction
	{
		bool isSimplifiableValue;
		std::shared_ptr<StubExpression> fullSimplification;


		bool isSimplifiable() const
		{
			return isSimplifiableValue;
		}


		StubExpression getFullSimplification() const
		{
			return fullSimplification ? *fullSimplification : StubExpression{};
		}
	};
}