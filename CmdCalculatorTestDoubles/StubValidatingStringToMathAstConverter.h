#pragma once

#include "../CmdCalculator/StringToMathAstConverter.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/MathAstNode.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::StringView StringViewT, CmdCalculator::MathAst::MathAstNode MathAstNodeT, class ExceptionT>
	struct StubValidatingStringToMathAstConverter :
		public CmdCalculator::StringToMathAstConverter_IntendedSatisfaction
	{
		using StringViewType = StringViewT;
		using MathAstNodeType = MathAstNodeT;
		using ExceptionType = ExceptionT;

		ExceptionT exceptionToThrow;
		MathAstNodeT convertedString;
		StringViewT validSource;

		MathAstNodeT getStringAsMathAst(StringViewT source) const
		{
			if (source != validSource)
				throw exceptionToThrow;

			return convertedString;
		}
	};
}