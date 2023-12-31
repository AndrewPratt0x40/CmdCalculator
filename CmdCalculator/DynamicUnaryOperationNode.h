#pragma once

#include "DynamicOperandNode.h"
#include "strings.h"
#include "NotImplementedException.h"

namespace CmdCalculator::MathAst
{
	/// \brief A unary operation.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicUnaryOperationNode :
		public DynamicOperandNode<StringT>
	{
	public:

		using DynamicOperandNode<StringT>::StringType;


		/// \brief Accessor to the operand of the operation.
		/// \returns The single operand of the operation.
		virtual DynamicOperandNode<StringT>& getOperand() const = 0;
		
		
		/// \brief Accessor to the inner trivia of the operation.
		/// \returns The trivia content between the operator and it's operand.
		virtual StringT getInnerTrivia() const = 0;
	};
}