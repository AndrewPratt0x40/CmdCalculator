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


		/// \brief Creates a new instance of the \ref UnknownCmdLineArgException class.
		/// \param arg The unknown argument.
		UnknownCmdLineArgException(ArgT arg) :
			m_arg{arg}
		{}


		virtual ~UnknownCmdLineArgException() = default;


		/// \brief Accessor to the unknown command-line argument.
		/// \returns A non-owning view of the unknown argument.
		ArgType getArg() const
		{
			return m_arg;
		}
	};
}