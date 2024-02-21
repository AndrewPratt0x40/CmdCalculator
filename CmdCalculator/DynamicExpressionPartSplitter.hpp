#pragma once

#include "DynamicExpressionPartSplitter.h"
#include "NotImplementedException.h"


template<class SplitterT, std::ranges::forward_range PartsInputRangeT>
	requires CmdCalculator::DynamicExpressionPartSplitter<SplitterT, PartsInputRangeT>
std::ranges::forward_range auto CmdCalculator::recursivelySplitExpressionParts(const SplitterT& splitter, PartsInputRangeT parts)
{
	throw NotImplementedException{};
}