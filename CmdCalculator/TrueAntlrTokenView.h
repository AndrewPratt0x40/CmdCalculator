#pragma once

#include <concepts>
#include <exception>

#include "AntlrToken.h"
#include "strings.h"
#include "../submodules/Antlr4CppRuntime/src/Token.h"
#include "NotImplementedException.h"


namespace CmdCalculator
{
	/// \brief A non-owning view of a \ref antlr4::Token instance.
	class TrueAntlrTokenView :
		public AntlrToken_IntendedSatisfaction
	{
	public:
		using StringType = decltype(std::declval<antlr4::Token>().getText());
		static_assert(String<StringType>);

		using StartIndexType = decltype(std::declval<antlr4::Token>().getStartIndex());
		static_assert(std::convertible_to<StartIndexType, size_t>);

		using StopIndexType = decltype(std::declval<antlr4::Token>().getStopIndex());
		static_assert(std::convertible_to<StopIndexType, size_t>);

	private:
		const antlr4::Token* m_token;


	public:
		/// \brief Creates a new instance of the \ref TrueAntlrTokenView class.
		/// \param token The token instance to view.
		TrueAntlrTokenView(const antlr4::Token* token);


		/// \brief Accessor to the token's text.
		/// \returns The text representing the token.
		StringType getText() const;


		/// \brief Accessor to the token's start index.
		/// \returns The index of the first character of the token in the source text the token is from.
		StartIndexType getStartIndex() const;


		/// \brief Accessor to the token's stop index.
		/// \returns The index of the last character of the token in the source text the token is from.
		StopIndexType getStopIndex() const;
	};


	static_assert(AntlrToken<TrueAntlrTokenView>);
}