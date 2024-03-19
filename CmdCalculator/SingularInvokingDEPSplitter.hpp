#pragma once

#include "SingularInvokingDEPSplitter.h"
#include "NotImplementedException.h"


template<CmdCalculator::DynamicExpressionPartSingleSplitter SingularSplitterT>
inline CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::SingularInvokingDEPSplitter
(
	SingularSplitterT&& singularSplitter
) :
	m_singularSplitter{ singularSplitter }
{}


template<CmdCalculator::DynamicExpressionPartSingleSplitter SingularSplitterT>
inline std::optional
<
	CmdCalculator::BasicDEPRecursiveSplitResult
	<
		typename CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::MathAstStringType
	>
>
	CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::tryToSplit
(
	MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts
) const
{
	std::unique_ptr<BasicDEPRecursiveSplitResult<MathAstStringType>> resultPtr
	{
		tryToSplitAsPtr(parts)
	};

	return resultPtrToOptional(resultPtr);
}


template<CmdCalculator::DynamicExpressionPartSingleSplitter SingularSplitterT>
inline std::optional
<
	CmdCalculator::BasicDEPRecursiveSplitResult
	<
		typename CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::MathAstStringType
	>
>
	CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::resultPtrToOptional
(
	std::unique_ptr<BasicDEPRecursiveSplitResult<MathAstStringType>>& resultPtr
) const
{
	if (resultPtr)
	{
		return std::make_optional<BasicDEPRecursiveSplitResult<MathAstStringType>>
		(
			std::move(*resultPtr.release())
		);
	}
	return {};
}


template<CmdCalculator::DynamicExpressionPartSingleSplitter SingularSplitterT>
inline std::unique_ptr
<
	CmdCalculator::BasicDEPRecursiveSplitResult
	<
		typename CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::MathAstStringType
	>
>
	CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::tryToSplitAsPtr
(
	MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts
) const
{
	const std::optional<SingularSplitterResultType> singleSplitResult
	{
		m_singularSplitter.tryToSplit(parts)
	};

	return singleSplitResult.has_value()
		? tryConvertSingleSplitResult(singleSplitResult.value())
		: nullptr
	;
}


template<CmdCalculator::DynamicExpressionPartSingleSplitter SingularSplitterT>
inline std::unique_ptr
<
	CmdCalculator::BasicDEPRecursiveSplitResult
	<
		typename CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::MathAstStringType
	>
>
	CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::tryConvertSingleSplitResult
(
	const SingularSplitterResultType& singleSplitResult
) const
{
	std::unique_ptr<BasicDEPRecursiveSplitResult<MathAstStringType>> leftPart;
	if (!tryConvertSingleSplitResultSide(singleSplitResult.getLeftParts(), leftPart))
		return {};

	std::unique_ptr<BasicDEPRecursiveSplitResult<MathAstStringType>> rightPart;
	if (!tryConvertSingleSplitResultSide(singleSplitResult.getRightParts(), rightPart))
		return {};

	return std::make_unique<BasicDEPRecursiveSplitResult<MathAstStringType>>
	(
		std::move(leftPart),
		singleSplitResult.getSplitPart(),
		std::move(rightPart)
	);
}


template<CmdCalculator::DynamicExpressionPartSingleSplitter SingularSplitterT>
inline bool
	CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterT>::tryConvertSingleSplitResultSide
(
	MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto singleSplitResultSideParts,
	std::unique_ptr<BasicDEPRecursiveSplitResult<MathAstStringType>>& part
) const
{
	const std::integral auto singleSplitResultSidePartsSize{ std::ranges::ssize(singleSplitResultSideParts) };

	if (singleSplitResultSidePartsSize > 1)
	{
		part = std::move(tryToSplitAsPtr(singleSplitResultSideParts));
		if (!part)
			return false;
	}
	else if (singleSplitResultSidePartsSize == 1)
	{
		part = std::make_unique<BasicDEPRecursiveSplitResult<MathAstStringType>>
		(
			nullptr,
			*std::begin(singleSplitResultSideParts),
			nullptr
		);
	}
	else
		part = nullptr;

	return true;
}