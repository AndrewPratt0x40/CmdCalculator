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
		::BasicRSRToDynamicExpressionConverter(const InnerOperandConverterT& innerOperandConverter) :
	m_innerOperandConverter{ std::ref(innerOperandConverter) }
{}


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
	const MathAst::DynamicExpressionPartNode<MathAstStringT>& splitPart{ sourceSplitResult.getSplitPart() };

	if (splitPart.isBinaryOperator())
		throw NotImplementedException{};

	return std::move
	(
		invokeInnerOperandConverter
		(
			reinterpret_cast<const MathAst::DynamicOperandNode<MathAstStringT>&>(splitPart)
		)
	);
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
	::invokeInnerOperandConverter(const MathAst::DynamicOperandNode<MathAstStringT>& operand) const
{
	return std::move(m_innerOperandConverter.get().getOperandAsExpression(operand));
}