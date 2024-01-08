#pragma once

#include<concepts>
#include<utility>

#include "dynamic_mathast.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"

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
		std::derived_from<T, BasicAntlrContextToMathAstConverter_IntendedSatisfaction>
		&& String<typename T::StringType>
		&& std::integral<typename T::IntType>
		&& requires(T&& instance, Antlr::CmdCalculatorExpressionParser::Full_expressionContext& context)
		{
			{ instance.getConvertedFull_expressionContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicExpressionNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, Antlr::CmdCalculatorExpressionParser::ExpressionContext& context)
		{
			{ instance.getConvertedExpressionContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicExpressionNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, Antlr::CmdCalculatorExpressionParser::OperandContext& context)
		{
			{ instance.getConvertedOperandContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicOperandNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, Antlr::CmdCalculatorExpressionParser::Operation_part_pairContext& context)
		{
			{ instance.getConvertedOperation_part_pairContext(context) } ->
				std::same_as<std::unique_ptr<ConvertedOperation_part_pairContext<typename T::StringType>>>;
		}
		&& requires(T&& instance, Antlr::CmdCalculatorExpressionParser::Binary_operatorContext& context)
		{
			{ instance.getConvertedBinary_operatorContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicBinaryOperatorNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, Antlr::CmdCalculatorExpressionParser::Number_literalContext& context)
		{
			{ instance.getConvertedNumber_literalContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicNumberLiteralNode<typename T::StringType, typename T::IntType>>>;
		}
		&& requires(T&& instance, Antlr::CmdCalculatorExpressionParser::Sign_operationContext& context)
		{
			{ instance.getConvertedSign_operationContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicSignOperationNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, Antlr::CmdCalculatorExpressionParser::Sqrt_operationContext& context)
		{
			{ instance.getConvertedSqrt_operationContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicSqrtOperationNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, Antlr::CmdCalculatorExpressionParser::GroupingContext& context)
		{
			{ instance.getConvertedGroupingContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicGroupingNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, Antlr::CmdCalculatorExpressionParser::Grouping_multiplicationContext& context)
		{
			{ instance.getConvertedGrouping_multiplicationContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicGroupingMultiplicationNode<typename T::StringType>>>;
		}
		&& requires(T&& instance, Antlr::CmdCalculatorExpressionParser::Absolute_value_operationContext& context)
		{
			{ instance.getConvertedAbsolute_value_operationContext(context) } ->
				std::same_as<std::unique_ptr<MathAst::DynamicAbsoluteValueNode<typename T::StringType>>>;
		}
	;
}