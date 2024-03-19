#pragma once

#include "ExpressionPartNode.h"
#include "DynamicMathAstNode.h"
#include "strings.h"

namespace CmdCalculator::MathAst
{
	template<String StringT>
	class DynamicExpressionPartNode;


	/// \brief A range of polymorphic \ref DynamicExpressionPartNode instances.
	/// \tparam T The range type.
	/// \tparam StringT The string type that each expression part node uses.
	template<class T, class StringT>
	concept DynamicExpressionPartNodeRange =
		String<StringT>
		&& std::ranges::forward_range<T>
		&& std::convertible_to
		<
			std::ranges::range_value_t<T>,
			const DynamicExpressionPartNode<StringT>&
		>
	;


	/// \brief A type that satisfies \ref ExpressionPartNode that is implemented via dynamic polymorphism.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicExpressionPartNode :
		public ExpressionPartNode_IntendedSatisfaction,
		public MathAstNode_IntendedSatisfaction,
		public DynamicMathAstNode<StringT>
	{
	public:
		using StringType = DynamicMathAstNode<StringT>::StringType;


		virtual ~DynamicExpressionPartNode()
		{}


		/// \brief Tests if the node is a binary operator or not.
		/// \returns True if the node is a binary operator, false otherwise.
		/// \remark If this method returns true, it is assumed that the instance is convertible to \ref MathAst::DynamicBinaryOperatorNode.
		/// \remark If this method returns false, it is assumed that the instance is convertible to \ref MathAst::DynamicOperandNode.
		virtual bool isBinaryOperator() const = 0;
	};
}