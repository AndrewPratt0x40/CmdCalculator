#pragma once

#include <span>
#include <memory>

#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<CmdCalculator::String StringT>
	class StubDynamicExpressionPartNode :
		public CmdCalculator::MathAst::DynamicExpressionPartNode<StringT>,
		public CmdCalculator::MathAst::MathAstNode_IntendedSatisfaction
	{
	public:
		using StringType = StringT;

		StringT leadingTrivia;
		StringT trailingTrivia;
		StringT stringRepresentation;


		StubDynamicExpressionPartNode
		(
			const StringT leadingTrivia,
			const StringT trailingTrivia,
			const StringT stringRepresentation
		) :
			leadingTrivia{ leadingTrivia },
			trailingTrivia{ trailingTrivia },
			stringRepresentation{ stringRepresentation }
		{}


		StringT getLeadingTrivia() const
		{
			return leadingTrivia;
		}


		StringT getTrailingTrivia() const
		{
			return trailingTrivia;
		}


		StringT getStringRepresentation() const
		{
			return stringRepresentation;
		}
	};
}