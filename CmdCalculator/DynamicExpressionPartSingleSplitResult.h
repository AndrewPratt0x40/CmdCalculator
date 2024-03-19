#pragma once

#include<concepts>
#include<ranges>

#include "utilities.h"
#include "DynamicExpressionPartNode.h"
#include "RealNumber.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref DynamicExpressionPartSingleSplitResult concept.
	struct DynamicExpressionPartSingleSplitResult_IntendedSatisfaction
	{};


	/// \brief The result of splitting a range of \ref MathAst::DynamicExpressionPartNode instances by their order of operation once.
	/// \tparam T The split result type.
	template<class T>
	concept DynamicExpressionPartSingleSplitResult =
		IntendsToSatisfy<T, DynamicExpressionPartSingleSplitResult_IntendedSatisfaction>
		&& String<typename T::MathAstStringType>
		&& requires(T&& instance)
		{
			{ instance.getLeftParts() } -> MathAst::DynamicExpressionPartNodeRange<typename T::MathAstStringType>;

			std::same_as
			<
				std::remove_cv_t<decltype(instance.getSplitPart())>,
				MathAst::DynamicExpressionPartNode<typename T::MathAstStringType>&
			>;

			{ instance.getRightParts() } -> MathAst::DynamicExpressionPartNodeRange<typename T::MathAstStringType>;
		}
	;
}