#pragma once

#include<concepts>
#include<ranges>
#include<vector>
#include<memory>

#include "StringToMathAstConverter.h"
#include "StringToAntlrContextConverter.h"
#include "AntlrContextToMathAstConverter.h"
#include "strings.h"
#include "DynamicExpressionNode.h"
#include "DynamicExpressionPartNode.h"
#include "NotImplementedException.h"

namespace CmdCalculator
{
	/// \brief An algorithm to convert a string into a mathematical abstract syntax tree using ANTLR.
	/// \tparam StringViewT The string view type to convert from.
	/// \tparam StringToAntlrContextConverterT The type to convert strings into ANTLR context objects.
	/// \tparam AntlrContextToMathAstConverter The type to convert ANTLR context objects into mathematical abstract syntax trees.
	template
	<
		StringView StringViewT,
		StringToAntlrContextConverter StringToAntlrContextConverterT,
		AntlrContextToMathAstConverter AntlrContextToMathAstConverterT
	>
	class AntlrBasedStringToMathAstConverter :
		public StringToMathAstConverter_IntendedSatisfaction
	{
	public:
		using StringType = std::basic_string<typename StringViewT::value_type>;
		using StringViewType = StringViewT;

		using StringToAntlrContextConverterType = StringToAntlrContextConverterT;
		using AntlrContextToMathAstConverterType = AntlrContextToMathAstConverterT;


		/// \brief Converts a string into a mathematical abstract syntax tree.
		/// \param source The string to convert.
		/// \returns The root node of the resulting mathematical abstract syntax tree.
		std::unique_ptr<MathAst::DynamicExpressionNode<StringType>> getStringAsMathAst(StringViewType source) const
		{
			throw NotImplementedException{};
		}
		

		/// \brief Creates a new instance of the \ref AntlrBasedStringToMathAstConverter class.
		/// \param stringToAntlrContextConverter The object to convert strings into ANTLR context objects.
		/// \param antlrContextToMathAstConverter The object to convert ANTLR context objects into mathematical abstract syntax trees.
		AntlrBasedStringToMathAstConverter
		(
			StringToAntlrContextConverterType&& stringToAntlrContextConverter,
			AntlrContextToMathAstConverterType&& antlrContextToMathAstConverter
		)
		{
			throw NotImplementedException{};
		}
	};
}