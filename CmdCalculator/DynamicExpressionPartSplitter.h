#pragma once

#include<concepts>
#include<ranges>

#include "utilities.h"
#include "DynamicExpressionPartSplitResult.h"
#include "DynamicExpressionPartRecursiveSplitResult.h"
#include "DynamicExpressionPartNode.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief The base type for types that are intended to satisfy the \ref DynamicExpressionPartSplitter concept.
	struct DynamicExpressionPartSplitter_IntendedSatisfaction
	{};


	/// \brief A type that splits ranges of \ref MathAst::DynamicExpressionPartNode instances by their order of operation.
	/// \tparam T The splitter type.
	/// \tparam PartsInputRangeT The type of range of each expression part node that is passed as input to the splitter.
	template<class T, class PartsInputRangeT>
	concept DynamicExpressionPartSplitter =
		IntendsToSatisfy<T, DynamicExpressionPartSplitter_IntendedSatisfaction>
		&& String<typename T::MathAstStringType>
		&& MathAst::DynamicExpressionPartNodeRange<PartsInputRangeT, typename T::MathAstStringType>
		&& requires(T&& instance, PartsInputRangeT parts)
		{
			{ instance.canSplit(parts) } -> std::same_as<bool>;
			{ instance.tryToSplit(parts) } -> OptionalDynamicExpressionPartSplitResult;
		}
	;


	/// \brief Recursively splits a range of expression parts by their order of operations until they cannot be split anymore.
	/// \tparam SplitterT The type of the object to split the expression parts.
	/// \tparam PartsInputRangeT The type of range of each expression part node that is passed as input to the splitter.
	/// \param splitter The object to split the expression parts.
	/// \param parts The range of expression parts to split.
	/// \returns \p parts recursively split by \p splitter.
	template<class SplitterT, class PartsInputRangeT>
		requires DynamicExpressionPartSplitter<SplitterT, PartsInputRangeT>
	DynamicExpressionPartRecursiveSplitResult auto recursivelySplitExpressionParts(const SplitterT& splitter, PartsInputRangeT parts);
}


#include "DynamicExpressionPartSplitter.hpp"