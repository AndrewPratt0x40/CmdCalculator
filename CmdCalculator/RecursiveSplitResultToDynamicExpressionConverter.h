#pragma once

#include<concepts>

#include "utilities.h"
#include "DynamicExpressionPartRecursiveSplitResult.h"
#include "DynamicExpression.h"
#include "RealNumber.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref RecursiveSplitResultToDynamicExpressionConverter concept.
	struct RecursiveSplitResultToDynamicExpressionConverter_IntendedSatisfaction
	{};


	/// \brief A type that converts recursive math AST split results into \ref Expressions::DynamicExpression instances.
	/// \tparam T The converter type.
	template<class T>
	concept RecursiveSplitResultToDynamicExpressionConverter =
		IntendsToSatisfy<T, RecursiveSplitResultToDynamicExpressionConverter_IntendedSatisfaction>
		&& DynamicExpressionPartRecursiveSplitResult<typename T::SourceSplitResultType>
		&& Arithmetic::RealNumber<typename T::ExpressionNumberType>
		&& requires(T&& instance, const typename T::SourceSplitResultType& sourceSplitResult)
	{
		std::convertible_to
		<
			decltype(instance.getSplitResultAsExpression(sourceSplitResult)),
			std::unique_ptr<Expressions::DynamicExpression<typename T::ExpressionNumberType>>
		>;
	}
	;
}