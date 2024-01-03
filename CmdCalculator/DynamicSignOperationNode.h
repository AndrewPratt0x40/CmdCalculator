#pragma once

#include "DynamicUnaryOperationNode.h"
#include "strings.h"
#include "NotImplementedException.h"

namespace CmdCalculator::MathAst
{
	/// \brief A sign operation.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicSignOperationNode :
		public DynamicUnaryOperationNode<StringT>
	{
	public:

		using StringType = DynamicOperandNode<StringT>::StringType;


		/// \brief Tests if the sign expression is positive or negative.
		/// \returns True if the sign expression is positive, false if it's negative.
		bool isPositive() const
		{
			throw NotImplementedException{};
		}


		StringT getInnerTrivia() const override
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