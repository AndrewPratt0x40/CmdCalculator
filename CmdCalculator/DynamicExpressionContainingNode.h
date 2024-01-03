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
	/// \tparam PartsT The type to use for accessing the collection of all parts of the contained expression.
	template<String StringT, std::ranges::input_range PartsT>
		requires std::same_as<DynamicExpressionPartNode<StringT>, std::ranges::range_value_t<PartsT>>
	class DynamicExpressionContainingNode :
		public DynamicOperandNode<StringT>
	{
	public:
		
		using StringType = DynamicOperandNode<StringT>::StringType;

		using PartsType = PartsT;

		/// \brief Accessor to the contained expression.
		/// \returns The expression contained within the node.
		virtual DynamicExpressionNode<StringT, PartsT> getContainedExpression() const = 0;
	};


	/// \brief A base class for types that subclass \ref DynamicExpressionContainingNode that are implemented via an underlying collection of a given type to store all parts of the contained expression.
	/// \tparam StringT The string type to use.
	/// \tparam UnderlyingPartsT The type to use to store the underlying collection of parts of the contained expression.
	template<String StringT, std::ranges::range UnderlyingPartsT>
		requires requires { typename std::ranges::owning_view<UnderlyingPartsT>; }
	class DynamicExpressionContainingNodeWithUnderlyingCollection :
		public DynamicExpressionContainingNode<StringT, decltype(std::declval<UnderlyingPartsT> | std::views::all)>
	{
	private:
		using ParentDynamicExpressionContainingNode = DynamicExpressionContainingNode<StringT, decltype(std::declval<UnderlyingPartsT> | std::views::all)>;

	public:
		using StringType = ParentDynamicExpressionContainingNode::StringType;
		using PartsType = ParentDynamicExpressionContainingNode::PartsType;

		using UnderlyingPartsType = UnderlyingPartsT;
	};
}