#pragma once

#include <concepts>

#include "MathAstToExpressionConverter.h"
#include "DynamicExpressionNode.h"
#include "DynamicExpression.h"
#include "FundamentallyBackedRealNumber.h"
#include "strings.h"


namespace CmdCalculator
{
	/// \brief An algorithm to convert a \ref MathAst::DynamicExpressionNode to a \ref Expressions::DynamicExpression instance.
	/// \tparam MathAstStringT The string type used by the dynamic math AST.
	/// \tparam InnerExpressionNumberT The underlying type to store numbers in the resulting dynamic expression.
	template<String MathAstStringT, std::floating_point InnerExpressionNumberT = long double>
	class DynamicMathAstToDynamicExpressionConverter :
		public MathAstToExpressionConverter_IntendedSatisfaction
	{
	public:
		using MathAstStringType = MathAstStringT;
		using InnerExpressionNumberType = InnerExpressionNumberT;
		using RootMathAstNodeType = MathAst::DynamicExpressionNode<MathAstStringType>;
		using OutputExpressionNumberType = Arithmetic::FundamentallyBackedRealNumber<InnerExpressionNumberType>;
		using OutputExpressionType = Expressions::DynamicExpression<OutputExpressionNumberType>;


	private:
		// TODO


	public:

		/// \brief Converts a mathematical abstract syntax tree into an expression.
		/// \param sourceRootNode The root node of the math AST to convert from.
		/// \returns \p sourceRootNode as a \ref Expressions::DynamicExpressionNode instance.
		OutputExpressionType getMathAstAsExpression(const RootMathAstNodeType& sourceRootNode) const;
	};
}