#pragma once

#include <memory>

#include "DynamicOperandNode.h"
#include "DynamicGroupingNode.h"
#include "strings.h"
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

		/// \brief Creates a new instance of the \ref DynamicGroupingMultiplicationNode class.
		/// \tparam TailMultiplicandsRangeT The type of the range holding the tail multiplicands of the operation.
		/// \param headMultiplicand The operand to be multiplied by the grouping operations that follow it.
		/// \param tailMultiplicands The grouping operations to multiply the head multiplicand by.
		/// \param leadingTrivia Trivial content at the beginning of the string contents of the node.
		/// \param trailingTrivia Trivial content at the end of the string contents of the node.
		template<std::ranges::input_range TailMultiplicandsRangeT>
			requires std::same_as<std::unique_ptr<MathAst::DynamicGroupingNode<StringT>>, std::ranges::range_value_t<TailMultiplicandsRangeT>>
		DynamicGroupingMultiplicationNode
		(
			std::unique_ptr<DynamicOperandNode<StringT>> headMultiplicand,
			std::ranges::owning_view<TailMultiplicandsRangeT>&& tailMultiplicands,
			const StringT leadingTrivia,
			const StringT trailingTrivia
		)
		{
			throw NotImplementedException{};
		}
		
		
		/// \brief Accessor to the head multiplicand of the operation.
		/// \returns The operand to be multiplied by the grouping operations that follow it.
		/// \example The head multiplicand of the grouping multiplication expression <tt>1(2)(3)</tt> would be <tt>1</tt>.
		const DynamicOperandNode<StringT>* getHeadMultiplicand() const
		{
			throw NotImplementedException{};
		}


		/// \brief Accessor to the tail multiplicands of the operation.
		/// \returns The grouping operations to multiply the head multiplicand by.
		/// \example The tail multiplicands of the grouping multiplication expression <tt>1(2)(3)</tt> would be <tt>2</tt> and <tt>3</tt>.
		std::ranges::owning_view<std::span<DynamicGroupingNode<StringT>*>> getTailMultiplicands() const
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