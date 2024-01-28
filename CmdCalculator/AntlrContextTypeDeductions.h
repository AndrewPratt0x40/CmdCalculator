#pragma once

#include "FullExpressionAntlrContext.h"

namespace CmdCalculator::AntlrContextTypeDeductions
{
	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using ExpressionType =
		std::remove_reference_t
		<
			decltype
			(
				std::declval<FullExpressionAntlrContextT>()
				.getExpressionValue()
			)
		>
	;

	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using OperandType =
		std::remove_reference_t
		<
			decltype
			(
				std::declval<ExpressionType<FullExpressionAntlrContextT>>()
				.getHeadOperand()
			)
		>
	;

	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using OperationPartPairType =
		std::remove_reference_t
		<
			std::ranges::range_value_t
			<
				decltype
				(
					std::declval<ExpressionType<FullExpressionAntlrContextT>>()
					.getOperationPartPairs()
				)
			>
		>
	;

	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using NonGroupingMultiplicationType =
		typename decltype
		(
			std::declval<OperandType<FullExpressionAntlrContextT>>()
			.getNonGroupingMultiplicationOperand()
		)
		::value_type
	;

	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using GroupingMultiplicationType =
		typename decltype
		(
			std::declval<OperandType<FullExpressionAntlrContextT>>()
			.getGroupingMultiplicationOperand()
		)
		::value_type
	;

	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using BinaryOperatorType =
		std::remove_reference_t
		<
			decltype
			(
				std::declval<OperationPartPairType<FullExpressionAntlrContextT>>()
				.getOperatorValue()
			)
		>
	;


	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using BinaryOperatorLeadingTriviaType =
		typename
		std::remove_reference_t
		<
			decltype
			(
				std::declval<OperationPartPairType<FullExpressionAntlrContextT>>()
				.getOperatorLeadingTrivia()
			)
		>
		::value_type
	;


	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using BinaryOperatorTrailingTriviaType =
		typename
		std::remove_reference_t
		<
			decltype
			(
				std::declval<OperationPartPairType<FullExpressionAntlrContextT>>()
				.getOperatorTrailingTrivia()
			)
		>::value_type
	;

	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using NumberLiteralType =
		typename decltype
		(
			std::declval<NonGroupingMultiplicationType<FullExpressionAntlrContextT>>()
			.getNumberLiteral()
		)
		::value_type
	;

	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using SignOperationType =
		typename decltype
		(
			std::declval<NonGroupingMultiplicationType<FullExpressionAntlrContextT>>()
			.getSignOperation()
		)
		::value_type
	;

	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using SqrtOperationType =
		typename decltype
		(
			std::declval<NonGroupingMultiplicationType<FullExpressionAntlrContextT>>()
			.getSqrtOperation()
		)
		::value_type
	;

	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using GroupingType =
		typename decltype
		(
			std::declval<NonGroupingMultiplicationType<FullExpressionAntlrContextT>>()
			.getGrouping()
		)
		::value_type
	;

	template<FullExpressionAntlrContext FullExpressionAntlrContextT>
	using AbsoluteValueOperationType =
		typename decltype
		(
			std::declval<NonGroupingMultiplicationType<FullExpressionAntlrContextT>>()
			.getAbsoluteValueOperation()
		)
		::value_type
	;
}