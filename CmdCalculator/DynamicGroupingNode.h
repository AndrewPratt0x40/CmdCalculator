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
	/// \tparam UnderlyingPartsT The type to use to store the underlying collection of parts of the contained expression.
	template<String StringT, std::ranges::range UnderlyingPartsT>
		requires requires { typename DynamicExpressionContainingNodeWithUnderlyingCollection<StringT, UnderlyingPartsT>; }
	class DynamicGroupingNode :
		public DynamicExpressionContainingNodeWithUnderlyingCollection<StringT, UnderlyingPartsT>
	{
	public:

		using DynamicExpressionContainingNodeWithUnderlyingCollection<StringT, UnderlyingPartsT>::StringType;
		using DynamicExpressionContainingNodeWithUnderlyingCollection<StringT, UnderlyingPartsT>::PartsType;
		using DynamicExpressionContainingNodeWithUnderlyingCollection<StringT, UnderlyingPartsT>::UnderlyingPartsType;


		DynamicExpressionNode<StringT, PartsType> getContainedExpression() const override
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