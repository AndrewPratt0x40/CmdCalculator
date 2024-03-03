#pragma once

#include <concepts>
#include <ranges>
#include <memory>
#include <functional>

#include "BasicDEPSingleSplitResult.h"
#include "NotImplementedException.h"


template<CmdCalculator::String MathAstStringT>
inline CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>::PartRefVectorType
	CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>::createPartRefVector
(
	MathAst::DynamicExpressionPartNodeRange<MathAstStringT> auto parts
)
{
	const std::ranges::range auto partRefsView
	{
		parts
		| std::views::transform
		(
			[](const MathAst::DynamicExpressionPartNode<MathAstStringT>& part)
			{ return std::ref(part); }
		)
	};

	return PartRefVectorType
	{
		std::ranges::begin(partRefsView),
		std::ranges::end(partRefsView)
	};
}


template<CmdCalculator::String MathAstStringT>
inline CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>::BasicDEPSingleSplitResult
(
	MathAst::DynamicExpressionPartNodeRange<MathAstStringT> auto leftParts,
	const MathAst::DynamicExpressionPartNode<MathAstStringT>& splitPart,
	MathAst::DynamicExpressionPartNodeRange<MathAstStringT> auto rightParts
) :
	m_leftParts{ createPartRefVector(leftParts) },
	m_splitPart{ std::ref(splitPart) },
	m_rightParts{ createPartRefVector(rightParts) }
{}


template<CmdCalculator::String MathAstStringT>
inline CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>::PartRefView
	CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>::getLeftParts() const
{
	return m_leftParts | std::views::all;
}


template<CmdCalculator::String MathAstStringT>
inline const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>&
	CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>::getSplitPart() const
{
	return m_splitPart.get();
}


template<CmdCalculator::String MathAstStringT>
inline CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>::PartRefView
	CmdCalculator::BasicDEPSingleSplitResult<MathAstStringT>::getRightParts() const
{
	return m_rightParts | std::views::all;
}