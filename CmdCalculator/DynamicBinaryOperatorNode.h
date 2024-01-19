#pragma once

#include "DynamicExpressionPartNode.h"
#include "EBinaryOperator.h"
#include "strings.h"
#include "NotImplementedException.h"

namespace CmdCalculator::MathAst
{
	/// \brief A node holding a binary operator.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicBinaryOperatorNode :
		public DynamicExpressionPartNode<StringT>
	{
	public:

		virtual ~DynamicBinaryOperatorNode() = default;


		DynamicBinaryOperatorNode(const EBinaryOperator operatorKind, const StringT leadingTrivia, const StringT trailingTrivia)
		{
			throw NotImplementedException{};
		}


		/// \brief Accessor to the kind of operator the node holds.
		/// \returns The operator kind.
		EBinaryOperator getOperatorKind() const
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