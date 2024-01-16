#pragma once

#include "ExpressionNode.h"
#include "DynamicMathAstNode.h"
#include "DynamicExpressionPartNode.h"
#include "strings.h"
#include "NotImplementedException.h"

#include <ranges>
#include <memory>
#include <utility>
#include <vector>

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
		/// \tparam PartsRangeT The type of the range holding every part of the expression.
		/// \param leadingTrivia Trivial content at the beginning of the string contents of the node.
		/// \param trailingTrivia Trivial content at the end of the string contents of the node.
		/// \param parts A range of every part of the expression, in order.
		template<std::ranges::input_range PartsRangeT>
			requires std::same_as<std::unique_ptr<MathAst::DynamicExpressionPartNode<StringT>>, std::ranges::range_value_t<PartsRangeT>>
		DynamicExpressionNode
		(
			const StringT leadingTrivia,
			const StringT trailingTrivia,
			const std::ranges::owning_view<PartsRangeT>&& parts
		)
		{
			throw NotImplementedException{};
		}

	public:
		/// \brief Accessor to the parts of the expression.
		/// \returns A range of every part of the expression, in order.
		std::ranges::owning_view<std::span<MathAst::DynamicExpressionPartNode<StringT>*>> getParts() const
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


		virtual StringT getStringRepresentation() const override
		{
			throw NotImplementedException{};
		}
	};
}