#pragma once

#include "BasicDynamicOperandToDynamicExpressionConverter.h"
#include "NotImplementedException.h"


template
<
	CmdCalculator::MathAstToExpressionConverter InnerConverterT,
	CmdCalculator::String MathAstStringT,
	CmdCalculator::Arithmetic::RealNumber ExpressionNumberT
>
inline CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT, ExpressionNumberT>::
	BasicDynamicOperandToDynamicExpressionConverter(const InnerConverterT& innerConverter)
{
	throw NotImplementedException{};
}


template
<
	CmdCalculator::MathAstToExpressionConverter InnerConverterT,
	CmdCalculator::String MathAstStringT,
	CmdCalculator::Arithmetic::RealNumber ExpressionNumberT
>
inline std::unique_ptr<CmdCalculator::Expressions::DynamicExpression<ExpressionNumberT>>
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT, ExpressionNumberT>::
	getOperandAsExpression(const MathAst::DynamicOperandNode<MathAstStringT>& sourceOperand) const
{
	throw NotImplementedException{};
}