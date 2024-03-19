#pragma once

#include <ranges>
#include <concepts>
#include <algorithm>
#include <memory>
#include <functional>
#include <assert.h>

#include "BasicDynamicOperandToDynamicExpressionConverter.h"
#include "NotImplementedException.h"


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::
	BasicDynamicOperandToDynamicExpressionConverter(InnerConverterFunctorType innerConverter) :
	m_innerConverter{ innerConverter }
{}


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline std::unique_ptr
<
	CmdCalculator::Expressions::DynamicExpression
	<
		typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
			::ExpressionNumberType
	>
>
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::
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


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::ExpressionNumberType
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
	::parseNumber(const MathAstStringT& str) const
{
	return ExpressionNumberType
	{
		std::stold(convertString<char>(str))
	};
}


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::ExpressionNumberType
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
	::parseNumberAsFractionalPart(const MathAstStringT& str) const
{
	return ExpressionNumberType
	{
		std::stold("0." + convertString<char>(str))
	};
}


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::ExpressionNumberType
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
	::parseWholePart(const std::optional<MathAstStringT>& str) const
{
	return str.has_value()
		? parseNumber(str.value())
		: ExpressionNumberType{ 0.0 }
	;
}


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::ExpressionNumberType
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
	::parseFractionalPart(const std::optional<MathAstStringT>& str) const
{
	return str.has_value()
		? parseNumberAsFractionalPart(str.value())
		: ExpressionNumberType{ 0.0 }
	;
}


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline std::unique_ptr
<
	CmdCalculator::Expressions::DynamicExpression
	<
		typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
			::ExpressionNumberType
	>
>
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::
	invokeInnerConverter(const MathAst::DynamicExpressionNode<MathAstStringT>& sourceExpression) const
{
	return std::move
	(
		m_innerConverter(sourceExpression).releaseInnerValue()
	);
}


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline std::unique_ptr
<
	CmdCalculator::Expressions::DynamicExpression
	<
		typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
			::ExpressionNumberType
	>
>
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::
	getAbsoluteValueAsExpression(const MathAst::DynamicAbsoluteValueNode<MathAstStringT>& sourceOperand) const
{
	assert(sourceOperand.getContainedExpression());
	
	return std::make_unique<Expressions::DynamicAbsoluteValueOperation<ExpressionNumberType>>
	(
		std::move(invokeInnerConverter(*sourceOperand.getContainedExpression()))
	);
}


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline std::unique_ptr
<
	CmdCalculator::Expressions::DynamicExpression
	<
		typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
			::ExpressionNumberType
	>
>
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::
	getGroupingAsExpression(const MathAst::DynamicGroupingNode<MathAstStringT>& sourceOperand) const
{
	return std::move(invokeInnerConverter(*sourceOperand.getContainedExpression()));
}


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline std::unique_ptr
<
	CmdCalculator::Expressions::DynamicExpression
	<
		typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
			::ExpressionNumberType
	>
>
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::
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


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline std::unique_ptr
<
	CmdCalculator::Expressions::DynamicExpression
	<
		typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
			::ExpressionNumberType
	>
>
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
	::getGroupingMultiplicationTailsAsExpression
(
	typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
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


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline std::unique_ptr
<
	CmdCalculator::Expressions::DynamicExpression
	<
		typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
			::ExpressionNumberType
	>
>
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::
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


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline std::unique_ptr
<
	CmdCalculator::Expressions::DynamicExpression
	<
	typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
	::ExpressionNumberType
	>
>
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::
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


template<CmdCalculator::String MathAstStringT, CmdCalculator::Expressions::BoxableInnerExpression InnerConverterExpressionT>
inline std::unique_ptr
<
	CmdCalculator::Expressions::DynamicExpression
	<
	typename CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>
	::ExpressionNumberType
	>
>
	CmdCalculator::BasicDynamicOperandToDynamicExpressionConverter<MathAstStringT, InnerConverterExpressionT>::
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