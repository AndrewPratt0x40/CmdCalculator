#pragma once

#include "DynamicOperandNode.h"
#include "DynamicGroupingNode.h"
#include "strings.h"
#include "NotImplementedException.h"

namespace CmdCalculator::MathAst
{
	/// \brief A multiplication operation using represented by an operand followed by one or more adjacent grouping operations.
	/// \tparam StringT The string type to use.
	/// \tparam TailMultiplicandsT The type to use to store the underlying collection of tail multiplicands.
	template<String StringT, std::ranges::range TailMultiplicandsT>
		requires std::same_as
		<
			DynamicGroupingNode
			<
				typename TailMultiplicandsT::StringType,
				typename TailMultiplicandsT::UnderlyingPartsType
			>,
			std::ranges::range_value_t<TailMultiplicandsT>
		>
	class DynamicGroupingMultiplicationNode :
		public DynamicOperandNode<StringT>
	{
	public:

		/// \brief Accessor to the head multiplicand of the operation.
		/// \returns The operand to be multiplied by the grouping operations that follow it.
		/// \example The head multiplicand of the grouping multiplication expression <tt>1(2)(3)</tt> would be <tt>1</tt>.
		const DynamicOperandNode<StringT>& getHeadMultiplicand() const
		{
			throw NotImplementedException{};
		}


		/// \brief Accessor to the tail multiplicands of the operation.
		/// \returns The grouping operations to multiply the head multiplicand by.
		/// \example The tail multiplicands of the grouping multiplication expression <tt>1(2)(3)</tt> would be <tt>2</tt> and <tt>3</tt>.
		TailMultiplicandsT getTailMultiplicands() const
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