#pragma once

#include "DynamicUnaryOperationNode.h"
#include "strings.h"
#include "NotImplementedException.h"

namespace CmdCalculator::MathAst
{
	/// \brief A square root operation.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicSqrtOperationNode :
		public DynamicUnaryOperationNode<StringT>
	{
	public:

		using StringType = DynamicOperandNode<StringT>::StringType;


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