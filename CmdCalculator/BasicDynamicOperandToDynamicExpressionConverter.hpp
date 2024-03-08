#pragma once

#include <ranges>
#include <concepts>
#include <algorithm>
#include <memory>
#include <functional>
#include <assert.h>

#include "BasicDynamicOperandToDynamicExpressionConverter.h"
#include "NotImplementedException.h"


template
<
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter InnerConverterT,
	CmdCalculator::String MathAstStringT
>
inline CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter
<
	InnerConverterT,
	MathAstStringT
>::
	BasicDynamicOperandToDynamicExpressionConverter(const InnerConverterT& innerConverter) :
	m_innerConverter{ std::ref(innerConverter) }
{}


template
<
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter InnerConverterT,
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
	switch (sourceOperand.getDerivedOperandKind())
	{
	case MathAst::EDerivedDynamicOperandNodeKind::AbsoluteValue:
		return std::move
		(
			getAbsoluteValueAsExpression
			(
				reinterpret_cast<const MathAst::DynamicAbsoluteValueNode<MathAstStringT>&>(sourceOperand)
			)
		);

	case MathAst::EDerivedDynamicOperandNodeKind::Grouping:
		return std::move
		(
			getGroupingAsExpression
			(
				reinterpret_cast<const MathAst::DynamicGroupingNode<MathAstStringT>&>(sourceOperand)
			)
		);

	case MathAst::EDerivedDynamicOperandNodeKind::GroupingMultiplication:
		return std::move
		(
			getGroupingMultiplicationAsExpression
			(
				reinterpret_cast<const MathAst::DynamicGroupingMultiplicationNode<MathAstStringT>&>(sourceOperand)
			)
		);

	case MathAst::EDerivedDynamicOperandNodeKind::NumberLiteral:
		return std::move
		(
			getNumberLiteralAsExpression
			(
				reinterpret_cast<const MathAst::DynamicNumberLiteralNode<MathAstStringT>&>(sourceOperand)
			)
		);

	case MathAst::EDerivedDynamicOperandNodeKind::SignOperation:
		return std::move
		(
			getSignOperationAsExpression
			(
				reinterpret_cast<const MathAst::DynamicSignOperationNode<MathAstStringT>&>(sourceOperand)
			)
		);

	case MathAst::EDerivedDynamicOperandNodeKind::SqrtOperation:
		return std::move
		(
			getSqrtAsExpression
			(
				reinterpret_cast<const MathAst::DynamicSqrtOperationNode<MathAstStringT>&>(sourceOperand)
			)
		);

	default:
		Polyfills::unreachable();
	}
}


template
<
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter InnerConverterT,
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
	getAbsoluteValueAsExpression(const MathAst::DynamicAbsoluteValueNode<MathAstStringT>& sourceOperand) const
{
	assert(sourceOperand.getContainedExpression());
	
	return std::move
	(
		m_innerConverter.get().getMathAstAsExpression(*sourceOperand.getContainedExpression()).releaseInnerValue()
	);
}


template
<
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter InnerConverterT,
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
	getGroupingAsExpression(const MathAst::DynamicGroupingNode<MathAstStringT>& sourceOperand) const
{
	throw NotImplementedException{};
}


template
<
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter InnerConverterT,
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
	getGroupingMultiplicationAsExpression(const MathAst::DynamicGroupingMultiplicationNode<MathAstStringT>& sourceOperand) const
{
	throw NotImplementedException{};
}


template
<
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter InnerConverterT,
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
	getNumberLiteralAsExpression(const MathAst::DynamicNumberLiteralNode<MathAstStringT>& sourceOperand) const
{
	throw NotImplementedException{};
}


template
<
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter InnerConverterT,
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
	getSignOperationAsExpression(const MathAst::DynamicSignOperationNode<MathAstStringT>& sourceOperand) const
{
	throw NotImplementedException{};
}


template
<
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter InnerConverterT,
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
	getSqrtAsExpression(const MathAst::DynamicSqrtOperationNode<MathAstStringT>& sourceOperand) const
{
	throw NotImplementedException{};
}