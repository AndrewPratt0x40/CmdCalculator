#pragma once

#include <concepts>
#include <memory>
#include <optional>
#include <functional>

#include "../CmdCalculator/DynamicExpression.h"
#include "../CmdCalculator/DynamicExpressionBox.h"
#include "../CmdCalculator/Expression.h"

namespace CmdCalculatorTestDoubles::Expressions
{
	template<CmdCalculator::Arithmetic::RealNumber NumberT>
	struct StubDynamicExpression :
		public CmdCalculator::Expressions::DynamicExpression<NumberT>,
		public CmdCalculator::Expressions::Expression_IntendedSatisfaction
	{
		using NumberType = CmdCalculator::Expressions::DynamicExpression<NumberT>::NumberType;
		//using FullSimplificationFuncType = std::function<CmdCalculator::Expressions::DynamicExpressionBox<NumberType>()>;


		NumberType evaluation;
		//bool isSimplifiableValue;
		//std::optional<FullSimplificationFuncType> fullSimplification;


		StubDynamicExpression(NumberType evaluation) :
			evaluation{ evaluation }
		{}
		
		
		virtual ~StubDynamicExpression() = default;


		/*bool isSimplifiable() const override
		{
			return isSimplifiableValue;
		}*/


		NumberType getEvaluation() const override
		{
			return evaluation;
		}


		/*CmdCalculator::Expressions::DynamicExpressionBox<NumberType> getFullSimplification() const override
		{
			return fullSimplification.has_value()
				? fullSimplification.value()()
				: CmdCalculator::Expressions::DynamicExpressionBox<NumberType>
				{
					std::make_unique<StubDynamicExpression<NumberType>>(*this)
				}
			;
		}*/
	};
}