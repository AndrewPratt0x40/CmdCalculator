#pragma once

#include <optional>
#include <memory>

#include "DynamicExpressionPartRecursiveSplitter.h"
#include "DynamicExpressionPartSingleSplitter.h"
#include "BasicDEPRecursiveSplitResult.h"


namespace CmdCalculator
{
	/// \brief A satisfaction of the \ref DynamicExpressionPartRecursiveSplitter concept that invokes a singular splitter object.
	/// \tparam SingularSplitterT The type of the singular splitter to use.
	template<DynamicExpressionPartSingleSplitter SingularSplitterT>
	class SingularInvokingDEPSplitter :
		public DynamicExpressionPartRecursiveSplitter_IntendedSatisfaction
	{
	public:
		using SingularSplitterType = SingularSplitterT;
		using MathAstStringType = typename SingularSplitterType::MathAstStringType;
		using SingularSplitterResultType = SingleSplitResultType<SingularSplitterType>;


	private:
		SingularSplitterType m_singularSplitter;


	public:
		/// \brief Creates a new instance of the \ref SingularInvokingDEPSplitter class.
		/// \param singularSplitter The singular splitter to use.
		SingularInvokingDEPSplitter(SingularSplitterT&& singularSplitter);


		/// \brief Attempts to split a range of expression part math AST nodes.
		/// \param parts The range of expression part nodes to split.
		/// \returns \p parts split by their order of operations, or an empty object if splitting failed.
		std::optional<BasicDEPRecursiveSplitResult<MathAstStringType>> tryToSplit
			(MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts) const
		;


	private:
		std::optional<BasicDEPRecursiveSplitResult<MathAstStringType>> resultPtrToOptional
			(std::unique_ptr<BasicDEPRecursiveSplitResult<MathAstStringType>>& resultPtr) const
		;


		std::unique_ptr<BasicDEPRecursiveSplitResult<MathAstStringType>> tryToSplitAsPtr
			(MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts) const
		;


		std::unique_ptr<BasicDEPRecursiveSplitResult<MathAstStringType>> tryConvertSingleSplitResult
			(const SingularSplitterResultType& singleSplitResult) const
		;

		bool tryConvertSingleSplitResultSide
		(
			MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto singleSplitResultSideParts,
			std::unique_ptr<BasicDEPRecursiveSplitResult<MathAstStringType>>& part
		) const;
	};
}


#include "SingularInvokingDEPSplitter.hpp"