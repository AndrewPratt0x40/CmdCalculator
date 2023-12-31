#pragma once

#include "ExpressionPartNode.h"
#include "DynamicMathAstNode.h"
#include "strings.h"

namespace CmdCalculator::MathAst
{
	/// \brief A type that satisfies \ref ExpressionPartNode that is implemented via dynamic polymorphism.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicExpressionPartNode :
		public ExpressionPartNode_IntendedSatisfaction,
		public DynamicMathAstNode<StringT>
	{
	public:
		using DynamicMathAstNode<StringT>::StringType;
	};
}