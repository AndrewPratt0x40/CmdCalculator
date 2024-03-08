#pragma once

#include <memory>
#include <functional>

#include "DynamicOperandToDynamicExpressionConverter.h"
#include "DynamicMathAstToDynamicExpressionConverter.h"
#include "FundamentallyBackedRealNumber.h"
#include "dynamic_mathast.h"
#include "dynamic_expressions.h"
#include "strings.h"
#include "utilities.h"


namespace CmdCalculator
{
	/// \brief A basic implementation that satisfies the \ref DynamicOperandToDynamicExpressionConverter concept.
	/// \tparam InnerConverterT The type of object to use for converting inner math ASTs into expression objects.
	/// \tparam MathAstStringT The string type used by the math AST nodes to convert from.
	/// \tparam ExpressionNumberT The number type used by the expression objects to convert to.
	template
	<
		DynamicMathAstToDynamicExpressionConverter InnerConverterT,
		String MathAstStringT
	>
	class BasicDynamicOperandToDynamicExpressionConverter :
		public DynamicOperandToDynamicExpressionConverter_IntendedSatisfaction
	{
	public:
		using InnerConverterType = InnerConverterT;
		using MathAstStringType = MathAstStringT;
		using ExpressionNumberType = Arithmetic::FundamentallyBackedRealNumber<long double>;


	private:
		using DynamicExprUniquePtrType = std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>>;
		using TailMultiplicandRangeIterType =
			std::ranges::iterator_t
			<
				decltype
				(
					std::declval<const MathAst::DynamicGroupingMultiplicationNode<MathAstStringT>&>()
					.getTailMultiplicands()
				)
			>
		;
		using TailMultiplicandSubrangeType = std::ranges::subrange<TailMultiplicandRangeIterType>;

		std::reference_wrapper<const InnerConverterT> m_innerConverter;


	public:

		/// \brief Creates a new instance of the \ref BasicDynamicOperandToDynamicExpressionConverter class.
		/// \param innerConverter The object to use for converting inner math ASTs into expression objects.
		BasicDynamicOperandToDynamicExpressionConverter(const InnerConverterT& innerConverter);


		/// \brief Converts a math AST operand into an expression object.
		/// \param sourceOperand The AST node to convert.
		/// \return \p sourceOperand as an expression instance.
		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> getOperandAsExpression
		(
			const MathAst::DynamicOperandNode<MathAstStringT>& sourceOperand
		) const;


	private:

		ExpressionNumberType parseNumber(const MathAstStringT& str) const;


		ExpressionNumberType parseNumberAsFractionalPart(const MathAstStringT& str) const;


		ExpressionNumberType parseWholePart(const std::optional<MathAstStringT>& str) const;


		ExpressionNumberType parseFractionalPart(const std::optional<MathAstStringT>& str) const;
		
		
		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> invokeInnerConverter
		(
			const MathAst::DynamicExpressionNode<MathAstStringT>& sourceExpression
		) const;
		
		
		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> getAbsoluteValueAsExpression
		(
			const MathAst::DynamicAbsoluteValueNode<MathAstStringT>& sourceOperand
		) const;


		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> getGroupingAsExpression
		(
			const MathAst::DynamicGroupingNode<MathAstStringT>& sourceOperand
		) const;


		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> getGroupingMultiplicationTailsAsExpression
		(
			TailMultiplicandSubrangeType tails
		) const;


		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> getGroupingMultiplicationAsExpression
		(
			const MathAst::DynamicGroupingMultiplicationNode<MathAstStringT>& sourceOperand
		) const;


		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> getNumberLiteralAsExpression
		(
			const MathAst::DynamicNumberLiteralNode<MathAstStringT>& sourceOperand
		) const;


		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> getSignOperationAsExpression
		(
			const MathAst::DynamicSignOperationNode<MathAstStringT>& sourceOperand
		) const;


		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> getSqrtAsExpression
		(
			const MathAst::DynamicSqrtOperationNode<MathAstStringT>& sourceOperand
		) const;
	};
}


#include "BasicDynamicOperandToDynamicExpressionConverter.hpp"