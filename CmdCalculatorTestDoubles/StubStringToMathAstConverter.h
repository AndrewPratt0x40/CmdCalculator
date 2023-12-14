#pragma once

#include "../CmdCalculator/MathAstToExpressionConverter.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/MathAstNode.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::StringView StringViewT, CmdCalculator::MathAst::MathAstNode MathAstNodeT>
	struct StubStringToMathAstConverter :
		public CmdCalculator::MathAstToExpressionConverter_IntendedSatisfaction
	{
		MathAstNodeT convertedString;

		MathAstNodeT getStringAsMathAst() const
		{
			return convertedString;
		}
	};
}