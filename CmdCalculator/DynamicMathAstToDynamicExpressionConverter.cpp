#include "DynamicMathAstToDynamicExpressionConverter.h"
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
inline typename CmdCalculator::DynamicMathAstToDynamicExpressionConverter
<
	DynamicExpressionPartRecursiveSplitterT,
	RecursiveSplitResultToDynamicExpressionConverterT
>::OutputExpressionType
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter
	<
		DynamicExpressionPartRecursiveSplitterT,
		RecursiveSplitResultToDynamicExpressionConverterT
	>::getMathAstAsExpression
(
	const RootMathAstNodeType& sourceRootNode
) const
{
	throw NotImplementedException{};
}