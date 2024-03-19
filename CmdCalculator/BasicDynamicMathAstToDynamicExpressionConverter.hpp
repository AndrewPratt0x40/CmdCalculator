#pragma once

#include <assert.h>

#include "BasicDynamicMathAstToDynamicExpressionConverter.h"
#include "NotImplementedException.h"



template
<
	CmdCalculator::DynamicExpressionPartRecursiveSplitter DynamicExpressionPartRecursiveSplitterT,
	CmdCalculator::RecursiveSplitResultToDynamicExpressionConverter RecursiveSplitResultToDynamicExpressionConverterT
>
	requires CmdCalculator::CompatibleSplitterAndResultToExpressionConverter
	<
		DynamicExpressionPartRecursiveSplitterT,
		RecursiveSplitResultToDynamicExpressionConverterT
	>
inline CmdCalculator::BasicDynamicMathAstToDynamicExpressionConverter
<
	DynamicExpressionPartRecursiveSplitterT, RecursiveSplitResultToDynamicExpressionConverterT>
	::BasicDynamicMathAstToDynamicExpressionConverter
(
	DynamicExpressionPartRecursiveSplitterType&& splitter,
	RecursiveSplitResultToDynamicExpressionConverterType&& splitResultConverter
) :
	m_splitter{ splitter },
	m_splitResultConverter{ splitResultConverter }
{}


template
<
	CmdCalculator::DynamicExpressionPartRecursiveSplitter DynamicExpressionPartRecursiveSplitterT,
	CmdCalculator::RecursiveSplitResultToDynamicExpressionConverter RecursiveSplitResultToDynamicExpressionConverterT
>
	requires CmdCalculator::CompatibleSplitterAndResultToExpressionConverter
	<
		DynamicExpressionPartRecursiveSplitterT,
		RecursiveSplitResultToDynamicExpressionConverterT
	>
inline typename CmdCalculator::BasicDynamicMathAstToDynamicExpressionConverter
<
	DynamicExpressionPartRecursiveSplitterT,
	RecursiveSplitResultToDynamicExpressionConverterT
>::OutputExpressionType
	CmdCalculator::BasicDynamicMathAstToDynamicExpressionConverter
	<
		DynamicExpressionPartRecursiveSplitterT,
		RecursiveSplitResultToDynamicExpressionConverterT
	>::getMathAstAsExpression
(
	const RootMathAstNodeType& sourceRootNode
) const
{
	const Optional auto splitResult{ m_splitter.tryToSplit(sourceRootNode.getParts()) };
	assert(splitResult.has_value());

	UniquePtr auto convertedSplitResult
	{
		std::move(m_splitResultConverter.getSplitResultAsExpression(splitResult.value()))
	};
	assert(convertedSplitResult);

	return Expressions::DynamicExpressionBox<OutputExpressionInnerType>
	{
		std::move(convertedSplitResult)
	};
}