#pragma once

#include "ExpressionNode.h"
#include "DynamicMathAstNode.h"
#include "DynamicExpressionPartNode.h"
#include "strings.h"
#include "std_polyfills.h"
#include "NotImplementedException.h"

#include <algorithm>
#include <ranges>
#include <memory>
#include <utility>
#include <iterator>
#include <format>
#include <vector>
#include<locale>
#include<assert.h>

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

	public:

		/// \brief Creates a new instance of the \ref DynamicExpressionNode class.
		/// \tparam PartsRangeT The type of the range holding every part of the expression.
		/// \param leadingTrivia Trivial content at the beginning of the string contents of the node.
		/// \param trailingTrivia Trivial content at the end of the string contents of the node.
		/// \param parts A range of every part of the expression, in order.
		template<std::ranges::forward_range PartsRangeT>
			requires std::convertible_to<std::unique_ptr<DynamicExpressionPartNode<StringType>>, std::ranges::range_value_t<PartsRangeT>>
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


		DynamicExpressionNode() = delete;
		DynamicExpressionNode(const DynamicExpressionNode<StringType>&) = delete;
		DynamicExpressionNode(DynamicExpressionNode<StringType>&&) = delete;


		virtual ~DynamicExpressionNode() override = default;


		/// \brief Accessor to the parts of the expression.
		/// \returns A range of every part of the expression, in order.
		DynamicExpressionPartNodeRange<StringType> auto getParts() const
		{
			return
				m_parts
				| std::views::transform
				(
					[](const std::unique_ptr<DynamicExpressionPartNode<StringType>>& part)
					{ return std::ref<DynamicExpressionPartNode<StringType>>(*part); }
				)
			;
		}


		StringType getLeadingTrivia() const override
		{
			return m_leadingTrivia;
		}


		StringType getTrailingTrivia() const override
		{
			return m_trailingTrivia;
		}


		virtual StringType getStringRepresentation() const override
		{
			using StdStringType = std::basic_string<typename StringType::value_type>;
			
			return static_cast<StringType>
			(
				Polyfills::ranges::fold_left
				(
					getParts()
					| std::views::transform
					(
						[](const DynamicExpressionPartNode<StringType>& part)
						{ return static_cast<StdStringType>(part.getStringRepresentation()); }
					),
					static_cast<StdStringType>(getLeadingTrivia()),
					std::plus()
				)
				+ static_cast<StdStringType>(getTrailingTrivia())
			);
		}
	};


	template<String StringT>
	using DynamicExpressionNodesGetPartsReturnType =
		decltype(std::declval<DynamicExpressionNode<StringT>>().getParts())
	;


	/// \brief A view of \ref DynamicExpressionPartNode instances stored within a \ref DynamicExpressionNode instance.
	/// \tparam StringT The string type used by the instances.
	template<String StringT>
	using DynamicExpressionNodePartsView =
		std::ranges::subrange
		<
			std::ranges::iterator_t<DynamicExpressionNodesGetPartsReturnType<StringT>>,
			std::ranges::sentinel_t<DynamicExpressionNodesGetPartsReturnType<StringT>>
		>
	;
}