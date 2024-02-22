#pragma once

#include<concepts>
#include<ranges>

#include "utilities.h"
#include "DynamicExpressionPartRecursiveSplitResult.h"
#include "DynamicExpressionPartNode.h"
#include "DynamicExpressionNode.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref DynamicExpressionPartRecursiveSplitter concept.
	struct DynamicExpressionPartRecursiveSplitter_IntendedSatisfaction
	{};


	/// \brief A type that recursively splits ranges of \ref MathAst::DynamicExpressionPartNode instances by their order of operations until they cannot be split anymore.
	/// \tparam T The splitter type.
	template<class T>
	concept DynamicExpressionPartRecursiveSplitter =
		IntendsToSatisfy<T, DynamicExpressionPartRecursiveSplitter_IntendedSatisfaction>
		&& String<typename T::MathAstStringType>
		&& requires(T&& instance, MathAst::DynamicExpressionNodePartsView<typename T::MathAstStringType> parts)
		{
			{ instance.tryToSplit(parts) } -> Optional;
			DynamicExpressionPartRecursiveSplitResult<OptionalValueType<decltype(instance.tryToSplit(parts))>>;
		}
	;
}