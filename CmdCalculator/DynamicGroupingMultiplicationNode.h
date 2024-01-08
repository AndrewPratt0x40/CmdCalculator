#pragma once

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
		std::ranges::ref_view<std::span<DynamicGroupingNode<StringT>>> getTailMultiplicands() const
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