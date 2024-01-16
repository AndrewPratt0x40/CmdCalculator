#pragma once

#include <span>
#include <memory>

#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<CmdCalculator::String StringT>
	class StubDynamicGroupingNode :
		public CmdCalculator::MathAst::DynamicGroupingNode<StringT>,
		public CmdCalculator::MathAst::ExpressionNode_IntendedSatisfaction,
		public CmdCalculator::MathAst::MathAstNode_IntendedSatisfaction
	{
	public:
		using StringType = StringT;


		CmdCalculator::MathAst::DynamicExpressionNode<StringType>* containedExpression;
		StringType leadingTrivia;
		StringType trailingTrivia;
		StringType stringRepresentation;

		
		StubDynamicGroupingNode
		(
			CmdCalculator::MathAst::DynamicExpressionNode<StringType>* containedExpression,
			const StringType leadingTrivia,
			const StringType trailingTrivia,
			const StringType stringRepresentation
		) :
			containedExpression{ containedExpression },
			leadingTrivia{ leadingTrivia },
			trailingTrivia{ trailingTrivia },
			stringRepresentation{ stringRepresentation }
		{}


		StringType getStringRepresentation() const override
		{
			return stringRepresentation;
		}
	};
}