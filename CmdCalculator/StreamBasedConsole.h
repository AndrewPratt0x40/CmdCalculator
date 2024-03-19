#pragma once

#include <concepts>
#include <string>
#include <string_view>
#include <iostream>
#include <functional>

#include "Console.h"


namespace CmdCalculator
{
	/// \brief A console that reads and writes to stream objects.
	/// \tparam CharT The type of character to use.
	template<class CharT>
	class StreamBasedConsole :
		public Console_IntendedSatisfaction
	{
	public:
		using CharType = CharT;
		using StringType = std::basic_string<CharT>;
		using StringViewType = std::basic_string_view<CharT>;


	private:

		std::reference_wrapper<std::basic_istream<CharT>> m_inputStream;
		std::reference_wrapper<std::basic_ostream<CharT>> m_infoStream;
		std::reference_wrapper<std::basic_ostream<CharT>> m_errorStream;
		std::reference_wrapper<std::basic_ostream<CharT>> m_debugStream;


	public:

		/// \brief Creates a new instance of the \ref StreamBasedConsole class.
		/// \param inputStream The input stream to use.
		/// \param infoStream The output stream to use for info messages.
		/// \param errorStream The output stream to use for error messages.
		/// \param debugStream The output stream to use for debug messages.
		StreamBasedConsole
		(
			std::basic_istream<CharT>& inputStream,
			std::basic_ostream<CharT>& infoStream,
			std::basic_ostream<CharT>& errorStream,
			std::basic_ostream<CharT>& debugStream
		);


		/// \brief Reads a line of text from the input stream.
		/// \returns The next line of text from the input stream.
		StringType getInput();


		/// \brief Writes text to an output stream.
		/// \param text The text to write.
		/// \param writeMode The mode to write in. This determines which output stream to write to.
		void write(StringViewType text, const EWriteMode writeMode);


		/// \brief Writes a line of text to an output stream.
		/// \param text The line of text to write.
		/// \param writeMode The mode to write in. This determines which output stream to write to.
		void writeLine(StringViewType text, const EWriteMode writeMode);


	private:
		void write(StringViewType text, const EWriteMode writeMode, const bool appendLineFeed);
	};
}


#include "StreamBasedConsole.hpp"