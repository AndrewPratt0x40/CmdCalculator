#pragma once

#include "../CmdCalculator/StringToMathAstConverter.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/MathAstNode.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::StringView StringViewT, CmdCalculator::MathAst::MathAstNode MathAstNodeT>
	struct StubStringToMathAstConverter :
		public CmdCalculator::StringToMathAstConverter_IntendedSatisfaction
	{
		MathAstNodeT convertedString;

		MathAstNodeT getStringAsMathAst(StringViewT source) const
		{
			return convertedString;
		}
	};
}