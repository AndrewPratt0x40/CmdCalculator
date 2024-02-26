#pragma once

#include <span>
#include <memory>

#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<::CmdCalculator::String StringT>
	class StubDynamicGroupingNode :
		public ::CmdCalculator::MathAst::DynamicGroupingNode<StringT>,
		public ::CmdCalculator::MathAst::MathAstNode_IntendedSatisfaction
	{
	public:
		using StringType = StringT;


		StringType stringRepresentation;

		
		StubDynamicGroupingNode
		(
			std::unique_ptr<::CmdCalculator::MathAst::DynamicExpressionNode<StringType>> containedExpression,
			const StringType leadingTrivia,
			const StringType trailingTrivia,
			const StringType stringRepresentation
		) :
			::CmdCalculator::MathAst::DynamicGroupingNode<StringType>(std::move(containedExpression), leadingTrivia, trailingTrivia),
			stringRepresentation{ stringRepresentation }
		{}


		StringType getStringRepresentation() const override
		{
			return stringRepresentation;
		}
	};
}