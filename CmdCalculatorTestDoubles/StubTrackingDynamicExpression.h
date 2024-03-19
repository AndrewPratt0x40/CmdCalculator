#pragma once

#include <concepts>
#include <memory>
#include <optional>
#include <functional>

#include "../CmdCalculator/DynamicExpression.h"
#include "../CmdCalculator/DynamicMathAstNode.h"
#include "../CmdCalculator/Expression.h"

namespace CmdCalculatorTestDoubles::Expressions
{
	template
	<
		CmdCalculator::Arithmetic::RealNumber NumberT,
		class SourceT
	>
	struct StubTrackingDynamicExpression :
		public CmdCalculator::Expressions::DynamicExpression<NumberT>,
		public CmdCalculator::Expressions::Expression_IntendedSatisfaction
	{
		using NumberType = CmdCalculator::Expressions::DynamicExpression<NumberT>::NumberType;
		using SourceType = SourceT;
		//using FullSimplificationFuncType = std::function<CmdCalculator::Expressions::DynamicExpressionBox<NumberType>()>;


		SourceType source;
		NumberType evaluation;
		//bool isSimplifiableValue;
		//std::optional<FullSimplificationFuncType> fullSimplification;


		StubTrackingDynamicExpression(SourceType source, NumberType evaluation) :
			source{ source },
			evaluation{ evaluation }
		{}
		
		
		virtual ~StubTrackingDynamicExpression() = default;


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