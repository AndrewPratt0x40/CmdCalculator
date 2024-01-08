#pragma once

#include "DynamicExpressionContainingNode.h"
#include "strings.h"
#include "NotImplementedException.h"

#include <concepts>
#include <ranges>
#include <utility>

namespace CmdCalculator::MathAst
{
	/// \brief An absolute value operation expression.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicAbsoluteValueNode :
		public DynamicExpressionContainingNode<StringT>
	{
	public:

		using StringType = DynamicExpressionContainingNode<StringT>::StringType;


		DynamicExpressionNode<StringT> getContainedExpression() const override
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