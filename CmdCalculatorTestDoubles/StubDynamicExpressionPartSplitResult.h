#pragma once

#include <functional>
#include <concepts>
#include <memory>
#include <optional>
#include <vector>

#include "../CmdCalculator/DynamicExpressionPartSplitResult.h"
#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/strings.h"


namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::String MathAstStringT>
	struct StubDynamicExpressionPartSplitResult :
		public CmdCalculator::DynamicExpressionPartSplitResult_IntendedSatisfaction
	{
		using MathAstStringType = MathAstStringT;
		using DynamicExpressionPartType = CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringType>;


		std::vector<std::reference_wrapper<DynamicExpressionPartType>> leftParts;
		DynamicExpressionPartType& splitPart;
		std::vector<std::reference_wrapper<DynamicExpressionPartType>> rightParts;


		StubDynamicExpressionPartSplitResult
		(
			CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto leftPartRefs,
			DynamicExpressionPartType& splitPart,
			CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto rightPartRefs
		) :
			splitPart{ splitPart }
		{
			std::ranges::input_range auto leftPartsView
			{
				leftPartRefs
				| std::views::transform
				(
					[](DynamicExpressionPartType& leftPart)
					{ return std::ref(leftPart); }
				)
			};

			leftPartRefs = { std::ranges::begin(leftPartsView), std::ranges::end(leftPartsView) };


			std::ranges::input_range auto rightPartsView
			{
				rightPartRefs
				| std::views::transform
				(
					[](DynamicExpressionPartType& rightPart)
					{ return std::ref(rightPart); }
				)
			};

			rightPartRefs = { std::ranges::begin(rightPartRefs), std::ranges::end(rightPartRefs) };
		}


		CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto getLeftParts() const
		{
			return leftParts | std::views::all;
		}


		DynamicExpressionPartType& getSplitPart() const
		{
			return splitPart;
		}


		CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto getRightParts() const
		{
			return rightParts | std::views::all;
		}
	};
}