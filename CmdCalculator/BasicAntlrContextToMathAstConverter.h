#pragma once

#include <concepts>
#include <utility>

#include "AntlrContextToMathAstConverter.h"
#include "dynamic_mathast.h"
#include "strings.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"
#include "NotImplementedException.h"

namespace CmdCalculator
{
	/// \brief The string type that ANTLR uses.
	using AntlrStringType = decltype(std::declval<antlr4::Token>().getText());
	static_assert(String<AntlrStringType>);


	/// \brief A type that converts ANTLR parsing output into mathematical abstract syntax trees.
	/// \tparam StringT The string type to use.
	/// \tparam IntT The type to use to store integers.
	template<String StringT, std::integral IntT>
		requires std::convertible_to<StringT, AntlrStringType>
	class BasicAntlrContextToMathAstConverter :
		public AntlrContextToMathAstConverter_IntendedSatisfaction
	{
	public:

		using StringType = StringT;
		using IntType = IntT;


		MathAst::DynamicExpressionNode<StringT> getConvertedFull_expressionContext(Antlr::CmdCalculatorExpressionParser::Full_expressionContext& context)
		{
			throw NotImplementedException{};
		}


		MathAst::DynamicExpressionNode<StringT> getConvertedExpressionContext(Antlr::CmdCalculatorExpressionParser::ExpressionContext& context)
		{
			throw NotImplementedException{};
		}


		MathAst::DynamicOperandNode<StringT> getConvertedOperandContext(Antlr::CmdCalculatorExpressionParser::OperandContext& context)
		{
			throw NotImplementedException{};
		}


		std::pair<MathAst::DynamicBinaryOperatorNode<StringT>, MathAst::DynamicOperandNode<StringT>> getConvertedOperation_part_pairContext
		(
			Antlr::CmdCalculatorExpressionParser::Operation_part_pairContext& context
		)
		{
			throw NotImplementedException{};
		}


		MathAst::DynamicBinaryOperatorNode<StringT> getConvertedBinary_operatorContext(Antlr::CmdCalculatorExpressionParser::Binary_operatorContext& context)
		{
			throw NotImplementedException{};
		}


		MathAst::DynamicNumberLiteralNode<StringT, IntT> getConvertedNumber_literalContext(Antlr::CmdCalculatorExpressionParser::Number_literalContext& context)
		{
			throw NotImplementedException{};
		}


		MathAst::DynamicSignOperationNode<StringT> getConvertedSign_operationContext(Antlr::CmdCalculatorExpressionParser::Sign_operationContext& context)
		{
			throw NotImplementedException{};
		}


		MathAst::DynamicSqrtOperationNode<StringT> getConvertedSqrt_operationContext(Antlr::CmdCalculatorExpressionParser::Sqrt_operationContext& context)
		{
			throw NotImplementedException{};
		}


		MathAst::DynamicGroupingNode<StringT> getConvertedGroupingContext(Antlr::CmdCalculatorExpressionParser::GroupingContext& context)
		{
			throw NotImplementedException{};
		}


		MathAst::DynamicGroupingMultiplicationNode<StringT> getConvertedGrouping_multiplicationContext(Antlr::CmdCalculatorExpressionParser::Grouping_multiplicationContext& context)
		{
			throw NotImplementedException{};
		}


		MathAst::DynamicAbsoluteValueNode<StringT> getConvertedAbsolute_value_operationContext(Antlr::CmdCalculatorExpressionParser::Absolute_value_operationContext& context)
		{
			throw NotImplementedException{};
		}
	};
}