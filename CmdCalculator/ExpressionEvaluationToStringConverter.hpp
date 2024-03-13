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
	using ImplCharType = char;
	
	template<class T>
	concept ImplCharsView =
		std::ranges::forward_range<T>
		&& std::convertible_to<std::ranges::range_value_t<T>, ImplCharType>
	;

	template<class T>
	concept ImplCharIter =
		std::input_iterator<T>
		&& std::convertible_to<std::iter_value_t<T>, ImplCharType>
	;


	constexpr inline ImplCharsView auto implCharDigits = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	constexpr inline ImplCharType implCharZero{ '0' };
	constexpr inline ImplCharType implCharMinusSign{ '-' };
	constexpr inline ImplCharType implCharPlusSign{ '+' };
	constexpr inline ImplCharType implCharDecimalPointSign{ '.' };


	constexpr bool isDigitChar(const ImplCharType ch);
	constexpr bool isSignChar(const ImplCharType ch);
	constexpr bool isDecimalPointChar(const ImplCharType ch);


	inline ImplCharsView auto dropSignCharView(ImplCharsView auto evalStr);

	inline ImplCharIter auto findDecimalPoint(ImplCharsView auto str);

	inline ImplCharsView auto getWholeDigitsView
	(
		ImplCharsView auto unsignedEvalStr,
		const ImplCharIter auto decimalPointIter
	);

	inline ImplCharsView auto getFractionalDigitsView
	(
		ImplCharsView auto unsignedEvalStr,
		const ImplCharIter auto decimalPointIter
	);

	inline ImplCharsView auto dropLeadingZerosView(ImplCharsView auto str);
	inline ImplCharsView auto dropTrailingZerosView(ImplCharsView auto str);

	inline std::string getSignOutStr
	(
		const CmdCalculator::Arithmetic::ESign sign,
		const CmdCalculator::CalculationConfiguration& configuration
	);

	inline std::string getWholeDigitsOutStr
	(
		ImplCharsView auto wholeDigitsStr,
		const CmdCalculator::CalculationConfiguration& configuration
	);

	inline std::string getDecimalPointOutStr
	(
		ImplCharsView auto wholeDigitsStr,
		ImplCharsView auto fractionalDigitsStr,
		const CmdCalculator::CalculationConfiguration& configuration
	);

	inline std::string getFractionalDigitsOutStr
	(
		ImplCharsView auto fractionalDigitsStr,
		const CmdCalculator::CalculationConfiguration& configuration
	);


	inline constexpr bool isDigitChar(const ImplCharType ch)
	{
		return std::ranges::find(implCharDigits, ch) != std::ranges::end(implCharDigits);
	}


	inline constexpr bool isSignChar(const ImplCharType ch)
	{
		return ch == implCharMinusSign || ch == implCharPlusSign;
	}


	inline constexpr bool isDecimalPointChar(const ImplCharType ch)
	{
		return ch == implCharDecimalPointSign;
	}


	inline ImplCharsView auto dropSignCharView(ImplCharsView auto evalStr)
	{
		assert(!std::ranges::empty(evalStr));
		const ImplCharType firstChar{ *std::ranges::begin(evalStr) };
		assert(isDigitChar(firstChar) || isSignChar(firstChar));

		return evalStr | std::views::drop(isSignChar(firstChar) ? 0 : 1);
	}


	inline ImplCharIter auto findDecimalPoint(ImplCharsView auto str)
	{
		return std::ranges::find_if(str, implCharDecimalPointSign);
	}


	inline ImplCharsView auto getWholeDigitsView
	(
		ImplCharsView auto unsignedEvalStr,
		const ImplCharIter auto decimalPointIter
	)
	{
		assert
		(
			decimalPointIter == std::ranges::end(unsignedEvalStr)
			|| *decimalPointIter == implCharDecimalPointSign
		);

		return std::ranges::subrange
		{
			std::ranges::begin(unsignedEvalStr),
			decimalPointIter
		};
	}


	inline ImplCharsView auto getFractionalDigitsView
	(
		ImplCharsView auto unsignedEvalStr,
		const ImplCharIter auto decimalPointIter
	)
	{
		assert
		(
			decimalPointIter == std::ranges::end(unsignedEvalStr)
			|| *decimalPointIter == implCharDecimalPointSign
		);

		return std::ranges::subrange
		{
			decimalPointIter + (decimalPointIter == std::ranges::end(unsignedEvalStr) ? 0 : 1),
			std::ranges::end(unsignedEvalStr)
		};
	}


	inline ImplCharsView auto dropLeadingZerosView(ImplCharsView auto str)
	{
		return str | std::views::drop_while([](const ImplCharType ch) { return ch == '0'; });
	}


	inline ImplCharsView auto dropTrailingZerosView(ImplCharsView auto str)
	{
		return dropLeadingZerosView(str | std::views::reverse) | std::views::reverse;
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
		ImplCharsView auto wholeDigitsStr,
		const CmdCalculator::CalculationConfiguration& configuration
	)
	{
		if (!std::ranges::empty(wholeDigitsStr))
			return std::string{ wholeDigitsStr };

		if (configuration.shouldPreferLeadingZeroOverWholelessNumbers())
			return "0";

		return "";
	}


	inline std::string getDecimalPointOutStr
	(
		ImplCharsView auto wholeDigitsStr,
		ImplCharsView auto fractionalDigitsStr,
		const CmdCalculator::CalculationConfiguration& configuration
	)
	{
		if
		(
			std::ranges::empty(wholeDigitsStr)
			|| !std::ranges::empty(fractionalDigitsStr)
			|| configuration.shouldPreferDecimalsOverIntegers()
		)
			return ".";

		return "";
	}


	inline std::string getFractionalDigitsOutStr
	(
		ImplCharsView auto fractionalDigitsStr,
		const CmdCalculator::CalculationConfiguration& configuration
	)
	{
		if (!std::ranges::empty(fractionalDigitsStr))
			return std::string{ fractionalDigitsStr };

		if (configuration.shouldPreferTrailingZeroOverEmptyDecimalPlace())
			return "0";

		return "";
	}
}



template<CmdCalculator::Expressions::Expression ExpressionT>
inline typename CmdCalculator::ExpressionEvaluationToStringConverter<ExpressionT>::StringType
	CmdCalculator::ExpressionEvaluationToStringConverter<ExpressionT>
	::stringifyExpression(const ExpressionT& source, const CalculationConfiguration& configuration) const
{
	const Arithmetic::RealNumber auto eval{ source.getEvaluation() };
	const std::string evalStr{ convertString<char>(eval.getStringRepresentation()) };
	assert(std::regex_match(evalStr, std::regex{ "^[+-]?(\\d*\\.\\d+|\\d+\\.?)$" }));

	auto foo{ dropSignCharView(evalStr) };
	ImplCharsView auto unsignedEvalStr{ dropSignCharView(evalStr) };
	const ImplCharIter auto decimalPointIter{ findDecimalPoint(unsignedEvalStr) };

	ImplCharsView auto wholeDigitsStr
	{
		dropLeadingZerosView(getWholeDigitsView(unsignedEvalStr, decimalPointIter))
	};

	ImplCharsView auto fractionalDigitsStr
	{
		dropTrailingZerosView(getFractionalDigitsView(unsignedEvalStr, decimalPointIter))
	};

	return convertString<CharType>
	(
		std::format
		(
			"{}{}{}{}",
			getSignOutStr(eval.getSign(), configuration),
			getWholeDigitsOutStr(wholeDigitsStr, configuration),
			getDecimalPointOutStr(wholeDigitsStr, fractionalDigitsStr, configuration),
			getFractionalDigitsOutStr(fractionalDigitsStr, configuration)
		)
	);
}