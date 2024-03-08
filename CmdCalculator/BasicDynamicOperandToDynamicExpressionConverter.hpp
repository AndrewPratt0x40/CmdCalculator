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
inline typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT>::ExpressionNumberType
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT>
	::parseNumber(const MathAstStringT& str) const
{
	return ExpressionNumberType
	{
		std::stold(convertString<char>(str))
	};
}


template
<
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter InnerConverterT,
	CmdCalculator::String MathAstStringT
>
inline typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT>::ExpressionNumberType
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT>
	::parseNumberAsFractionalPart(const MathAstStringT& str) const
{
	return ExpressionNumberType
	{
		std::stold("0." + convertString<char>(str))
	};
}


template
<
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter InnerConverterT,
	CmdCalculator::String MathAstStringT
>
inline typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT>::ExpressionNumberType
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT>
	::parseWholePart(const std::optional<MathAstStringT>& str) const
{
	return str.has_value()
		? parseNumber(str.value())
		: ExpressionNumberType{ 0.0 }
	;
}


template
<
	CmdCalculator::DynamicMathAstToDynamicExpressionConverter InnerConverterT,
	CmdCalculator::String MathAstStringT
>
inline typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT>::ExpressionNumberType
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT>
	::parseFractionalPart(const std::optional<MathAstStringT>& str) const
{
	return str.has_value()
		? parseNumberAsFractionalPart(str.value())
		: ExpressionNumberType{ 0.0 }
	;
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
	invokeInnerConverter(const MathAst::DynamicExpressionNode<MathAstStringT>& sourceExpression) const
{
	return std::move
	(
		m_innerConverter.get().getMathAstAsExpression(sourceExpression).releaseInnerValue()
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
	getAbsoluteValueAsExpression(const MathAst::DynamicAbsoluteValueNode<MathAstStringT>& sourceOperand) const
{
	assert(sourceOperand.getContainedExpression());
	
	return std::make_unique<Expressions::DynamicAbsoluteValueOperation<ExpressionNumberType>>
	(
		std::move(invokeInnerConverter(*sourceOperand.getContainedExpression()))
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
	return std::move(invokeInnerConverter(*sourceOperand.getContainedExpression()));
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
	DynamicExprUniquePtrType multiplier{ getOperandAsExpression(*sourceOperand.getHeadMultiplicand()) };
	MathAst::DynamicGroupingTailMultiplicandRange auto tails{ sourceOperand.getTailMultiplicands() };

	if (std::ranges::empty(tails))
		return std::move(multiplier);

	return std::move
	(
		std::make_unique<Expressions::DynamicMultiplicationOperation<ExpressionNumberType>>
		(
			std::move(multiplier),
			std::move
			(
				getGroupingMultiplicationTailsAsExpression
				(
					TailMultiplicandSubrangeType
					{
						std::ranges::begin(tails),
						std::ranges::end(tails)
					}
				)
			)
		)
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
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT>
	::getGroupingMultiplicationTailsAsExpression
(
	typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<InnerConverterT, MathAstStringT>
		::TailMultiplicandSubrangeType tails
) const
{
	assert(!std::ranges::empty(tails));

	DynamicExprUniquePtrType multiplier{ getGroupingAsExpression(**std::ranges::begin(tails)) };

	if (std::ranges::size(tails) == 1)
		return std::move(multiplier);

	return std::move
	(
		std::make_unique<Expressions::DynamicMultiplicationOperation<ExpressionNumberType>>
		(
			std::move(multiplier),
			std::move(getGroupingMultiplicationTailsAsExpression(tails | std::views::drop(1)))
		)
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
	getNumberLiteralAsExpression(const MathAst::DynamicNumberLiteralNode<MathAstStringT>& sourceOperand) const
{
	return std::move
	(
		std::make_unique<Expressions::DynamicNumber<ExpressionNumberType>>
		(
			parseWholePart(sourceOperand.getWholePart())
			+ parseFractionalPart(sourceOperand.getFractionalPart())
		)
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
	getSignOperationAsExpression(const MathAst::DynamicSignOperationNode<MathAstStringT>& sourceOperand) const
{
	DynamicExprUniquePtrType operand{ getOperandAsExpression(*sourceOperand.getOperand()) };
	
	if (sourceOperand.isPositive())
		return std::move(operand);

	return std::move
	(
		std::make_unique<Expressions::DynamicNegationOperation<ExpressionNumberType>>
		(
			std::move(operand)
		)
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
	getSqrtAsExpression(const MathAst::DynamicSqrtOperationNode<MathAstStringT>& sourceOperand) const
{
	return std::move
	(
		std::make_unique<Expressions::DynamicNthRootOperation<ExpressionNumberType>>
		(
			std::move
			(
				std::make_unique<Expressions::DynamicNumber<ExpressionNumberType>>
				(
					ExpressionNumberType{ 2.0 }
				)
			),
			std::move(getOperandAsExpression(*sourceOperand.getOperand()))
		)
	);
}