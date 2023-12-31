#pragma once

#include "ExpressionNode.h"
#include "DynamicMathAstNode.h"
#include "DynamicExpressionPartNode.h"
#include "strings.h"

#include <ranges>

namespace CmdCalculator::MathAst
{
	/// \brief A type that satisfies \ref ExpressionNode that is implemented via dynamic polymorphism.
	/// \tparam StringT The string type to use.
	/// \tparam PartsT The type to use for accessing the collection of all parts of the expression.
	template<String StringT, std::ranges::input_range PartsT>
		requires std::same_as<DynamicExpressionPartNode<StringT>, std::ranges::range_value_t<PartsT>>
	class DynamicExpressionNode :
		public ExpressionNode_IntendedSatisfaction,
		public DynamicMathAstNode<StringT>
	{
		/// \brief Accessor to the parts of the expression.
		/// \returns A range of every part of the expression, in order.
		virtual PartsT getParts() const = 0;
	};
}