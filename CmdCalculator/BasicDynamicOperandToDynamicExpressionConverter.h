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
	namespace
	{
		using DefaultNumberType = Arithmetic::FundamentallyBackedRealNumber<long double>;
	}


	/// \brief A basic implementation that satisfies the \ref DynamicOperandToDynamicExpressionConverter concept.
	/// \tparam MathAstStringT The string type used by the math AST nodes to convert from.
	/// \tparam InnerConverterExpressionT The boxed expression type returned by the object's inner converter.
	template
	<
		String MathAstStringT,
		Expressions::BoxableInnerExpression InnerConverterExpressionT =
			Expressions::DynamicExpression<DefaultNumberType>
	>
	class BasicDynamicOperandToDynamicExpressionConverter :
		public DynamicOperandToDynamicExpressionConverter_IntendedSatisfaction
	{
	public:
		using MathAstStringType = MathAstStringT;
		using ExpressionNumberType = DefaultNumberType;
		using InnerConverterFunctorType = std::function
		<
			Expressions::DynamicExpressionBox<InnerConverterExpressionT>
			(const MathAst::DynamicExpressionNode<MathAstStringT>&)
		>;


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

		InnerConverterFunctorType m_innerConverter;


	public:

		/// \brief Creates a new instance of the \ref BasicDynamicOperandToDynamicExpressionConverter class.
		/// \param innerConverter The object to use for converting inner math ASTs into expression objects.
		BasicDynamicOperandToDynamicExpressionConverter(InnerConverterFunctorType innerConverter);


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