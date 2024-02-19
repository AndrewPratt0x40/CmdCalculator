#include "DynamicMathAstToDynamicExpressionConverter.h"
#include "NotImplementedException.h"



template<CmdCalculator::DynamicOperandToDynamicExpressionConverter OperandToExpressionConverterT>
inline std::unique_ptr<typename CmdCalculator::DynamicMathAstToDynamicExpressionConverter<OperandToExpressionConverterT>::OutputExpressionType>
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter<OperandToExpressionConverterT>::getMathAstAsExpression
(
	const RootMathAstNodeType& sourceRootNode
) const
{
	throw NotImplementedException{};
}