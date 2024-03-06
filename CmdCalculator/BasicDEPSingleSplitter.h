#pragma once

#include <optional>

#include "DynamicExpressionPartSingleSplitter.h"
#include "BasicDEPSingleSplitResult.h"
#include "strings.h"


namespace CmdCalculator
{
	/// \brief A basic implementation that satisfies the \ref DynamicExpressionPartSingleSplitter concept.
	/// \tparam StringT The string type that each expression part node in the math AST uses.
	template<String MathAstStringT>
	class BasicDEPSingleSplitter :
		public DynamicExpressionPartSingleSplitter_IntendedSatisfaction
	{
	public:
		using MathAstStringType = MathAstStringT;


		/// \brief Determines whether or not the splitter can split the given parts.
		/// \param parts The range of parts to examine.
		/// \returns True if the splitter can split \p parts, false otherwise.
		bool canSplit(MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts) const;


		/// \brief Attempts to split a range of expression part math AST nodes.
		/// \param parts The range of expression part nodes to split.
		/// \returns \p parts split by their order of operations once, or an empty object if splitting failed.
		std::optional<BasicDEPSingleSplitResult<MathAstStringT>> tryToSplit(MathAst::DynamicExpressionPartNodeRange<MathAstStringType> auto parts) const;
	};
}


#include "BasicDEPSingleSplitter.hpp"