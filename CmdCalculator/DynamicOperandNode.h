#pragma once

#include "DynamicExpressionPartNode.h"
#include "strings.h"

namespace CmdCalculator::MathAst
{
	// TODO: This is just RTTI with extra steps. Use double-dispatch or std::visit instead.
	/// \brief Enumerates different types that are derived from \ref DynamicOperandNode.
	enum class EDerivedDynamicOperandNodeKind
	{
		/// \brief A type that is convertible to DynamicNumberLiteralNode
		NumberLiteral,
		/// \brief A type that is convertible to DynamicAbsoluteValueNode
		AbsoluteValue,
		/// \brief A type that is convertible to DynamicGroupingNode
		Grouping,
		/// \brief A type that is convertible to DynamicGroupingMultiplicationNode
		GroupingMultiplication,
		/// \brief A type that is convertible to DynamicSignOperationNode
		SignOperation,
		/// \brief A type that is convertible to DynamicSqrtOperationNode
		SqrtOperation
	};


	/// \brief A node that may be used as an operand for an operation.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicOperandNode :
		public ExpressionPartNode_IntendedSatisfaction,
		public MathAstNode_IntendedSatisfaction,
		public DynamicExpressionPartNode<StringT>
	{
	public:
		using StringType = DynamicExpressionPartNode<StringT>::StringType;


		virtual ~DynamicOperandNode()
		{}


		/// \brief Accessor to the derived type of the operand.
		/// \returns A value representing the derived type of the instance.
		virtual EDerivedDynamicOperandNodeKind getDerivedOperandKind() const = 0;


		inline bool isBinaryOperator() const override
		{
			return false;
		}
	};
}