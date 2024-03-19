#pragma once

#include <memory>
#include <functional>

#include "DynamicExpressionPartRecursiveSplitResult.h"
#include "DynamicExpressionPartNode.h"
#include "strings.h"


namespace CmdCalculator
{
	/// \brief A basic implementation that satisfies the \ref DynamicExpressionPartRecursiveSplitResult concept.
	/// \tparam StringT The string type that each expression part node in the math AST uses.
	template<String MathAstStringT>
	class BasicDEPRecursiveSplitResult :
		public DynamicExpressionPartRecursiveSplitResult_IntendedSatisfaction
	{
	public:
		using MathAstStringType = MathAstStringT;


	private:
		std::unique_ptr<BasicDEPRecursiveSplitResult> m_leftPart;
		std::reference_wrapper<const MathAst::DynamicExpressionPartNode<MathAstStringT>> m_splitPart;
		std::unique_ptr<BasicDEPRecursiveSplitResult> m_rightPart;


	public:
		/// \brief Creates a new instance of the \ref BasicDEPRecursiveSplitResult class.
		/// \param leftPart The split result instance that is to the left of where the expression was split, or nullptr if there is none.
		/// \param splitPart The expression part that the expression was split by.
		/// \param rightPart The split result instance that is to the right of where the expression was split, or nullptr if there is none.
		BasicDEPRecursiveSplitResult
		(
			std::unique_ptr<BasicDEPRecursiveSplitResult> leftPart,
			const MathAst::DynamicExpressionPartNode<MathAstStringT>& splitPart,
			std::unique_ptr<BasicDEPRecursiveSplitResult> rightPart
		);


		/// \brief Accessor to the left part of the split result.
		/// \returns The split result instance that is to the left of where the expression was split, or nullptr if there is none.
		const BasicDEPRecursiveSplitResult* getLeftPart() const;


		/// \brief Accessor to the expression part that the expression was split by.
		/// \returns The expression part that exists between the left and right part.
		const MathAst::DynamicExpressionPartNode<MathAstStringT>& getSplitPart() const;


		/// \brief Accessor to the right part of the split result.
		/// \returns The split result instance that is to the right of where the expression was split, or nullptr if there is none.
		const BasicDEPRecursiveSplitResult* getRightPart() const;
	};
}


#include "BasicDEPRecursiveSplitResult.hpp"