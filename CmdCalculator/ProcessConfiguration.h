#pragma once

#include <optional>

#include "strings.h"
#include "CalculationConfiguration.h"

namespace CmdCalculator
{
	/// \brief A collection of settings for a CmdCalculator process.
	/// \tparam ExpressionStringT The string type that represents a given expression.
	template<String ExpressionStringT>
	struct ProcessConfiguration
	{
		/// \brief The given expression to calculate, if any.
		/// \details If this value is empty, the user will be prompted to enter an expression instead.
		std::optional<ExpressionStringT> givenExpression;

		/// \brief The configuration to use for calculation.
		CalculationConfiguration calculationConfiguration;
	};
}