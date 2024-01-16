#pragma once

#include <memory>

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

		using StringType = DynamicOperandNode<StringT>::StringType;


	protected:

		DynamicUnaryOperationNode
		(
			const bool isOperatorOnLeftOfOperand,
			std::unique_ptr<DynamicOperandNode<StringType>> operand,
			const StringType innerTrivia,
			const StringType leadingTrivia,
			const StringType trailingTrivia
		)
		{
			throw NotImplementedException{};
		}


		virtual StringT getOperatorStringRepresentation() const = 0;


	public:


		/// \brief Accessor to the operand of the operation.
		/// \returns The single operand of the operation.
		virtual DynamicOperandNode<StringT>* getOperand() const
		{
			throw NotImplementedException{};
		}
		
		
		/// \brief Accessor to the inner trivia of the operation.
		/// \returns The trivia content between the operator and it's operand.
		virtual StringT getInnerTrivia() const
		{
			throw NotImplementedException{};
		}


		virtual StringT getLeadingTrivia() const override
		{
			throw NotImplementedException{};
		}


		virtual StringT getTrailingTrivia() const override
		{
			throw NotImplementedException{};
		}


		virtual StringT getStringRepresentation() const override
		{
			throw NotImplementedException{};
		}
	};
}