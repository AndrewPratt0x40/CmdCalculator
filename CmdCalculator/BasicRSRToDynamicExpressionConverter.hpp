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



/// \internal
template<CmdCalculator::Expressions::Expression ExpressionT>
using DynamicExpressionOfSameNumberType = CmdCalculator::Expressions::DynamicExpression
<
	CmdCalculator::Expressions::ExpressionEvaluationType<ExpressionT>
>;

/// \internal
template<class T>
concept DerivedDynamicBinaryExpression =
	CmdCalculator::Expressions::Expression<T>
	&& std::convertible_to
	<
		std::unique_ptr<T>,
		std::unique_ptr<DynamicExpressionOfSameNumberType<T>>
	>
	&& requires
	{
		std::make_unique<T>
		(
			std::move(std::declval<std::unique_ptr<DynamicExpressionOfSameNumberType<T>>>),
			std::move(std::declval<std::unique_ptr<DynamicExpressionOfSameNumberType<T>>>)
		);
	}
;


template<CmdCalculator::String MathAstStringT, DerivedDynamicBinaryExpression ExpressionT>
static std::unique_ptr<ExpressionT> getOperandsAndSplitPartAsDerivedBinaryOperation
(
	std::unique_ptr<DynamicExpressionOfSameNumberType<ExpressionT>> leftOperand,
	const CmdCalculator::MathAst::DynamicBinaryOperatorNode<MathAstStringT>& splitPart,
	std::unique_ptr<DynamicExpressionOfSameNumberType<ExpressionT>> rightOperand
);


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
		return getOperandsAndSplitPartAsDerivedBinaryOperation
		<
			MathAstStringT,
			Expressions::DynamicAdditionOperation<ExpressionNumberType>
		>(std::move(leftPart), splitPart, std::move(rightPart));
	case MathAst::EBinaryOperator::Subtraction:
		return getOperandsAndSplitPartAsDerivedBinaryOperation
		<
			MathAstStringT,
			Expressions::DynamicSubtractionOperation<ExpressionNumberType>
		>(std::move(leftPart), splitPart, std::move(rightPart));
	case MathAst::EBinaryOperator::Multiplication:
		return getOperandsAndSplitPartAsDerivedBinaryOperation
		<
			MathAstStringT,
			Expressions::DynamicMultiplicationOperation<ExpressionNumberType>
		>(std::move(leftPart), splitPart, std::move(rightPart));
	case MathAst::EBinaryOperator::Division:
		return getOperandsAndSplitPartAsDerivedBinaryOperation
		<
			MathAstStringT,
			Expressions::DynamicDivisionOperation<ExpressionNumberType>
		>(std::move(leftPart), splitPart, std::move(rightPart));
	case MathAst::EBinaryOperator::Exponentiation:
		return getOperandsAndSplitPartAsDerivedBinaryOperation
		<
			MathAstStringT,
			Expressions::DynamicExponentiationOperation<ExpressionNumberType>
		>(std::move(leftPart), splitPart, std::move(rightPart));
	case MathAst::EBinaryOperator::NthRoot:
		return getOperandsAndSplitPartAsDerivedBinaryOperation
		<
			MathAstStringT,
			Expressions::DynamicNthRootOperation<ExpressionNumberType>
		>(std::move(leftPart), splitPart, std::move(rightPart));
	case MathAst::EBinaryOperator::Modulo:
		return getOperandsAndSplitPartAsDerivedBinaryOperation
		<
			MathAstStringT,
			Expressions::DynamicModuloOperation<ExpressionNumberType>
		>(std::move(leftPart), splitPart, std::move(rightPart));
	default:
		Polyfills::unreachable();
	}
}


template<CmdCalculator::String MathAstStringT, DerivedDynamicBinaryExpression ExpressionT>
inline std::unique_ptr<ExpressionT> getOperandsAndSplitPartAsDerivedBinaryOperation
(
	std::unique_ptr<DynamicExpressionOfSameNumberType<ExpressionT>> leftOperand, 
	const CmdCalculator::MathAst::DynamicBinaryOperatorNode<MathAstStringT>& splitPart,
	std::unique_ptr<DynamicExpressionOfSameNumberType<ExpressionT>> rightOperand
)
{
	assert(leftOperand);
	assert(rightOperand);

	return std::make_unique<ExpressionT>
		(std::move(leftOperand), std::move(rightOperand))
	;
}