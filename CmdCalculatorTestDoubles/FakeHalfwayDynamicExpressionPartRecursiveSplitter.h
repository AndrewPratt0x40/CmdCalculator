#pragma once
#pragma once

#include <concepts>
#include <memory>
#include <optional>
#include <assert.h>

#include "../CmdCalculator/DynamicExpressionPartRecursiveSplitter.h"
#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/NotImplementedException.h"
#include "StubDynamicExpressionPartRecursiveSplitResult.h"


namespace CmdCalculatorTestDoubles
{
	template<::CmdCalculator::String MathAstStringT>
	class FakeHalfwayDynamicExpressionPartRecursiveSplitter :
		public ::CmdCalculator::DynamicExpressionPartRecursiveSplitter_IntendedSatisfaction
	{
	public:
		using MathAstStringType = MathAstStringT;
		using DynamicExpressionPartType = ::CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringType>;


	private:
		
		::CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringType>& getPart
		(
			::CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts,
			const std::integral auto index
		) const
		{
			return *(std::ranges::begin(parts) + index);
		}
		
		
		StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType> split
		(
			const std::integral auto partsSize,
			::CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts
		) const;


	public:

		std::optional<StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType>>
			tryToSplit(::CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts) const
		{
			const std::integral auto partsSize{ std::ranges::ssize(parts) };
			if (partsSize % 2 == 0)
				return {};

			return split(partsSize, parts);
		}
	};


	template<::CmdCalculator::String MathAstStringT>
	inline StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType> CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartRecursiveSplitter<MathAstStringT>::split(const std::integral auto partsSize, ::CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts) const
	{
		return StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType>();
	}


	template<::CmdCalculator::String MathAstStringT>
	inline StubDynamicExpressionPartRecursiveSplitResult<MathAstStringT>
		FakeHalfwayDynamicExpressionPartRecursiveSplitter<MathAstStringT>::split
	(
		const std::integral auto partsSize,
		::CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringT> auto parts
	) const
	{
		assert(partsSize % 2 != 0);
		assert(partsSize == std::ranges::ssize(parts));

		if (partsSize == 1)
		{
			return StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType>
			{
				.leftPart{},
				.splitPart{ std::ref(getPart(parts, 0)) },
				.rightPart{}
			};
		}

		const std::integral auto splitIndex
		{
			((partsSize / 2) % 2 == 0)
			? (partsSize / 2) - 1
			: partsSize / 2
		};

		return StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType>
		{
			.leftPart
			{
				std::make_unique<StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType>>
				(
					split
					(
						splitIndex,
						parts | std::views::take(splitIndex)
					)
				)
			},
			.splitPart{ std::ref(getPart(parts, splitIndex)) },
			.rightPart
			{
				std::make_unique<StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType>>
				(
					split
					(
						partsSize - splitIndex - 1,
						parts | std::views::drop(splitIndex + 1)
					)
				)
			}
		};
}