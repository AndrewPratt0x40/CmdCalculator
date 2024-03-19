#pragma once

#include<concepts>
#include<ranges>

#include "utilities.h"
#include "DynamicExpressionPartSingleSplitResult.h"
#include "DynamicExpressionPartRecursiveSplitResult.h"
#include "DynamicExpressionPartNode.h"
#include "DynamicExpressionNode.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref DynamicExpressionPartSingleSplitter concept.
	struct DynamicExpressionPartSingleSplitter_IntendedSatisfaction
	{};


	/// \brief A type that splits ranges of \ref MathAst::DynamicExpressionPartNode instances by their order of operation a single time.
	/// \tparam T The splitter type.
	template<class T>
	concept DynamicExpressionPartSingleSplitter =
		IntendsToSatisfy<T, DynamicExpressionPartSingleSplitter_IntendedSatisfaction>
		&& String<typename T::MathAstStringType>
		&& requires(T&& instance, MathAst::DynamicExpressionNodePartsView<typename T::MathAstStringType> parts)
		{
			{ instance.canSplit(parts) } -> std::same_as<bool>;
			{ instance.tryToSplit(parts) } -> Optional;
			DynamicExpressionPartSingleSplitResult<OptionalValueType<decltype(instance.tryToSplit(parts))>>;
		}
	;


	template<DynamicExpressionPartSingleSplitter SplitterT>
	using SingleSplitResultType =
		OptionalValueType
		<
			decltype
			(
				std::declval<SplitterT>().tryToSplit
				(
					std::declval<MathAst::DynamicExpressionNodePartsView<typename SplitterT::MathAstStringType>>()
				)
			)
		>
	;
}