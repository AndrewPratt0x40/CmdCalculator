#include "DynamicMathAstToDynamicExpressionConverter.h"
#include "NotImplementedException.h"



template<CmdCalculator::String MathAstStringT, std::floating_point InnerExpressionNumberT>
inline CmdCalculator::DynamicMathAstToDynamicExpressionConverter<MathAstStringT, InnerExpressionNumberT>::OutputExpressionType
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter<MathAstStringT, InnerExpressionNumberT>::getMathAstAsExpression
(
	const RootMathAstNodeType& sourceRootNode
) const
{
	throw NotImplementedException{};
}