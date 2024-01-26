#pragma once

#include <concepts>
#include <memory>
#include <string>

#include "AntlrContextToMathAstConverter.h"
#include "FullExpressionAntlrContext.h"
#include "AntlrContextTypeDeductions.h"
#include "dynamic_mathast.h"
#include "strings.h"
#include "NotImplementedException.h"

namespace CmdCalculator
{
	/// \brief A type that converts ANTLR parsing output into polymorphic mathematical abstract syntax trees.
	/// \tparam FullExpressionAntlrContextT The ANTLR context object for a full expression to convert into a math AST.
	/// \tparam CharT The character type to use for strings in the math AST.
	/// \tparam IntT The integer type to use in the math AST.
	template
	<
		FullExpressionAntlrContext FullExpressionAntlrContextT,
		class CharT,
		std::integral IntT
	>
	class AntlrContextToDynamicMathAstConverter :
		public AntlrContextToMathAstConverter_IntendedSatisfaction
	{
	public:

		using FullExpressionAntlrContextType = FullExpressionAntlrContextT;
		using CharType = CharT;
		using StringType = std::basic_string<CharType>;
		using IntType = IntT;


		std::unique_ptr<MathAst::DynamicExpressionNode<StringType>> getConvertedFullExpressionContext
			(const FullExpressionAntlrContextType& context) const
		{
			throw NotImplementedException{};
		}


		std::unique_ptr<MathAst::DynamicExpressionNode<StringType>> getConvertedExpressionContext
			(const AntlrContextTypeDeductions::ExpressionType<FullExpressionAntlrContextType>& context) const
		{
			throw NotImplementedException{};
		}


		std::unique_ptr<MathAst::DynamicOperandNode<StringType>> getConvertedOperandContext
			(const AntlrContextTypeDeductions::OperandType<FullExpressionAntlrContextType>& context) const
		{
			throw NotImplementedException{};
		}


		std::unique_ptr<ConvertedOperation_part_pairContext<StringType>> getConvertedOperationPartPairContext
			(const AntlrContextTypeDeductions::OperationPartPairType<FullExpressionAntlrContextType>& context) const
		{
			throw NotImplementedException{};
		}


		std::unique_ptr<MathAst::DynamicBinaryOperatorNode<StringType>> getConvertedBinaryOperatorContext
			(const AntlrContextTypeDeductions::BinaryOperatorType<FullExpressionAntlrContextType>& context) const
		{
			throw NotImplementedException{};
		}


		std::unique_ptr<MathAst::DynamicNumberLiteralNode<StringType, IntType>> getConvertedNumberLiteralContext
			(const AntlrContextTypeDeductions::NumberLiteralType<FullExpressionAntlrContextType>& context) const
		{
			throw NotImplementedException{};
		}


		std::unique_ptr<MathAst::DynamicSignOperationNode<StringType>> getConvertedSignOperationContext
			(const AntlrContextTypeDeductions::SignOperationType<FullExpressionAntlrContextType>& context) const
		{
			throw NotImplementedException{};
		}


		std::unique_ptr<MathAst::DynamicSqrtOperationNode<StringType>> getConvertedSqrtOperationContext
			(const AntlrContextTypeDeductions::SqrtOperationType<FullExpressionAntlrContextType>& context) const
		{
			throw NotImplementedException{};
		}


		std::unique_ptr<MathAst::DynamicGroupingNode<StringType>> getConvertedGroupingContext
			(const AntlrContextTypeDeductions::GroupingType<FullExpressionAntlrContextType>& context) const
		{
			throw NotImplementedException{};
		}


		std::unique_ptr<MathAst::DynamicGroupingMultiplicationNode<StringType>> getConvertedGroupingMultiplicationContext
			(const AntlrContextTypeDeductions::GroupingMultiplicationType<FullExpressionAntlrContextType>& context) const
		{
			throw NotImplementedException{};
		}


		std::unique_ptr<MathAst::DynamicAbsoluteValueNode<StringType>> getConvertedAbsoluteValueOperationContext
			(const AntlrContextTypeDeductions::AbsoluteValueOperationType<FullExpressionAntlrContextType>& context) const
		{
			throw NotImplementedException{};
		}
	};
}