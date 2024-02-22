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


		bool canSplit(CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts) const
		{
			const std::integral auto partsSize{ std::ranges::size(parts) };
			return partsSize >= 3 && (partsSize % 2 != 0);
		}
		
		
		std::optional<StubDynamicExpressionPartSplitResult<MathAstStringType>>
			tryToSplit(CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts) const
		{
			if (!canSplit(parts))
				return {};

			const std::integral auto leftPartsSize{ std::ranges::size(parts) / 2 };

			const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto leftParts
			{
				parts
				| std::views::take(leftPartsSize)
				| std::views::transform
				(
					[](const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringType>& leftPart)
					{ return std::ref(leftPart); }
				)
			};

			const auto& splitPart
			{
				*(std::ranges::cbegin(parts) + leftPartsSize)
			};

			const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto rightParts
			{
				parts
				| std::views::drop(leftPartsSize + 1)
				| std::views::transform
				(
					[](const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringType>& rightPart)
					{ return std::ref(rightPart); }
				)
			};

			return StubDynamicExpressionPartSplitResult<MathAstStringType>
			{
				leftParts,
				splitPart,
				rightParts
			};
		}
	};
}