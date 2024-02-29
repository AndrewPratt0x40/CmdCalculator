#pragma once

#include <optional>

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


	private:
		// TODO


	public:
		/// \brief Creates a new instance of the \ref SingularInvokingDEPSplitter class.
		/// \param singularSplitter The singular splitter to use.
		SingularInvokingDEPSplitter(SingularSplitterT&& singularSplitter);


		/// \brief Attempts to split a range of expression part math AST nodes.
		/// \param parts The range of expression part nodes to split.
		/// \returns \p parts split by their order of operations, or an empty object if splitting failed.
		std::optional<BasicDEPRecursiveSplitResult<MathAstStringType>> tryToSplit
			(MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts);
	};
}


#include "SingularInvokingDEPSplitter.hpp"