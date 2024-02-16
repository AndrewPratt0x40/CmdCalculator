#pragma once

#include<concepts>

#include "utilities.h"
#include "DynamicOperandNode.h"
#include "DynamicExpression.h"
#include "RealNumber.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref DynamicOperandToDynamicExpressionConverter concept.
	struct DynamicOperandToDynamicExpressionConverter_IntendedSatisfaction
	{};


	/// \brief A type that converts \ref MathAst::DynamicOperandNode instances into \ref Expressions::DynamicExpression instances.
	/// \tparam T The converter type.
	template<class T>
	concept DynamicOperandToDynamicExpressionConverter =
		IntendsToSatisfy<T, DynamicOperandToDynamicExpressionConverter_IntendedSatisfaction>
		&& String<typename T::MathAstStringType>
		&& Arithmetic::RealNumber<typename T::ExpressionNumberType>
		&& requires(T&& instance, const MathAst::DynamicOperandNode<typename T::MathAstStringType>& sourceOperand)
	{
		{ instance.getOperandAsExpression(sourceOperand) } -> UniquePtr;
		std::same_as
		<
			decltype(instance.getOperandAsExpression(sourceOperand)),
			std::unique_ptr<Expressions::DynamicExpression<typename T::ExpressionNumberType>>
		>;
	}
	;
}