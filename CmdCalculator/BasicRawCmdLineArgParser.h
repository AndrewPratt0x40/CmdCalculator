#pragma once

#include "RawCmdLineArgParser.h"
#include "MissingCmdLineArgValueException.h"
#include "DuplicateCmdLineArgException.h"
#include "ContradictingCmdLineArgException.h"
#include "UnknownCmdLineArgException.h"
#include "strings.h"


namespace CmdCalculator
{
	/// \brief A basic implementation of the \ref RawCmdLineArgParser concept.
	/// \tparam ExpressionStringT The string type that represents expressions.
	template<String ExpressionStringT>
	class BasicRawCmdLineArgParser :
		public RawCmdLineArgParser_IntendedSatisfaction
	{
	public:
		using ExpressionStringType = ExpressionStringT;


		/// \brief Parses raw command line arguments.
		/// \param rawCmdLineArgs The raw command line arguments to parse.
		/// \param defaultConfiguration The configuration to fallback to for values not given by \p rawCmdLineArgs.
		/// \returns A \ref ProcessConfiguration instance representing the parsed information.
		/// \throws MissingCmdLineArgValueException if an argument that should have a value doesn't have one.
		/// \throws DuplicateCmdLineArgException if the same argument is given more than once.
		/// \throws ContradictingCmdLineArgException if two arguments contradict each other.
		/// \throws UnknownCmdLineArgException if an unknown argument is present.
		ProcessConfiguration<ExpressionStringT> parseRawCmdLineArgs
		(
			StringForwardRange auto rawCmdLineArgs,
			const ProcessConfiguration<ExpressionStringT>& defaultConfiguration
		) const
			requires
				std::convertible_to
				<
					std::ranges::range_value_t<decltype(rawCmdLineArgs)>,
					ExpressionStringT
				>
		;
	};
}


#include "BasicRawCmdLineArgParser.hpp"