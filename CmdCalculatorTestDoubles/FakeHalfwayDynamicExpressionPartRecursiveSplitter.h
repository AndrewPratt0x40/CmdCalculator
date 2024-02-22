#pragma once
#pragma once

#include <concepts>
#include <memory>
#include <optional>

#include "../CmdCalculator/DynamicExpressionPartRecursiveSplitter.h"
#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/NotImplementedException.h"
#include "StubDynamicExpressionPartRecursiveSplitResult.h"


namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::String MathAstStringT>
	struct FakeHalfwayDynamicExpressionPartRecursiveSplitter :
		public CmdCalculator::DynamicExpressionPartRecursiveSplitter_IntendedSatisfaction
	{
		using MathAstStringType = MathAstStringT;
		using DynamicExpressionPartType = CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringType>;


		std::optional<StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType>>
			tryToSplit(CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts) const
		{
			throw CmdCalculator::NotImplementedException{};
		}
	};
}