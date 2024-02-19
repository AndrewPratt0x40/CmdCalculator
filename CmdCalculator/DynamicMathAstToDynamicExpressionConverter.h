#pragma once

#include <concepts>
#include <memory>

#include "MathAstToExpressionConverter.h"
#include "DynamicOperandToDynamicExpressionConverter.h"
#include "DynamicExpressionNode.h"
#include "DynamicExpressionBox.h"
#include "FundamentallyBackedRealNumber.h"
#include "strings.h"


namespace CmdCalculator
{
	/// \brief An algorithm to convert a \ref MathAst::DynamicExpressionNode to a \ref Expressions::DynamicExpression instance.
	/// \tparam OperandToExpressionConverterT The type of object to use for converting operands into expressions.
	template<DynamicOperandToDynamicExpressionConverter OperandToExpressionConverterT>
	class DynamicMathAstToDynamicExpressionConverter :
		public MathAstToExpressionConverter_IntendedSatisfaction
	{
	public:
		using OperandToExpressionConverterType = OperandToExpressionConverterT;
		using MathAstStringType = OperandToExpressionConverterType::MathAstStringType;

		using RootMathAstNodeType = MathAst::DynamicExpressionNode<MathAstStringType>;
		using OutputExpressionNumberType = OperandToExpressionConverterType::ExpressionNumberType;
		using OutputExpressionType = Expressions::DynamicExpressionBox<OutputExpressionNumberType>;


	private:
		// TODO


	public:

		/// \brief Converts a mathematical abstract syntax tree into an expression.
		/// \param sourceRootNode The root node of the math AST to convert from.
		/// \returns \p sourceRootNode as a \ref Expressions::DynamicExpressionNode instance.
		OutputExpressionType getMathAstAsExpression(const RootMathAstNodeType& sourceRootNode) const;
	};
}