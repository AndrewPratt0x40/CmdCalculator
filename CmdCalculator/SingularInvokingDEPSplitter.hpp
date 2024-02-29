#pragma once

#include "SingularInvokingDEPSplitter.h"
#include "NotImplementedException.h"


template<CmdCalculator::DynamicExpressionPartSingleSplitter SingularSplitterT>
inline CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::SingularInvokingDEPSplitter
(
	SingularSplitterT&& singularSplitter
)
{
	throw NotImplementedException{};
}


template<CmdCalculator::DynamicExpressionPartSingleSplitter SingularSplitterT>
inline std::optional<CmdCalculator::BasicDEPRecursiveSplitResult
<
	typename CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::MathAstStringType>
>
	CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::tryToSplit
(
	MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts
)
{
	throw NotImplementedException{};
}