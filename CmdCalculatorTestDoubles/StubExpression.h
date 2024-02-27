#pragma once

#include <concepts>
#include <memory>

#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/RealNumber.h"

namespace CmdCalculatorTestDoubles::Expressions
{
	template<CmdCalculator::Arithmetic::RealNumber NumberT>
	struct StubExpression :
		public CmdCalculator::Expressions::Expression_IntendedSatisfaction
	{
		using NumberType = NumberT;


		NumberType evaluation;
		//bool isSimplifiableValue;
		//std::shared_ptr<StubExpression> fullSimplification;


		NumberType getEvaluation() const
		{
			return evaluation;
		}


		/*bool isSimplifiable() const
		{
			return isSimplifiableValue;
		}*/


		/*StubExpression getFullSimplification() const
		{
			return fullSimplification ? *fullSimplification : *this;
		}*/
	};
}