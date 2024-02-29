#pragma once

#include "BasicDEPRecursiveSplitResult.h"
#include "NotImplementedException.h"


template<CmdCalculator::String MathAstStringT>
inline CmdCalculator::BasicDEPRecursiveSplitResult<MathAstStringT>::BasicDEPRecursiveSplitResult
(
	std::unique_ptr<BasicDEPRecursiveSplitResult> leftPart,
	const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>& splitPart,
	std::unique_ptr<BasicDEPRecursiveSplitResult> rightPart
) :
	m_leftPart{ std::move(leftPart) },
	m_splitPart{ std::ref(splitPart) },
	m_rightPart{ std::move(rightPart) }
{}


template<CmdCalculator::String MathAstStringT>
inline const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>&
	CmdCalculator::BasicDEPRecursiveSplitResult<MathAstStringT>::getSplitPart() const
{
	return m_splitPart.get();
}


template<CmdCalculator::String MathAstStringT>
inline const CmdCalculator::BasicDEPRecursiveSplitResult<MathAstStringT>*
	CmdCalculator::BasicDEPRecursiveSplitResult<MathAstStringT>::getLeftPart() const
{
	return m_leftPart.get();
}


template<CmdCalculator::String MathAstStringT>
inline const CmdCalculator::BasicDEPRecursiveSplitResult<MathAstStringT>*
	CmdCalculator::BasicDEPRecursiveSplitResult<MathAstStringT>::getRightPart() const
{
	return m_rightPart.get();
}