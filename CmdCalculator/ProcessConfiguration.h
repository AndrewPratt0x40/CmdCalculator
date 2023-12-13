#pragma once

#include <optional>

#include "strings.h"
#include "CalculationConfiguration.h"

namespace CmdCalculator
{
	/// \brief A configuration for a CmdCalculator process.
	/// \tparam String The data type to store strings with.
	template<String StringT>
	struct ProcessConfiguration
	{
		/// \brief The expression given to CmdCalculator to calculate, if any.
		std::optional<StringT> givenExpression;

		/// \brief The calculation configuration to use.
		CalculationConfiguration CalculationConfiguration;
	};
}