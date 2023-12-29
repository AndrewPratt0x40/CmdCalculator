#pragma once

#include "../CmdCalculator/StringToMathAstConverter.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculatorTestDoubles/StubTrackingMathAstNode.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::StringView StringViewT, CmdCalculator::String MathAstNodeStringT>
	class StubTrackingStringToMathAstConverter :
		public CmdCalculator::StringToMathAstConverter_IntendedSatisfaction
	{
	public:
		using StringViewType = StringViewT;
		using MathAstNodeType = MathAst::StubTrackingMathAstNode<MathAstNodeStringT, StringViewT>;

		MathAstNodeStringT convertedValueLeadingTrivia;
		MathAstNodeStringT convertedValueTrailingTrivia;
		MathAstNodeStringT convertedValueStringRepresentation;


		MathAstNodeType getStringAsMathAst(StringViewT source) const
		{
			return MathAstNodeType
			{
				.stringSource{ source },
				.leadingTrivia{ convertedValueLeadingTrivia },
				.trailingTrivia{ convertedValueTrailingTrivia },
				.stringRepresentation{ convertedValueStringRepresentation }
			};
		}
	};
}