#pragma once

#include <span>
#include <memory>

#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<CmdCalculator::String StringT>
	class StubDynamicOperandNode :
		public CmdCalculator::MathAst::DynamicOperandNode<StringT>,
		public CmdCalculator::MathAst::ExpressionNode_IntendedSatisfaction,
		public CmdCalculator::MathAst::MathAstNode_IntendedSatisfaction
	{
	public:
		using StringType = StringT;


		StringType leadingTrivia;
		StringType trailingTrivia;
		StringType stringRepresentation;

		
		StubDynamicOperandNode
		(
			const StringType leadingTrivia,
			const StringType trailingTrivia,
			const StringType stringRepresentation
		) :
			leadingTrivia{ leadingTrivia },
			trailingTrivia{ trailingTrivia },
			stringRepresentation{ stringRepresentation }
		{}


		StringType getLeadingTrivia() const override
		{
			return leadingTrivia;
		}


		StringType getTrailingTrivia() const override
		{
			return trailingTrivia;
		}


		StringT getStringRepresentation() const override
		{
			return stringRepresentation;
		}
	};
}