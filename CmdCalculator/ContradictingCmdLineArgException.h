#pragma once

#include <utility>

#include "BadRawCmdLineArgsException.h"
#include "strings.h"

namespace CmdCalculator
{
	/// \brief An exception that is thrown when two given command-line arguments have contradicting meanings.
	/// \tparam ArgT The type of each object representing the arguments.
	template<String ArgT>
	class ContradictingCmdLineArgException : public BadRawCmdLineArgsException
	{
	private:
		std::pair<ArgT, ArgT> m_args;

	public:
		using ArgType = ArgT;


		/// \brief Creates a new instance of the \ref ContradictingCmdLineArgException class.
		/// \param args The contradicting arguments.
		ContradictingCmdLineArgException(std::pair<ArgT, ArgT> args) :
			m_args{ args }
		{}


		/// \brief Creates a new instance of the \ref ContradictingCmdLineArgException class.
		/// \param arg The first contradicting argument.
		/// \param otherArg The second contradicting argument.
		ContradictingCmdLineArgException(ArgT arg, ArgT otherArg) :
			m_args{ std::make_pair(arg, otherArg) }
		{}


		virtual ~ContradictingCmdLineArgException() = default;


		/// \brief Accessor to the contradicting command-line arguments.
		/// \returns A non-owning view of the contradicting arguments.
		std::pair<ArgType, ArgType> getArgs() const
		{
			return m_args;
		}
	};
}