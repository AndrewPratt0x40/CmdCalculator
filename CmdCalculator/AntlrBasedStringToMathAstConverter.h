#pragma once

#include<concepts>
#include<ranges>
#include<algorithm>
#include<vector>
#include<memory>
#include<string>
#include<string_view>
#include<map>

#include "StringToMathAstConverter.h"
#include "StringToAntlrContextConverter.h"
#include "AntlrContextToMathAstConverter.h"
#include "strings.h"
#include "DynamicExpressionNode.h"
#include "DynamicExpressionPartNode.h"
#include "EmptyInputExpressionException.h"
#include "UnexpectedInputExpressionCharException.h"
#include "NotImplementedException.h"
#include "../submodules/Antlr4CppRuntime/src/RecognitionException.h"
#include "../submodules/Antlr4CppRuntime/src/Token.h"
#include "../submodules/Antlr4CppRuntime/src/misc/IntervalSet.h"
#include "../submodules/Antlr4CppRuntime/src/Recognizer.h"

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


	private:
		StringToAntlrContextConverterType m_stringToAntlrContextConverter;
		AntlrContextToMathAstConverterType m_antlrContextToMathAstConverter;


	public:

		/// \brief Creates a new instance of the \ref AntlrBasedStringToMathAstConverter class.
		/// \param stringToAntlrContextConverter The object to convert strings into ANTLR context objects.
		/// \param antlrContextToMathAstConverter The object to convert ANTLR context objects into mathematical abstract syntax trees.
		AntlrBasedStringToMathAstConverter
		(
			StringToAntlrContextConverterType&& stringToAntlrContextConverter,
			AntlrContextToMathAstConverterType&& antlrContextToMathAstConverter
		) :
			m_stringToAntlrContextConverter{ std::move(stringToAntlrContextConverter) },
			m_antlrContextToMathAstConverter{ std::move(antlrContextToMathAstConverter) }
		{}


		/// \brief Converts a string into a mathematical abstract syntax tree.
		/// \param source The string to convert.
		/// \returns The root node of the resulting mathematical abstract syntax tree.
		/// \throws EmptyInputExpressionException Thrown if \p source is empty.
		/// \throws UnexpectedInputExpressionCharException Thrown if an unexpected character is encountered in \p source.
		std::unique_ptr<MathAst::DynamicExpressionNode<StringType>> getStringAsMathAst(StringViewType source)
		{
			if (static_cast<std::basic_string_view<typename StringViewType::value_type>>(source).empty())
				throw EmptyInputExpressionException{};

			try
			{
				auto fullExpressionContextPtr{ std::move(m_stringToAntlrContextConverter.getStringAsAntlrContext(source)) };
				assert(fullExpressionContextPtr);
				return m_antlrContextToMathAstConverter.getConvertedFullExpressionContext(*fullExpressionContextPtr);
			}
			catch (antlr4::RecognitionException& exception)
			{
				const size_t charIndex{ exception.getOffendingToken()->getStartIndex() };
				antlr4::Recognizer* recognizer{ exception.getRecognizer() };

				if (!recognizer)
				{
					throw UnexpectedInputExpressionCharException{ charIndex };
				}

				const std::map<std::string_view, size_t> tokenTypeMap{ recognizer->getTokenTypeMap() };

				std::ranges::forward_range auto expectedValuesView
				{
					// Get a collection of the token ids of every expected token.
					exception.getExpectedTokens().toList()
					// Convert to a range of iterators to key-value-pairs of tokenTypeMap.
					| std::views::transform
					(
						[&tokenTypeMap](const auto tokenId)
						{
							return std::ranges::find_if
							(
								tokenTypeMap,
								[&tokenId](const auto kvp)
								{ return kvp.second == tokenId; }
							);
						}
					)
					// Filter out any tokens that weren't found.
					| std::views::filter
					(
						[&tokenTypeMap](const auto kvp)
						{ return kvp != tokenTypeMap.end(); }
					)
					// Convert to a range of token names.
					| std::views::transform
					(
						[](const auto kvp)
						{ return std::string{ kvp->first }; }
					)
				};
				static_assert(std::same_as<std::string, std::ranges::range_value_t<decltype(expectedValuesView)>>);

				throw UnexpectedInputExpressionCharException
				{
					charIndex,
					std::move(expectedValuesView)
				};
			}
		}
	};
}