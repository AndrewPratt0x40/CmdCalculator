#pragma once

#include <memory>
#include <functional>

#include "RecursiveSplitResultToDynamicExpressionConverter.h"
#include "DynamicExpressionPartRecursiveSplitResult.h"
#include "DynamicOperandToDynamicExpressionConverter.h"
#include "dynamic_mathast.h"
#include "dynamic_expressions.h"
#include "strings.h"


namespace CmdCalculator
{
	/// \brief A basic implementation that satisfies the \ref RecursiveSplitResultToDynamicExpressionConverter concept.
	/// \tparam SourceSplitResultT The type of split result to convert from.
	/// \tparam InnerOperandConverterT The type of object to use for converting inner math operand ASTs into expression objects.
	/// \tparam StringT The string type that each expression part node in the math AST uses.
	template
	<
		DynamicExpressionPartRecursiveSplitResult SourceSplitResultT,
		DynamicOperandToDynamicExpressionConverter InnerOperandConverterT,
		String MathAstStringT
	>
	class BasicRSRToDynamicExpressionConverter :
		public RecursiveSplitResultToDynamicExpressionConverter_IntendedSatisfaction
	{
	public:
		using SourceSplitResultType = SourceSplitResultT;
		using InnerOperandConverterType = InnerOperandConverterT;
		using MathAstStringType = MathAstStringT;
		using ExpressionNumberType = InnerOperandConverterT::ExpressionNumberType;


	private:
		std::reference_wrapper<const InnerOperandConverterT> m_innerOperandConverter;


	public:

		/// \brief Creates a new instance of the \ref BasicRSRToDynamicExpressionConverter class.
		/// \param innerOperandConverter The object to use for converting inner math operand ASTs into expression objects.
		BasicRSRToDynamicExpressionConverter(const InnerOperandConverterT& innerOperandConverter);


		/// \brief Converts a math AST operand into an expression object.
		/// \param sourceOperand The AST node to convert.
		/// \return \p sourceOperand as an expression instance.
		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> getSplitResultAsExpression
		(
			const SourceSplitResultT& sourceSplitResult
		) const;


	private:

		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> invokeInnerOperandConverter
		(
			const MathAst::DynamicOperandNode<MathAstStringT>& operand
		) const;


		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> getSplitResultAsBinaryOperation
		(
			const SourceSplitResultT& leftPart,
			const MathAst::DynamicBinaryOperatorNode<MathAstStringT>& splitPart,
			const SourceSplitResultT& rightPart
		) const;


		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> getOperandsAndSplitPartAsBinaryOperation
		(
			std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> leftPart,
			const MathAst::DynamicBinaryOperatorNode<MathAstStringT>& splitPart,
			std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> rightPart
		) const;


		std::unique_ptr<Expressions::DynamicAdditionOperation<ExpressionNumberType>> getOperandsAndSplitPartAsAdditionOperation
		(
			std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> augend,
			const MathAst::DynamicBinaryOperatorNode<MathAstStringT>& splitPart,
			std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> addend
		) const;


		std::unique_ptr<Expressions::DynamicSubtractionOperation<ExpressionNumberType>> getOperandsAndSplitPartAsSubtractionOperation
		(
			std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> minuend,
			const MathAst::DynamicBinaryOperatorNode<MathAstStringT>& splitPart,
			std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> subtrahend
		) const;


		std::unique_ptr<Expressions::DynamicMultiplicationOperation<ExpressionNumberType>> getOperandsAndSplitPartAsMultiplicationOperation
		(
			std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> multiplier,
			const MathAst::DynamicBinaryOperatorNode<MathAstStringT>& splitPart,
			std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> multiplicand
		) const;


		std::unique_ptr<Expressions::DynamicDivisionOperation<ExpressionNumberType>> getOperandsAndSplitPartAsDivisionOperation
		(
			std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> dividend,
			const MathAst::DynamicBinaryOperatorNode<MathAstStringT>& splitPart,
			std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberType>> divisor
		) const;
	};
}


#include "BasicRSRToDynamicExpressionConverter.hpp"