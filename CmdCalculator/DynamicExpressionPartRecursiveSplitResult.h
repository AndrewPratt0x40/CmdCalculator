#pragma once

#include<concepts>
#include<ranges>

#include "utilities.h"
#include "DynamicExpressionPartNode.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref DynamicExpressionPartRecursiveSplitResult concept.
	struct DynamicExpressionPartRecursiveSplitResult_IntendedSatisfaction
	{};


	/// \brief The result of recursively splitting a range of expression parts by their order of operations until they cannot be split anymore.
	/// \tparam T The recursive split result type.
	template<class T>
	concept DynamicExpressionPartRecursiveSplitResult =
		IntendsToSatisfy<T, DynamicExpressionPartRecursiveSplitResult_IntendedSatisfaction>
		&& String<typename T::MathAstStringType>
		&& requires(T&& instance)
		{
			{ instance.getLeftPart() } -> std::convertible_to<std::remove_cvref_t<T>*>;

			{ instance.getSplitPart() } -> std::convertible_to<MathAst::DynamicExpressionPartNode<typename T::MathAstStringType>&>;

			{ instance.getRightPart() } -> std::convertible_to<std::remove_cvref_t<T>*>;
		}
	;
}