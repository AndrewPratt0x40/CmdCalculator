#pragma once

#include "BasicRSRToDynamicExpressionConverter.h"
#include "NotImplementedException.h"


template
<
	CmdCalculator::DynamicExpressionPartRecursiveSplitResult SourceSplitResultT,
	CmdCalculator::DynamicOperandToDynamicExpressionConverter InnerOperandConverterT,
	CmdCalculator::String MathAstStringT
>
inline CmdCalculator::BasicRSRToDynamicExpressionConverter<SourceSplitResultT, InnerOperandConverterT, MathAstStringT>
	::BasicRSRToDynamicExpressionConverter(const InnerOperandConverterT& innerOperandConverter)
{
	throw NotImplementedException{};
}


template
<
	CmdCalculator::DynamicExpressionPartRecursiveSplitResult SourceSplitResultT,
	CmdCalculator::DynamicOperandToDynamicExpressionConverter InnerOperandConverterT,
	CmdCalculator::String MathAstStringT
>
inline std::unique_ptr
<
	CmdCalculator::Expressions::DynamicExpression
	<
		typename CmdCalculator::BasicRSRToDynamicExpressionConverter<SourceSplitResultT, InnerOperandConverterT, MathAstStringT>
			::ExpressionNumberType
	>
>
	CmdCalculator::BasicRSRToDynamicExpressionConverter<SourceSplitResultT, InnerOperandConverterT, MathAstStringT>
	::getSplitResultAsExpression(const SourceSplitResultT& sourceSplitResult) const
{
	throw NotImplementedException{};
}