#pragma once

#include <concepts>
#include <memory>

#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<CmdCalculator::String StringT, CmdCalculator::StringView SourceStringViewT>
	struct StubTrackingMathAstNode :
		public CmdCalculator::MathAst::MathAstNode_IntendedSatisfaction
	{
		using StringType = StringT;

		SourceStringViewT stringSource;

		StringT leadingTrivia;
		StringT trailingTrivia;
		StringT stringRepresentation;


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