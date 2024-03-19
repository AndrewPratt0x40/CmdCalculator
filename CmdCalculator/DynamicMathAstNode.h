#pragma once

#include "MathAstNode.h"
#include "strings.h"

namespace CmdCalculator::MathAst
{
	/// \brief A type that satisfies \ref MathAstNode that is implemented via dynamic polymorphism.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicMathAstNode :
		public MathAstNode_IntendedSatisfaction
	{
	public:

		using StringType = StringT;


		virtual ~DynamicMathAstNode()
		{}


		/// \brief Accessor to the AST node's leading trivia.
		/// \returns Trivial content at the beginning of the string contents of the node.
		virtual StringType getLeadingTrivia() const = 0;


		/// \brief Accessor to the AST node's trailing trivia.
		/// \returns Trivial content at the end of the string contents of the node.
		virtual StringType getTrailingTrivia() const = 0;


		/// \brief Accessor to the AST node's string representation.
		/// \returns All non-trivial string contents of the node.
		virtual StringType getStringRepresentation() const = 0;
	};
}