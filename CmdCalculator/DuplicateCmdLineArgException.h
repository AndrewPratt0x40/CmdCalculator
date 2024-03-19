#pragma once

#include "BadRawCmdLineArgsException.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief An exception that is thrown when the same command-line argument is given several times.
	/// \tparam ArgT The type of the object representing the duplicated argument.
	template<String ArgT>
	class DuplicateCmdLineArgException : public BadRawCmdLineArgsException
	{
	private:
		ArgT m_arg;

	public:
		using ArgType = ArgT;


		/// \brief Creates a new instance of the \ref DuplicateCmdLineArgException class.
		/// \param arg The missing argument.
		DuplicateCmdLineArgException(ArgT arg) :
			m_arg{ arg }
		{}


		virtual ~DuplicateCmdLineArgException() = default;


		/// \brief Accessor to the duplicated command-line argument.
		/// \returns A non-owning view of the duplicated argument.
		ArgType getArg() const
		{
			return m_arg;
		}
	};
}