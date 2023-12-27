#pragma once

#include <string_view>

#include "BadRawCmdLineArgsException.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief An exception that is thrown when an unknown command-line argument is given.
	/// \tparam ArgT The type of the object representing the unknown argument.
	template<String ArgT>
	class UnknownCmdLineArgException : public BadRawCmdLineArgsException
	{
	private:
		ArgT m_arg;

	public:
		using ArgType = ArgT;
		using ArgViewType = std::basic_string_view<typename ArgType::value_type>;


		/// \brief Creates a new instance of the \ref UnknownCmdLineArgException class.
		/// \param arg The unknown argument.
		UnknownCmdLineArgException(ArgT arg) :
			m_arg{arg}
		{}


		/// \brief Accessor to the unknown command-line argument.
		/// \returns A non-owning view of the unknown argument.
		ArgViewType getArg() const
		{
			return m_arg;
		}
	};
}