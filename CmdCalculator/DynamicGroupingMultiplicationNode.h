#pragma once

#include <memory>
#include <vector>
#include <ranges>
#include <algorithm>
#include <assert.h>
#include <iterator>

#include "DynamicOperandNode.h"
#include "DynamicGroupingNode.h"
#include "strings.h"
#include "std_polyfills.h"
#include "NotImplementedException.h"

namespace CmdCalculator::MathAst
{
	/// \brief A multiplication operation using represented by an operand followed by one or more adjacent grouping operations.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicGroupingMultiplicationNode :
		public DynamicOperandNode<StringT>
	{
	public:
		using StringType = DynamicOperandNode<StringT>::StringType;

	private:
		const std::unique_ptr<DynamicOperandNode<StringType>> m_headMultiplicand;
		std::vector<std::unique_ptr<DynamicGroupingNode<StringType>>> m_tailMultiplicands;
		const StringType m_leadingTrivia;
		const StringType m_trailingTrivia;

	public:

		virtual ~DynamicGroupingMultiplicationNode() = default;


		/// \brief Creates a new instance of the \ref DynamicGroupingMultiplicationNode class.
		/// \tparam TailMultiplicandsRangeT The type of the range holding the tail multiplicands of the operation.
		/// \param headMultiplicand The operand to be multiplied by the grouping operations that follow it.
		/// \param tailMultiplicands The grouping operations to multiply the head multiplicand by.
		/// \param leadingTrivia Trivial content at the beginning of the string contents of the node.
		/// \param trailingTrivia Trivial content at the end of the string contents of the node.
		template<std::ranges::forward_range TailMultiplicandsRangeT>
			requires std::same_as<std::unique_ptr<MathAst::DynamicGroupingNode<StringType>>, std::ranges::range_value_t<TailMultiplicandsRangeT>>
		DynamicGroupingMultiplicationNode
		(
			std::unique_ptr<DynamicOperandNode<StringType>> headMultiplicand,
			std::ranges::owning_view<TailMultiplicandsRangeT>&& tailMultiplicands,
			const StringType leadingTrivia,
			const StringType trailingTrivia
		) :
			m_headMultiplicand{ std::move(headMultiplicand) },
			m_tailMultiplicands{},
			m_leadingTrivia{ leadingTrivia },
			m_trailingTrivia{ trailingTrivia }
		{
			assert(m_headMultiplicand);
			std::ranges::move(tailMultiplicands, std::back_inserter(m_tailMultiplicands));
		}


		inline EDerivedDynamicOperandNodeKind getDerivedOperandKind() const override
		{
			return EDerivedDynamicOperandNodeKind::GroupingMultiplication;
		}
		
		
		/// \brief Accessor to the head multiplicand of the operation.
		/// \returns The operand to be multiplied by the grouping operations that follow it.
		/// \example The head multiplicand of the grouping multiplication expression <tt>1(2)(3)</tt> would be <tt>1</tt>.
		const DynamicOperandNode<StringType>* getHeadMultiplicand() const
		{
			return m_headMultiplicand.get();
		}


		/// \brief Accessor to the tail multiplicands of the operation.
		/// \returns The grouping operations to multiply the head multiplicand by.
		/// \example The tail multiplicands of the grouping multiplication expression <tt>1(2)(3)</tt> would be <tt>2</tt> and <tt>3</tt>.
		std::ranges::forward_range auto getTailMultiplicands() const
		{
			return
				m_tailMultiplicands
				| std::views::transform
				([](const std::unique_ptr<DynamicGroupingNode<StringType>>& tailMultiplicand) { return tailMultiplicand.get(); })
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


		StringType getStringRepresentation() const override
		{
			using StdStringType = std::basic_string<typename StringType::value_type>;
			
			return static_cast<StringType>
			(
				static_cast<StdStringType>(getLeadingTrivia())
				+ Polyfills::ranges::fold_left
				(
					getTailMultiplicands()
					| std::views::transform
					(
						[](const auto* tailMultiplicand)
						{ return static_cast<StdStringType>(tailMultiplicand->getStringRepresentation()); }
					),
					static_cast<StdStringType>(getHeadMultiplicand()->getStringRepresentation()),
					std::plus()
				)
				+ static_cast<StdStringType>(getTrailingTrivia())
			);
		}
	};
}