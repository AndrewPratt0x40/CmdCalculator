#pragma once

#include "StreamBasedConsole.h"
#include "NotImplementedException.h"


template<class CharT>
inline CmdCalculator::StreamBasedConsole<CharT>::StreamBasedConsole
(
	std::basic_istream<CharT>& inputStream,
	std::basic_ostream<CharT>& infoStream,
	std::basic_ostream<CharT>& errorStream,
	std::basic_ostream<CharT>& debugStream
)
{
	throw NotImplementedException{};
}


template<class CharT>
inline typename CmdCalculator::StreamBasedConsole<CharT>::StringType
	CmdCalculator::StreamBasedConsole<CharT>::getInput()
{
	throw NotImplementedException{};
}


template<class CharT>
inline void CmdCalculator::StreamBasedConsole<CharT>::write(StringViewType text, const EWriteMode writeMode)
{
	throw NotImplementedException{};
}


template<class CharT>
inline void CmdCalculator::StreamBasedConsole<CharT>::writeLine(StringViewType text, const EWriteMode writeMode)
{
	throw NotImplementedException{};
}