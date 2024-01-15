#pragma once

#include "ExpressionNode.h"
#include "DynamicMathAstNode.h"
#include "DynamicExpressionPartNode.h"
#include "strings.h"
#include "NotImplementedException.h"

#include <ranges>
#include <span>
#include <memory>

namespace CmdCalculator::MathAst
{
	/// \brief A type that satisfies \ref ExpressionNode that is implemented via dynamic polymorphism.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicExpressionNode :
		public ExpressionNode_IntendedSatisfaction,
		public MathAstNode_IntendedSatisfaction,
		public DynamicMathAstNode<StringT>
	{
	protected:
		/// \brief Creates a new instance of the \ref DynamicExpressionNode class.
		/// \param leadingTrivia Trivial content at the beginning of the string contents of the node.
		/// \param trailingTrivia Trivial content at the end of the string contents of the node.
		/// \param parts A range of every part of the expression, in order.
		DynamicExpressionNode
		(
			const StringT leadingTrivia,
			const StringT trailingTrivia,
			const std::span<MathAst::DynamicExpressionPartNode<StringT>*>&& parts
		)
		{
			throw NotImplementedException{};
		}

	public:
		/// \brief Accessor to the parts of the expression.
		/// \returns A range of every part of the expression, in order.
		std::ranges::ref_view<std::span<MathAst::DynamicExpressionPartNode<StringT>*>> getParts() const
		{
			throw NotImplementedException{};
		}


		StringT getLeadingTrivia() const override
		{
			throw NotImplementedException{};
		}


		StringT getTrailingTrivia() const override
		{
			throw NotImplementedException{};
		}


		StringT getStringRepresentation() const override
		{
			throw NotImplementedException{};
		}
	};
}