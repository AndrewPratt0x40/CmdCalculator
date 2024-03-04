#pragma once

#include "BasicDEPSingleSplitter.h"
#include "NotImplementedException.h"


template<CmdCalculator::String MathAstStringT>
inline bool CmdCalculator::BasicDEPSingleSplitter<MathAstStringT>::canSplit
(
	MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts
) const
{
	throw NotImplementedException{};
}


template<CmdCalculator::String MathAstStringT>
inline std::optional<CmdCalculator::BasicDEPSingleSplitResult<std::string>>
	CmdCalculator::BasicDEPSingleSplitter<MathAstStringT>::tryToSplit
(
	MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts
) const
{
	throw NotImplementedException{};
}