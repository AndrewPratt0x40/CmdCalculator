#pragma once

#include "DynamicOperandNode.h"
#include "DynamicExpressionNode.h"
#include "strings.h"

#include <concepts>
#include <ranges>
#include <utility>

namespace CmdCalculator::MathAst
{
	/// \brief A node that holds an expression inside of it.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicExpressionContainingNode :
		public DynamicOperandNode<StringT>
	{
	public:
		
		using StringType = DynamicOperandNode<StringT>::StringType;


		virtual ~DynamicExpressionContainingNode()
		{}

		/// \brief Accessor to the contained expression.
		/// \returns The expression contained within the node.
		virtual DynamicExpressionNode<StringT>* getContainedExpression() const = 0;
	};
}