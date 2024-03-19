#pragma once

#include<concepts>
#include<ranges>
#include<algorithm>
#include<iterator>
#include<functional>

#include "BasicDEPSingleSplitter.h"
#include "std_polyfills.h"
#include "EBinaryOperator.h"
#include "dynamic_mathast.h"
#include "NotImplementedException.h"


static constexpr uint8_t getPrecedenceLevel(const CmdCalculator::MathAst::EBinaryOperator binaryOperator)
{
	switch (binaryOperator)
	{
	case CmdCalculator::MathAst::EBinaryOperator::Addition:
		[[fallthrough]];
	case CmdCalculator::MathAst::EBinaryOperator::Subtraction:
		return 0;
	case CmdCalculator::MathAst::EBinaryOperator::Multiplication:
		[[fallthrough]];
	case CmdCalculator::MathAst::EBinaryOperator::Division:
		return 1;
	case CmdCalculator::MathAst::EBinaryOperator::Exponentiation:
		[[fallthrough]];
	case CmdCalculator::MathAst::EBinaryOperator::NthRoot:
		return 2;
	case CmdCalculator::MathAst::EBinaryOperator::Modulo:
		return 3;
	default:
		CmdCalculator::Polyfills::unreachable();
	}
}


template<CmdCalculator::String MathAstStringT>
static inline bool canSplitWithGivenSize
(
	CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringT> auto parts,
	const std::integral auto partsSize
)
{
	assert(partsSize == std::ranges::size(parts));

	return
		partsSize % 2 != 0
		&& std::ranges::all_of
		(
			std::views::iota(decltype(partsSize){ 0 }, partsSize),
			[&parts](const std::integral auto i)
			{
				return
					(i % 2 != 0)
					== static_cast<const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>&>
						(*(std::ranges::begin(parts) + i))
						.isBinaryOperator()
				;
			}
		)
	;
}


template<CmdCalculator::String MathAstStringT>
static inline std::optional<CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>> tryToSplitSinglePart
(
	const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>& part
)
{
	return part.isBinaryOperator()
		? std::optional<CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>>{}
		: std::make_optional<CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>>
		(
			std::views::empty<std::reference_wrapper<const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>>>,
			part,
			std::views::empty<std::reference_wrapper<const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>>>
		)
	;
}


template<CmdCalculator::String MathAstStringT>
static inline std::optional<CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>> tryToSplitSeveralParts
(
	CmdCalculator::MathAst::DynamicExpressionPartNodeRange<MathAstStringT> auto parts,
	const std::integral auto partsSize
)
{
	assert(partsSize == std::ranges::size(parts));
	assert(canSplitWithGivenSize<MathAstStringT>(parts, partsSize));

	std::ranges::forward_range auto possibleSplitPartsIndexes
	{
		// The index of every part...
		std::views::iota(decltype(partsSize){0}, partsSize)
		// ...filtered to only odd indexes...
		| std::views::filter
		(
			[](const std::integral auto index)
			{ return index % 2 != 0; }
		)
		// ...in reverse order, so that if several operators have the
		// same max precedence level std::ranges::min_element selects
		// the last one instead of the first.
		| std::views::reverse
	};
	
	const std::input_iterator auto splitPartIndexIter
	{
		std::ranges::min_element
		(
			possibleSplitPartsIndexes,
			std::ranges::less(),
			[&parts](const std::integral auto possibleSplitPartsIndex)
			{
				return getPrecedenceLevel
				(
					reinterpret_cast<const CmdCalculator::MathAst::DynamicBinaryOperatorNode<MathAstStringT>&>
					(
						static_cast<const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>&>
						(*(std::ranges::begin(parts) + possibleSplitPartsIndex))
					)
					.getOperatorKind()
				);
			}
		)
	};
	const int64_t DELETE_ME_splitPartIndexIter{ *splitPartIndexIter };

	if (splitPartIndexIter == std::ranges::end(possibleSplitPartsIndexes))
		return {};

	return std::make_optional<CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>>
	(
		parts | std::views::take(*splitPartIndexIter),
		*(std::ranges::begin(parts) + *splitPartIndexIter),
		parts | std::views::drop(*splitPartIndexIter + 1)
	);
}


template<CmdCalculator::String MathAstStringT>
inline bool CmdCalculator::BasicDEPSingleSplitter<MathAstStringT>::canSplit
(
	MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts
) const
{
	return canSplitWithGivenSize<MathAstStringT>(parts, std::ranges::size(parts));
}


template<CmdCalculator::String MathAstStringT>
inline std::optional<CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>>
	CmdCalculator::BasicDEPSingleSplitter<MathAstStringT>::tryToSplit
(
	MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts
) const
{
	const std::integral auto partsSize{ std::ranges::ssize(parts) };

	if (!canSplitWithGivenSize<MathAstStringT>(parts, partsSize))
		return {};

	if (partsSize == 1)
		return tryToSplitSinglePart<MathAstStringT>(*std::ranges::begin(parts));

	assert(partsSize > 1 && (partsSize % 2 != 0));

	return tryToSplitSeveralParts<MathAstStringT>(parts, partsSize);
}