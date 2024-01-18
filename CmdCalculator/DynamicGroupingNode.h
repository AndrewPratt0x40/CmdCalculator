#pragma once

#include "DynamicExpressionContainingNode.h"
#include "strings.h"
#include "NotImplementedException.h"

#include <concepts>
#include <ranges>
#include <utility>

namespace CmdCalculator::MathAst
{
	/// \brief An expression grouped by parentheses.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicGroupingNode :
		public DynamicExpressionContainingNode<StringT>
	{
	public:

		using StringType = DynamicExpressionContainingNode<StringT>::StringType;

		
		DynamicGroupingNode
		(
			std::unique_ptr<DynamicExpressionNode<StringT>> containedExpression,
			StringT leadingTrivia,
			StringT trailingTrivia
		)
		{
			//throw NotImplementedException{};
		}


		DynamicExpressionNode<StringT>* getContainedExpression() const override
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


		virtual StringT getStringRepresentation() const override
		{
			throw NotImplementedException{};
		}
	};
}