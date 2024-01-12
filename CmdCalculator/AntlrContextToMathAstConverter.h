#pragma once

#include<concepts>
#include<utility>

#include "FullExpressionAntlrContext.h"
#include "dynamic_mathast.h"
#include "AntlrContextTypeDeductions.h"
#include "utilities.h"
#include "strings.h"

namespace CmdCalculator
{
	template<String StringT>
	struct ConvertedOperation_part_pairContext
	{
		std::unique_ptr<MathAst::DynamicBinaryOperatorNode<StringT>> binaryOperator;
		std::unique_ptr<MathAst::DynamicOperandNode<StringT>> operand;
	};
	
	
	/// \brief The base type for types that are intended to satisfy the \ref BasicAntlrContextToMathAstConverter concept.
	struct BasicAntlrContextToMathAstConverter_IntendedSatisfaction
	{};


	/// \brief A type that converts ANTLR contexts objects into mathematical abstract syntax trees.
	/// \tparam T The converter type.
	template<class T>
	concept AntlrContextToMathAstConverter =
		IntendsToSatisfy<T, BasicAntlrContextToMathAstConverter_IntendedSatisfaction>
		&& String<typename T::StringType>
		&& std::integral<typename T::IntType>
		&& FullExpressionAntlrContext<typename T::FullExpressionAntlrContextType>
		&& requires(T&& instance, const typename T::FullExpressionAntlrContextType& context)
		{
			{ instance.getConvertedFullExpressionContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicExpressionNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, const AntlrContextTypeDeductions::ExpressionType<typename T::FullExpressionAntlrContextType>& context)
		{
			{ instance.getConvertedExpressionContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicExpressionNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, const AntlrContextTypeDeductions::OperandType<typename T::FullExpressionAntlrContextType>& context)
		{
			{ instance.getConvertedOperandContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicOperandNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, const AntlrContextTypeDeductions::OperationPartPairType<typename T::FullExpressionAntlrContextType>& context)
		{
			{ instance.getConvertedOperationPartPairContext(context) } ->
				std::same_as<std::unique_ptr<ConvertedOperation_part_pairContext<typename T::StringType>>>;
		}
		&& requires(T&& instance, const AntlrContextTypeDeductions::BinaryOperatorType<typename T::FullExpressionAntlrContextType>& context)
		{
			{ instance.getConvertedBinaryOperatorContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicBinaryOperatorNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, const AntlrContextTypeDeductions::NumberLiteralType<typename T::FullExpressionAntlrContextType>& context)
		{
			{ instance.getConvertedNumberLiteralContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicNumberLiteralNode<typename T::StringType, typename T::IntType>>>;
		}
		&& requires(T&& instance, const AntlrContextTypeDeductions::SignOperationType<typename T::FullExpressionAntlrContextType>& context)
		{
			{ instance.getConvertedSignOperationContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicSignOperationNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, const AntlrContextTypeDeductions::SqrtOperationType<typename T::FullExpressionAntlrContextType>& context)
		{
			{ instance.getConvertedSqrtOperationContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicSqrtOperationNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, const AntlrContextTypeDeductions::GroupingType<typename T::FullExpressionAntlrContextType>& context)
		{
			{ instance.getConvertedGroupingContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicGroupingNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, const AntlrContextTypeDeductions::GroupingMultiplicationType<typename T::FullExpressionAntlrContextType>& context)
		{
			{ instance.getConvertedGroupingMultiplicationContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicGroupingMultiplicationNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, const AntlrContextTypeDeductions::AbsoluteValueOperationType<typename T::FullExpressionAntlrContextType>& context)
		{
			{ instance.getConvertedAbsolute_value_operationContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicAbsoluteValueNode<typename T::StringType>>>;
		}
	;
}