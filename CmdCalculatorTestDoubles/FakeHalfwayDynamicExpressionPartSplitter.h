#pragma once

#include <concepts>
#include <memory>
#include <optional>

#include "../CmdCalculator/DynamicExpressionPartSplitter.h"
#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/NotImplementedException.h"
#include "StubDynamicExpressionPartSplitResult.h"


namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::String MathAstStringT>
	struct FakeHalfwayDynamicExpressionPartSplitter :
		public CmdCalculator::DynamicExpressionPartSplitter_IntendedSatisfaction
	{
		using MathAstStringType = MathAstStringT;
		using DynamicExpressionPartType = CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringType>;


		bool canSplit(CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts)
		{
			throw CmdCalculator::NotImplementedException{};
		}
		
		
		std::optional<StubDynamicExpressionPartSplitResult<MathAstStringType>>
			tryToSplit(CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts) const
		{
			throw CmdCalculator::NotImplementedException{};
		}
	};
}