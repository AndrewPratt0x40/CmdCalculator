#pragma once

#include <concepts>
#include <memory>

#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<CmdCalculator::String StringT>
	struct StubMathAstNode :
		public CmdCalculator::MathAst::MathAstNode_IntendedSatisfaction
	{
		using StringType = StringT;

		StringT leadingTrivia;
		StringT trailingTrivia;
		StringT stringRepresentation;


		StringT getLeadingTrivia() const
		{
			return leadingTrivia;
		}


		StringT getTrailingTrivia() const
		{
			return leadingTrivia;
		}


		StringT getStringRepresentation() const
		{
			return leadingTrivia;
		}
	};
}