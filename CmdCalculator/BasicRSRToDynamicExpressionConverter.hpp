#pragma once

#include <ranges>
#include <concepts>
#include <memory>
#include <functional>
#include <assert.h>

#include "BasicRSRToDynamicExpressionConverter.h"
#include "RecursiveSplitResultToDynamicExpressionConverter.h"
#include "DynamicExpressionPartRecursiveSplitResult.h"
#include "DynamicOperandToDynamicExpressionConverter.h"
#include "dynamic_mathast.h"
#include "dynamic_expressions.h"
#include "strings.h"
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
	{
		const SourceSplitResultT* leftPart{ sourceSplitResult.getLeftPart() };
		assert(leftPart);

		const SourceSplitResultT* rightPart{ sourceSplitResult.getRightPart() };
		assert(rightPart);

		return getSplitResultAsBinaryOperation
		(
			*leftPart,
			reinterpret_cast<const MathAst::DynamicBinaryOperatorNode<MathAstStringT>&>(splitPart),
			*rightPart
		);
	}

	return invokeInnerOperandConverter
	(
		reinterpret_cast<const MathAst::DynamicOperandNode<MathAstStringT>&>(splitPart)
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
	::getSplitResultAsBinaryOperation
(
	const SourceSplitResultT& leftPart,
	const MathAst::DynamicBinaryOperatorNode<MathAstStringT>& splitPart,
	const SourceSplitResultT& rightPart
) const
{
	return getOperandsAndSplitPartAsBinaryOperation
	(
		getSplitResultAsExpression(leftPart),
		splitPart,
		getSplitResultAsExpression(rightPart)
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
	::getOperandsAndSplitPartAsBinaryOperation
(
	std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> leftPart,
	const MathAst::DynamicBinaryOperatorNode<MathAstStringT>& splitPart,
	std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> rightPart
) const
{
	assert(leftPart);
	assert(rightPart);

	switch (splitPart.getOperatorKind())
	{
	case MathAst::EBinaryOperator::Addition:
		return getOperandsAndSplitPartAsAdditionOperation(std::move(leftPart), splitPart, std::move(rightPart));
	case MathAst::EBinaryOperator::Subtraction:
		throw NotImplementedException{};
	case MathAst::EBinaryOperator::Multiplication:
		throw NotImplementedException{};
	case MathAst::EBinaryOperator::Division:
		throw NotImplementedException{};
	case MathAst::EBinaryOperator::Exponentiation:
		throw NotImplementedException{};
	case MathAst::EBinaryOperator::NthRoot:
		throw NotImplementedException{};
	case MathAst::EBinaryOperator::Modulo:
		throw NotImplementedException{};
	default:
		Polyfills::unreachable();
	}
}


template
<
	CmdCalculator::DynamicExpressionPartRecursiveSplitResult SourceSplitResultT,
	CmdCalculator::DynamicOperandToDynamicExpressionConverter InnerOperandConverterT,
	CmdCalculator::String MathAstStringT
>
inline std::unique_ptr
<
	CmdCalculator::Expressions::DynamicAdditionOperation
	<
	typename CmdCalculator::BasicRSRToDynamicExpressionConverter<SourceSplitResultT, InnerOperandConverterT, MathAstStringT>
		::ExpressionNumberType
	>
>
	CmdCalculator::BasicRSRToDynamicExpressionConverter<SourceSplitResultT, InnerOperandConverterT, MathAstStringT>
	::getOperandsAndSplitPartAsAdditionOperation
(
	std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> augend,
	const MathAst::DynamicBinaryOperatorNode<MathAstStringT>& splitPart,
	std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> addend
) const
{
	assert(augend);
	assert(addend);

	return std::make_unique<Expressions::DynamicAdditionOperation<ExpressionNumberType>>
		(std::move(augend), std::move(addend))
	;
}