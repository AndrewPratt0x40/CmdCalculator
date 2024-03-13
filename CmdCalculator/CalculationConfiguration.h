#pragma once
#include <stdexcept>

namespace CmdCalculator
{
	/// \brief A collection of settings for how calculations should be done.
	class CalculationConfiguration
	{
	private:
		/// \brief How many decimal places are to be included in the answer of a calculation.
		int m_precision;

		/// \brief True if integers should have decimal points in the answer of a calculation, false if integers should have no decimal points.
		bool m_shouldPreferDecimalsOverIntegers;

		/// \brief True if positive values should be displayed as a sign expression in the answer of a calculation, false if positive values should stay as-is.
		bool m_shouldPreferSignExpressionForPositiveValues;

		/// \brief True if numbers with an absolute value greater than zero and less than one should be shown with a leading zero before the decimal point in the answer of a calculation, false to show nothing before the decimal point.
		bool m_shouldPreferLeadingZeroOverWholelessNumbers;

		/// \brief True if integers should be shown with a trailing zero after the decimal point in the answer of a calculation, false to show nothing after the decimal point.
		bool m_shouldPreferTrailingZeroOverEmptyDecimalPlace;

	public:
		/// \brief Accessor for the preferred precision.
		/// \returns How many decimal places are to be included in the answer of a calculation.
		int getPrecision() const;


		/// \brief Accessor for the preferred representation of integers.
		/// \returns True if integers should have decimal points in the answer of a calculation, false if integers should have no decimal points.
		bool shouldPreferDecimalsOverIntegers() const;


		/// \brief Accessor for the preferred representation of positive values.
		/// \returns True if positive values should be displayed as a sign expression in the answer of a calculation, false if positive values should stay as-is.
		bool shouldPreferSignExpressionForPositiveValues() const;


		/// \brief Accessor for the preferred representation of leading zeros.
		/// \returns True if numbers with an absolute value greater than zero and less than one should be shown with a leading zero before the decimal point in the answer of a calculation, false to show nothing before the decimal point.
		bool shouldPreferLeadingZeroOverWholelessNumbers() const;


		/// \brief Accessor for the preferred representation of trailing zeros.
		/// \returns True if integers should be shown with a trailing zero after the decimal point in the answer of a calculation, false to show nothing after the decimal point.
		bool shouldPreferTrailingZeroOverEmptyDecimalPlace() const;


		/// \brief Creates a new instance of the \ref CalculationConfiguration class.
		/// \param[in] precision How many decimal places are to be included in the answer of a calculation.
		/// \param[in] shouldPreferDecimalsOverIntegers True if integers should have decimal points in the answer of a calculation, false if integers should have no decimal points.
		/// \param[in] shouldPreferSignExpressionForPositiveValues True if positive values should be displayed as a sign expression in the answer of a calculation, false if positive values should stay as-is.
		/// \param[in] shouldPreferLeadingZeroOverWholelessNumbers True if numbers with an absolute value greater than zero and less than one should be shown with a leading zero before the decimal point in the answer of a calculation, false to show nothing before the decimal point.
		/// \param[in] shouldPreferTrailingZeroOverEmptyDecimalPlace True if integers should be shown with a trailing zero after the decimal point in the answer of a calculation, false to show nothing after the decimal point.
		/// \exception std::invalid_argument \p precision is negative.
		CalculationConfiguration
		(
			int precision,
			bool shouldPreferDecimalsOverIntegers,
			bool shouldPreferSignExpressionForPositiveValues,
			bool shouldPreferLeadingZeroOverWholelessNumbers,
			bool shouldPreferTrailingZeroOverEmptyDecimalPlace
		);


		bool operator==(const CalculationConfiguration& other) const;
	};
}