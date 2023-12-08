#include "CalculationConfiguration.h"

#include "NotImplementedException.h"


CmdCalculator::CalculationConfiguration::CalculationConfiguration
(
	int precision,
	bool shouldPreferDecimalsOverIntegers,
	bool shouldPreferSignExpressionForPositiveValues,
	bool shouldPreferLeadingZeroOverWholelessNumbers,
	bool shouldPreferTrailingZeroOverEmptyDecimalPlace
) :
	m_precision{ precision },
	m_shouldPreferDecimalsOverIntegers{ shouldPreferDecimalsOverIntegers },
	m_shouldPreferSignExpressionForPositiveValues{ shouldPreferSignExpressionForPositiveValues },
	m_shouldPreferLeadingZeroOverWholelessNumbers{ shouldPreferLeadingZeroOverWholelessNumbers },
	m_shouldPreferTrailingZeroOverEmptyDecimalPlace{ shouldPreferTrailingZeroOverEmptyDecimalPlace }
{
	if (m_precision < 0)
		throw std::invalid_argument{ "Precision cannot be negative." };
}


int CmdCalculator::CalculationConfiguration::getPrecision()
{
	return m_precision;
}


bool CmdCalculator::CalculationConfiguration::shouldPreferDecimalsOverIntegers()
{
	return m_shouldPreferDecimalsOverIntegers;
}


bool CmdCalculator::CalculationConfiguration::shouldPreferSignExpressionForPositiveValues()
{
	return m_shouldPreferSignExpressionForPositiveValues;
}


bool CmdCalculator::CalculationConfiguration::shouldPreferLeadingZeroOverWholelessNumbers()
{
	return m_shouldPreferLeadingZeroOverWholelessNumbers;
}


bool CmdCalculator::CalculationConfiguration::shouldPreferTrailingZeroOverEmptyDecimalPlace()
{
	return m_shouldPreferTrailingZeroOverEmptyDecimalPlace;
}