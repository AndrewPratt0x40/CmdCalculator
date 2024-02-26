#pragma once

#include <memory>

#include "../CmdCalculator/StringToMathAstConverter.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/MathAstNode.h"

namespace CmdCalculatorTestDoubles
{
	template<::CmdCalculator::StringView StringViewT, ::CmdCalculator::MathAst::MathAstNode MathAstNodeT>
	struct StubStringToMathAstConverter :
		public ::CmdCalculator::StringToMathAstConverter_IntendedSatisfaction
	{
		using StringViewType = StringViewT;
		using MathAstNodeType = MathAstNodeT;

		MathAstNodeT convertedString;

		std::unique_ptr<MathAstNodeT> getStringAsMathAst(StringViewT source) const
		{
			return std::make_unique<MathAstNodeT>(convertedString);
		}
	};
}