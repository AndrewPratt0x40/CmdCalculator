#pragma once

#include "ExpressionNode.h"
#include "DynamicMathAstNode.h"
#include "DynamicExpressionPartNode.h"
#include "strings.h"
#include "NotImplementedException.h"

#include <algorithm>
#include <ranges>
#include <memory>
#include <utility>
#include <iterator>
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
	public:
		using StringType = DynamicMathAstNode<StringT>::StringType;


	private:
		const StringType m_leadingTrivia;
		const StringType m_trailingTrivia;
		std::vector<std::unique_ptr<DynamicExpressionPartNode<StringType>>> m_parts;

	protected:
		/// \brief Creates a new instance of the \ref DynamicExpressionNode class.
		/// \tparam PartsRangeT The type of the range holding every part of the expression.
		/// \param leadingTrivia Trivial content at the beginning of the string contents of the node.
		/// \param trailingTrivia Trivial content at the end of the string contents of the node.
		/// \param parts A range of every part of the expression, in order.
		template<std::ranges::input_range PartsRangeT>
			requires std::same_as<std::unique_ptr<DynamicExpressionPartNode<StringType>>, std::ranges::range_value_t<PartsRangeT>>
		DynamicExpressionNode
		(
			const StringType leadingTrivia,
			const StringType trailingTrivia,
			std::ranges::owning_view<PartsRangeT>&& parts
		) :
			m_leadingTrivia{ leadingTrivia },
			m_trailingTrivia{ trailingTrivia },
			m_parts{}
		{
			std::ranges::move(parts, std::back_inserter(m_parts));
		}

	public:
		DynamicExpressionNode() = delete;
		DynamicExpressionNode(const DynamicExpressionNode<StringType>&) = delete;
		DynamicExpressionNode(DynamicExpressionNode<StringType>&&) = delete;


		/// \brief Accessor to the parts of the expression.
		/// \returns A range of every part of the expression, in order.
		auto getParts()
		{
			return
				m_parts
				| std::views::transform
				([](std::unique_ptr<DynamicExpressionPartNode<StringType>>& part) { return part.get(); })
			;
		}


		StringType getLeadingTrivia() const override
		{
			throw NotImplementedException{};
		}


		StringType getTrailingTrivia() const override
		{
			throw NotImplementedException{};
		}


		virtual StringType getStringRepresentation() const override
		{
			throw NotImplementedException{};
		}
	};
}