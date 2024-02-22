#pragma once

#include "DynamicExpressionPartSplitter.h"
#include "NotImplementedException.h"


template<class SplitterT, class PartsInputRangeT>
	requires CmdCalculator::DynamicExpressionPartSplitter<SplitterT, PartsInputRangeT>
CmdCalculator::DynamicExpressionPartRecursiveSplitResult auto CmdCalculator::recursivelySplitExpressionParts
	(const SplitterT& splitter, PartsInputRangeT parts)
{
	throw NotImplementedException{};
}