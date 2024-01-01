#pragma once

#include<concepts>
#include<ranges>
#include<vector>

#include "StringToMathAstConverter.h"
#include "strings.h"
#include "DynamicExpressionNode.h"
#include "DynamicExpressionPartNode.h"
#include "NotImplementedException.h"

namespace CmdCalculator
{
	/// \brief Enumerates general kinds of mathematical abstract syntax tree nodes that may be attempted to parsed by \ref SequentialMathAstParser.
	enum class EExpectedAstNodeKindToParse
	{
	};
	
	
	/// \brief Enumerates kinds of mathematical abstract syntax tree nodes that may be parsed by \ref SequentialMathAstParser.
	enum class EParsedMathAstNodeKind
	{
		Expression,
		ExpressionPart
	};


	/// \brief The sub-result of one of the parsing steps from \ref SequentialMathAstParser.
	/// StringViewT The string view type that is being parsed for conversion.
	/// NodeT The type of the math AST node that part of the source string was parsed into.
	template<StringView StringViewT, MathAst::MathAstNode NodeT>
	struct SequentialMathAstParsingSubresult
	{
		/// \brief The remaining content of the string to parse.
		StringViewT remainingContent;
		/// \brief The node that was parsed.
		NodeT parsedNode;
		/// \brief The kind of the node that was parsed.
		EParsedMathAstNodeKind parsedNodeKind;
	};



	/// \brief An algorithm to convert a string into a mathematical abstract syntax tree by sequentially parsing the string.
	/// \tparam StringViewT The string view type to convert from.
	template<StringView StringViewT>
	class SequentialMathAstParser :
		public StringToMathAstConverter_IntendedSatisfaction
	{
	private:
		using UnderlyingPartsType = std::vector<MathAst::DynamicExpressionPartNode<StringT>>;

	public:

		using StringType = std::basic_string<typename StringViewT::value_type>;
		using StringViewType = StringViewT;

		/// \brief Converts a string into a mathematical abstract syntax tree.
		/// \param source The string to convert.
		/// \returns The root node of the resulting mathematical abstract syntax tree.
		MathAst::DynamicExpressionNode<StringType, UnderlyingPartsType> getStringAsMathAst(StringViewT source) const
		{
			throw NotImplementedException{};
		}


		
	};
}