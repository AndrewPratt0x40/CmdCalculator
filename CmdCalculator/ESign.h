#pragma once


namespace CmdCalculator::Arithmetic
{
	/// \brief Enumerates the different sign kinds a signed value may have.
	enum class ESign
	{
		/// \brief A neutrally-signed value, i.e. zero.
		Neutral,
		/// \brief A positively-signed value, i.e. greater than zero.
		Positive,
		/// \brief A negatively-signed value, i.e. less than zero.
		Negative
	};
}