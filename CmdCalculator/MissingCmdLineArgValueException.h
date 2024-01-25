#pragma once

#include <string_view>

#include "BadRawCmdLineArgsException.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief An exception that is thrown when a command-line argument is missing a value.
	/// \tparam ArgT The type of the object representing the argument missing it's value.
	template<String ArgT>
	class MissingCmdLineArgValueException : public BadRawCmdLineArgsException
	{
	private:
		ArgT m_arg;

	public:
		using ArgType = ArgT;


		/// \brief Creates a new instance of the \ref MissingCmdLineArgValueException class.
		/// \param arg The missing argument.
		MissingCmdLineArgValueException(ArgT arg) :
			m_arg{ arg }
		{}


		/// \brief Accessor to the missing command-line argument.
		/// \returns A non-owning view of the missing argument.
		ArgType getArg() const
		{
			return m_arg;
		}
	};
}