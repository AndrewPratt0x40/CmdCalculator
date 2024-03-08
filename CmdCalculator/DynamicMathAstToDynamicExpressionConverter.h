#pragma once

#include "MathAstToExpressionConverter.h"
#include "DynamicExpressionBox.h"


namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref DynamicMathAstToDynamicExpressionConverter concept.
	struct DynamicMathAstToDynamicExpressionConverter_IntendedSatisfaction
	{};


	/// \brief An algorithm to convert a \ref MathAst::DynamicExpressionNode to a \ref Expressions::DynamicExpression instance.
	/// \tparam T The converter type.
	template<class T>
	concept DynamicMathAstToDynamicExpressionConverter =
		IntendsToSatisfy<T, DynamicMathAstToDynamicExpressionConverter_IntendedSatisfaction>
		&& MathAstToExpressionConverter<T>
		&& requires(T&& instance, const typename T::RootMathAstNodeType& sourceRootNode)
	{
		typename ResultOfMathAstToExpressionConverterType<T>::BoxedExpressionType;
		{ instance.getMathAstAsExpression(sourceRootNode) } ->
			std::same_as
			<
				Expressions::DynamicExpressionBox
				<
					typename ResultOfMathAstToExpressionConverterType<T>::BoxedExpressionType
				>
			>
		;
	}
	;
}