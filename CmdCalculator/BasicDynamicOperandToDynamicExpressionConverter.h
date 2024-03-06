#pragma once

#include <memory>

#include "DynamicOperandToDynamicExpressionConverter.h"
#include "MathAstToExpressionConverter.h"
#include "RealNumber.h"
#include "dynamic_mathast.h"
#include "dynamic_expressions.h"
#include "strings.h"


namespace CmdCalculator
{
	/// \brief A basic implementation that satisfies the \ref DynamicOperandToDynamicExpressionConverter concept.
	/// \tparam MathAstToExpressionConverterT The type of object to use for converting inner math ASTs into expression objects.
	/// \tparam MathAstStringT The string type used by the math AST nodes to convert from.
	/// \tparam ExpressionNumberT The number type used by the expression objects to convert to.
	template
	<
		MathAstToExpressionConverter InnerConverterT,
		String MathAstStringT,
		Arithmetic::RealNumber ExpressionNumberT
	>
	class BasicDynamicOperandToDynamicExpressionConverter :
		public DynamicOperandToDynamicExpressionConverter_IntendedSatisfaction
	{
	public:
		using InnerConverterType = InnerConverterT;
		using MathAstStringType = MathAstStringT;
		using ExpressionNumberType = ExpressionNumberT;


		/// \brief Creates a new instance of the \ref BasicDynamicOperandToDynamicExpressionConverter class.
		/// \param innerConverter The object to use for converting inner math ASTs into expression objects.
		BasicDynamicOperandToDynamicExpressionConverter(const InnerConverterT& innerConverter);


		/// \brief Converts a math AST operand into an expression object.
		/// \param sourceOperand The AST node to convert.
		/// \return \p sourceOperand as an expression instance.
		std::unique_ptr<Expressions::DynamicExpression<ExpressionNumberT>> getOperandAsExpression
		(
			const MathAst::DynamicOperandNode<MathAstStringT>& sourceOperand
		) const;
	};
}


#include "BasicDynamicOperandToDynamicExpressionConverter.hpp"