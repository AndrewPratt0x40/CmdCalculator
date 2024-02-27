#pragma once
#pragma once

#include <concepts>
#include <ranges>
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
		
		const ::CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringType>& getPart
		(
			::CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts,
			const std::integral auto index
		) const
		{
			/*auto fooBegin{std::ranges::begin(parts)};
			auto fooBeginElem{ *std::ranges::begin(parts) };
			auto fooBeginElemX{ (*std::ranges::begin(parts)).getStringRepresentation() };

			auto fooNext{ std::ranges::next(std::ranges::begin(parts), 0) };
			auto fooNextElem{ *std::ranges::next(std::ranges::begin(parts), 0) };
			auto fooNextElemX{ (*std::ranges::next(std::ranges::begin(parts), 0)).getStringRepresentation() };*/

			return *std::ranges::next(std::ranges::begin(parts), index);
		}


		template<std::input_or_output_iterator PartsIterT>
		StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType> split
		(
			const std::integral auto partsSize,
			const std::ranges::subrange<PartsIterT> parts
		) const;


	public:

		std::optional<StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType>>
			tryToSplit(::CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts) const
		{
			const std::integral auto partsSize{ std::ranges::ssize(parts) };
			if (partsSize % 2 == 0)
				return {};

			return split<std::ranges::iterator_t<decltype(parts)>>(partsSize, parts);
		}
	};



	template<::CmdCalculator::String MathAstStringT>
	template<std::input_or_output_iterator PartsIterT>
	inline StubDynamicExpressionPartRecursiveSplitResult<MathAstStringT>
		FakeHalfwayDynamicExpressionPartRecursiveSplitter<MathAstStringT>::split
	(
		const std::integral auto partsSize,
		const std::ranges::subrange<PartsIterT> parts
	) const
	{
		assert(partsSize % 2 != 0);
		assert(partsSize == std::ranges::ssize(parts));

		if (partsSize == 1)
		{
			return StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType>
			{
				.leftPart{},
				.splitPart{ std::ref<const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringType>>(getPart(parts, 0)) },
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
						std::ranges::subrange<PartsIterT>{ parts | std::views::take(splitIndex) }
					)
				)
			},
			.splitPart{ std::ref<const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringType>>(getPart(parts, splitIndex)) },
			.rightPart
			{
				std::make_unique<StubDynamicExpressionPartRecursiveSplitResult<MathAstStringType>>
				(
					split
					(
						partsSize - splitIndex - 1,
						std::ranges::subrange<PartsIterT>{ parts | std::views::drop(splitIndex + 1) }
					)
				)
			}
		};
	}
}