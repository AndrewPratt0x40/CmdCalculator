#pragma once

#include <concepts>
#include <optional>

#include "../CmdCalculator/NotImplementedException.h"
#include "../CmdCalculator/Expression.h"

namespace CmdCalculatorTestDoubles::Expressions
{
	using StubExpressionDefaultIdentifierType = int;
	static_assert(std::regular<StubExpressionDefaultIdentifierType>);


	template<std::regular IdentifierT = StubExpressionDefaultIdentifierType>
	struct StubExpression :
		public CmdCalculator::Expressions::Expression_IntendedSatisfaction
	{
		using IdentifierType = IdentifierT;

		IdentifierT identifier;
		std::optional<StubExpression<IdentifierT>> fullSimplification;

		bool isSimplifiable() const
		{
			return identifier;
		}


		StubExpression<IdentifierT> getFullSimplification() const
		{
			return fullSimplification.value_or(*this);
		}
	};
}