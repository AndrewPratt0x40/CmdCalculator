#pragma once

#include <concepts>
#include <string>
#include <string_view>
#include <iostream>
#include <functional>
#include <sstream>
#include <assert.h>

#include "StreamBasedConsole.h"
#include "std_polyfills.h"
#include "strings.h"
#include "NotImplementedException.h"


// TODO: Handle io errors instead of just asserting that stream.bad() is false.

namespace
{
	template<char chAs_char, class CharT>
	inline CharT getChar();
	template<class CharT>
	inline CharT getLineFeedChar();
	template<class CharT>
	inline CharT getCarriageReturnChar();


	enum class ENewlineKind
	{
		None,
		CRLF,
		LF,
		CR
	};


	template<class CharT>
	inline bool isNewlineChar(const CharT ch);


	template<class CharT>
	std::basic_string_view<CharT> trimBackChars(const std::basic_string_view<CharT>& str, const size_t count);


	template<class CharT>
	std::basic_string<CharT> readUntilNewlineOrEnd(std::basic_istream<CharT>& istream);


	template<class CharT>
	void writeToStream(std::basic_ostream<CharT>& ostream, std::basic_string_view<CharT> text, const bool appendLineFeed);




	template<char chAs_char, class CharT>
	inline CharT getChar()
	{
		static const CharT ch{ CmdCalculator::convertChar<CharT>(chAs_char) };

		return ch;
	}
	template<class CharT>
	inline CharT getLineFeedChar()
	{
		return getChar<'\n', CharT>();
	}
	template<class CharT>
	inline CharT getCarriageReturnChar()
	{
		return getChar<'\r', CharT>();
	}


	template<class CharT>
	inline bool isNewlineChar(const CharT ch)
	{
		return ch == getLineFeedChar<CharT>() || ch == getCarriageReturnChar<CharT>();
	}


	template<class CharT>
	std::basic_string_view<CharT> trimBackChars(const std::basic_string_view<CharT>& str, const size_t count)
	{
		assert(count <= str.size());
		return str.substr(0, str.size() - count);
	}


	template<class CharT>
	std::basic_string<CharT> readUntilNewlineOrEnd(std::basic_istream<CharT>& istream)
	{
		assert(!istream.bad());

		std::basic_stringstream<CharT> readCharsStream{ "" };

		while (istream.good())
		{
			CharT nextChar{ static_cast<CharT>(istream.get()) };
			assert(!istream.bad());

			if (istream.eof() || isNewlineChar(nextChar))
				break;

			readCharsStream.put(nextChar);
		}

		assert(istream.good() || istream.eof());

		return std::move(readCharsStream).str();
	}


	template<class CharT>
	void writeToStream(std::basic_ostream<CharT>& ostream, std::basic_string_view<CharT> text, const bool appendLineFeed)
	{
		assert(!ostream.bad());

		for (size_t i{ 0 }; i < text.size(); i++)
		{
			const CharT ch{ text[i] };

			if (ch == getCarriageReturnChar<CharT>())
			{
				if (i == text.size() - 1 || text[i + 1] != getLineFeedChar<CharT>())
					ostream.put(getLineFeedChar<CharT>());
			}
			else
				ostream.put(ch);
		}

		if (appendLineFeed)
			ostream.put(getLineFeedChar<CharT>());
	}
}


template<class CharT>
inline CmdCalculator::StreamBasedConsole<CharT>::StreamBasedConsole
(
	std::basic_istream<CharT>& inputStream,
	std::basic_ostream<CharT>& infoStream,
	std::basic_ostream<CharT>& errorStream,
	std::basic_ostream<CharT>& debugStream
) :
	m_inputStream{ std::ref(inputStream) },
	m_infoStream{ std::ref(infoStream) },
	m_errorStream{ std::ref(errorStream) },
	m_debugStream{ std::ref(debugStream) }
{
	assert(!m_inputStream.get().bad());
	assert(!m_infoStream.get().bad());
	assert(!m_errorStream.get().bad());
	assert(!m_debugStream.get().bad());
}


template<class CharT>
inline typename CmdCalculator::StreamBasedConsole<CharT>::StringType
	CmdCalculator::StreamBasedConsole<CharT>::getInput()
{
	assert(!m_inputStream.get().bad());

	return readUntilNewlineOrEnd(m_inputStream.get());
}


template<class CharT>
inline void CmdCalculator::StreamBasedConsole<CharT>::write(StringViewType text, const EWriteMode writeMode)
{
	write(text, writeMode, false);
}


template<class CharT>
inline void CmdCalculator::StreamBasedConsole<CharT>::writeLine(StringViewType text, const EWriteMode writeMode)
{
	const size_t textSize{ text.size() };

	// Note: "Newline character" refers to both LF ('\n') and CR ('\r').

	// If text doesn't end with a newline character, append LF to it.
	if (textSize == 0 || !isNewlineChar(text.back()))
		write(text, writeMode, true);
	// If text is exactly one newline character, treat it as a LF.
	else if (textSize == 1)
	{
		write(text.substr(0, 0), writeMode, true);
	}
	// If text is more than one character and ends with CR, replace the last character with a LF.
	else if (text.back() == getCarriageReturnChar<CharT>())
	{
		write(trimBackChars(text, 1), writeMode, true);
	}
	// If text if more than one character and ends with CRLF, replace the CRLF with a LF.
	else if (text[textSize - 2] == getCarriageReturnChar<CharT>())
	{
		write(trimBackChars(text, 2), writeMode, true);
	}
	// If text if more than one character and ends with LF (and not CRLF), keep it as-is.
	else
	{
		write(text, writeMode, false);
	}
}


template<class CharT>
inline void CmdCalculator::StreamBasedConsole<CharT>::write(StringViewType text, const EWriteMode writeMode, const bool appendLineFeed)
{
	switch (writeMode)
	{
	case EWriteMode::Info:
		assert(!m_infoStream.get().bad());
		writeToStream(m_infoStream.get(), text, appendLineFeed);
		break;
	case EWriteMode::Error:
		assert(!m_errorStream.get().bad());
		writeToStream(m_errorStream.get(), text, appendLineFeed);
		break;
	case EWriteMode::Debug:
		assert(!m_debugStream.get().bad());
		writeToStream(m_debugStream.get(), text, appendLineFeed);
		break;
	default:
		Polyfills::unreachable();
	}
}