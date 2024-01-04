#pragma once

#include<concepts>
#include<ranges>
#include<vector>
#include<memory>

#include "StringToMathAstConverter.h"
#include "strings.h"
#include "DynamicExpressionNode.h"
#include "DynamicExpressionPartNode.h"
#include "NotImplementedException.h"
//#include "../Antlr4CppRuntime/src/antlr4-runtime.h"
//#include "antlr_output/CmdCalculatorExpressionLexer.h"

namespace CmdCalculator
{
	/// \brief An algorithm to convert a string into a mathematical abstract syntax tree using ANTLR.
	/// \tparam StringViewT The string view type to convert from.
	template<StringView StringViewT>
	class AntlrBasedStringToMathAstConverter :
		public StringToMathAstConverter_IntendedSatisfaction
	{
	public:
		using StringType = std::basic_string<typename StringViewT::value_type>;
		using StringViewType = StringViewT;

	private:
		using UnderlyingPartsType = std::vector<std::unique_ptr<MathAst::DynamicExpressionPartNode<StringType>>>;

		/// \brief Converts a string into a mathematical abstract syntax tree.
		/// \param source The string to convert.
		/// \returns The root node of the resulting mathematical abstract syntax tree.
		MathAst::DynamicExpressionNode<StringType, UnderlyingPartsType> getStringAsMathAst(StringViewT source) const
		{
			throw NotImplementedException{};
		}
		
	};
}