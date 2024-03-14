#pragma once

#include <concepts>
#include <ranges>
#include <iterator>
#include <string>
#include <string_view>
#include <optional>
#include <regex>
#include <format>
#include <algorithm>
#include <assert.h>

#include "ExpressionEvaluationToStringConverter.h"
#include "NotImplementedException.h"


namespace
{
	const std::regex numAsStrRegex{ "^[-+]?0*([1-9]\\d*)?(\\.(\\d*[1-9])?0*)?" };
	enum NumAsStrRegexSubgroups : size_t
	{
		WholeDigits = 1,
		FractionalDigits = 3
	};

	constexpr inline auto dropLeadingZeros = std::views::drop_while([](const char ch) { return ch == '0'; });
	constexpr inline auto dropTrailingZeros =
		std::views::reverse
		| dropLeadingZeros
		| std::views::reverse
	;


	template<std::ranges::input_range CharRangeT>
		requires std::convertible_to<std::ranges::range_value_t<CharRangeT>, char>
	inline std::string rangeToString(CharRangeT chars);


	inline std::string getSignOutStr
	(
		const CmdCalculator::Arithmetic::ESign sign,
		const CmdCalculator::CalculationConfiguration& configuration
	);

	inline std::string getWholeDigitsOutStr
	(
		std::string_view wholeDigitsStr,
		const CmdCalculator::CalculationConfiguration& configuration
	);

	inline std::string getDecimalPointOutStr
	(
		std::string_view wholeDigitsStr,
		std::string_view fractionalDigitsStr,
		const CmdCalculator::CalculationConfiguration& configuration
	);

	inline std::string getFractionalDigitsOutStr
	(
		std::string_view fractionalDigitsStr,
		const CmdCalculator::CalculationConfiguration& configuration
	);


	template<std::ranges::input_range CharRangeT>
		requires std::convertible_to<std::ranges::range_value_t<CharRangeT>, char>
	std::string rangeToString(CharRangeT chars)
	{
		return std::string{ std::ranges::begin(chars), std::ranges::end(chars) };
	}


	inline std::string getSignOutStr
	(
		const CmdCalculator::Arithmetic::ESign sign,
		const CmdCalculator::CalculationConfiguration& configuration
	)
	{
		if (sign == CmdCalculator::Arithmetic::ESign::Negative)
			return "-";

		if (configuration.shouldPreferSignExpressionForPositiveValues() && sign == CmdCalculator::Arithmetic::ESign::Positive)
			return "+";

		return "";
	}


	inline std::string getWholeDigitsOutStr
	(
		std::string_view wholeDigitsStr,
		const CmdCalculator::CalculationConfiguration& configuration
	)
	{
		const std::string trimmedwholeDigitsStr
		{
			rangeToString(wholeDigitsStr | dropLeadingZeros)
		};

		return
		(
			trimmedwholeDigitsStr.empty()
			&& configuration.shouldPreferLeadingZeroOverWholelessNumbers()
		)
			? "0"
			: trimmedwholeDigitsStr
		;
	}


	inline std::string getDecimalPointOutStr
	(
		std::string_view wholeDigitsOutStr,
		std::string_view fractionalDigitsOutStr,
		const CmdCalculator::CalculationConfiguration& configuration
	)
	{
		if
		(
			(std::ranges::empty(wholeDigitsOutStr) && std::ranges::empty(fractionalDigitsOutStr))
			|| !std::ranges::empty(fractionalDigitsOutStr)
			|| configuration.shouldPreferDecimalsOverIntegers()
		)
			return ".";

		return "";
	}


	inline std::string getFractionalDigitsOutStr
	(
		std::string_view fractionalDigitsStr,
		const CmdCalculator::CalculationConfiguration& configuration
	)
	{
		const std::string trimmedFractionalDigitsStr
		{
			rangeToString(fractionalDigitsStr.substr(0, configuration.getPrecision()) | dropTrailingZeros)
		};

		return
		(
			trimmedFractionalDigitsStr.empty()
			&& configuration.shouldPreferDecimalsOverIntegers()
			&& configuration.shouldPreferTrailingZeroOverEmptyDecimalPlace()
		)
			? "0"
			: trimmedFractionalDigitsStr
		;
	}
}



template<CmdCalculator::Expressions::Expression ExpressionT>
inline typename CmdCalculator::ExpressionEvaluationToStringConverter<ExpressionT>::StringType
	CmdCalculator::ExpressionEvaluationToStringConverter<ExpressionT>
	::stringifyExpression(const ExpressionT& source, const CalculationConfiguration& configuration) const
{
	const Arithmetic::RealNumber auto eval{ source.getEvaluation() };
	const std::string evalStr{ convertString<char>(eval.getStringRepresentation()) };

	std::smatch evalStrMatchResult;
	const bool couldMatch{ std::regex_match(evalStr, evalStrMatchResult, numAsStrRegex) };
	assert(couldMatch);
	assert(evalStrMatchResult.ready());

	const std::string wholeDigitsOutStr
	{
		getWholeDigitsOutStr
		(
			evalStrMatchResult[NumAsStrRegexSubgroups::WholeDigits].str(),
			configuration
		)
	};
	const std::string fractionalDigitsOutStr
	{
		getFractionalDigitsOutStr
		(
			evalStrMatchResult[NumAsStrRegexSubgroups::FractionalDigits].str(),
			configuration
		)
	};

	return convertString<CharType>
	(
		std::format
		(
			"{}{}{}{}",
			getSignOutStr(eval.getSign(), configuration),
			wholeDigitsOutStr,
			getDecimalPointOutStr(wholeDigitsOutStr, fractionalDigitsOutStr, configuration),
			fractionalDigitsOutStr
		)
	);
}