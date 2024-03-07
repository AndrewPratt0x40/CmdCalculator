#pragma once

#include "BasicDynamicOperandToDynamicExpressionConverter.h"
#include "NotImplementedException.h"


template
<
	CmdCalculator::MathAstToExpressionConverter InnerConverterT,
	CmdCalculator::String MathAstStringT
>
inline CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter
<
	InnerConverterT,
	MathAstStringT
>::
	BasicDynamicOperandToDynamicExpressionConverter(const InnerConverterT& innerConverter)
{
	throw NotImplementedException{};
}


template
<
	CmdCalculator::MathAstToExpressionConverter InnerConverterT,
	CmdCalculator::String MathAstStringT
>
inline std::unique_ptr
<
	CmdCalculator::Expressions::DynamicExpression
	<
		typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT>
		::ExpressionNumberType
	>
>
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT>::
	getOperandAsExpression(const MathAst::DynamicOperandNode<MathAstStringT>& sourceOperand) const
{
	throw NotImplementedException{};
}