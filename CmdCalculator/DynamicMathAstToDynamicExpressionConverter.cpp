#include "DynamicMathAstToDynamicExpressionConverter.h"
#include "NotImplementedException.h"



template<CmdCalculator::DynamicOperandToDynamicExpressionConverter OperandToExpressionConverterT>
inline typename CmdCalculator::DynamicMathAstToDynamicExpressionConverter<OperandToExpressionConverterT>::OutputExpressionType
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter<OperandToExpressionConverterT>::getMathAstAsExpression
(
	const RootMathAstNodeType& sourceRootNode
) const
{
	throw NotImplementedException{};
}