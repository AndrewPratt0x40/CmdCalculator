#pragma once

#include "DynamicExpressionPartNode.h"
#include "strings.h"

namespace CmdCalculator::MathAst
{
	/// \brief A node that may be used as an operand for an operation.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicOperandNode :
		public DynamicExpressionPartNode<StringT>
	{
	public:
		using DynamicExpressionPartNode<StringT>::StringType;
	};
}