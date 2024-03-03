#pragma once

#include <memory>
#include <functional>

#include "DynamicExpressionPartSingleSplitResult.h"
#include "DynamicExpressionPartNode.h"
#include "strings.h"


namespace CmdCalculator
{
	/// \brief A basic implementation that satisfies the \ref DynamicExpressionPartSingleSplitResult concept.
	/// \tparam StringT The string type that each expression part node in the math AST uses.
	template<String MathAstStringT>
	class BasicDEPSingleSplitResult :
		public DynamicExpressionPartSingleSplitResult_IntendedSatisfaction
	{
	public:
		using MathAstStringType = MathAstStringT;


	private:
		using PartRefType = std::reference_wrapper<const MathAst::DynamicExpressionPartNode<MathAstStringType>>;
		using PartRefVectorType = std::vector<PartRefType>;

		PartRefVectorType m_leftParts;
		PartRefType m_splitPart;
		PartRefVectorType m_rightParts;


		PartRefVectorType createPartRefVector(MathAst::DynamicExpressionPartNodeRange<MathAstStringT> auto parts);


	public:
		using PartRefView = std::ranges::ref_view<const PartRefVectorType>;


		/// \brief Creates a new instance of the \ref BasicDEPSingleSplitResult class.
		/// \param leftParts A range of expression part nodes that are to the left of where the expression was split.
		/// \param splitPart The expression part that the expression was split by.
		/// \param rightPart A range of expression part nodes that are to the right of where the expression was split.
		BasicDEPSingleSplitResult
		(
			MathAst::DynamicExpressionPartNodeRange<MathAstStringT> auto leftParts,
			const MathAst::DynamicExpressionPartNode<MathAstStringT>& splitPart,
			MathAst::DynamicExpressionPartNodeRange<MathAstStringT> auto rightParts
		);


		/// \brief Accessor to the left parts of the split result.
		/// \returns A range of expression part nodes that are to the left of where the expression was split.
		PartRefView getLeftParts() const;


		/// \brief Accessor to the expression part that the expression was split by.
		/// \returns The expression part that exists between the left and right part.
		const MathAst::DynamicExpressionPartNode<MathAstStringT>& getSplitPart() const;


		/// \brief Accessor to the right parts of the split result.
		/// \returns A range of expression part nodes that are to the right of where the expression was split.
		PartRefView getRightParts() const;
	};
}


#include "BasicDEPSingleSplitResult.hpp"