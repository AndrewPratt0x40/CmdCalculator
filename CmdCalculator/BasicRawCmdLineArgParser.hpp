#pragma once

#include <concepts>
#include <ranges>
#include <algorithm>
#include <map>
#include <utility>
#include <functional>

#include "BasicRawCmdLineArgParser.h"
#include "strings.h"
#include "utilities.h"
#include "std_polyfills.h"
#include "NotImplementedException.h"


namespace
{
	enum ECmdLineArgKind
	{
		None,

		Expression,
		Precision,

		TruePreferDecimalsOverIntegers,
		FalsePreferDecimalsOverIntegers,

		TruePreferSignExpressionForPositiveValues,
		FalsePreferSignExpressionForPositiveValues,

		TruePreferLeadingZeroOverWholelessNumbers,
		FalsePreferLeadingZeroOverWholelessNumbers,

		TruePreferTrailingZeroOverEmptyDecimalPlace,
		FalsePreferTrailingZeroOverEmptyDecimalPlace
	};


	template<CmdCalculator::String ExpressionStringT>
	struct IntermediateProcessConfig
	{
		std::optional<ExpressionStringT> givenExpression;
		int precision;
		bool shouldPreferDecimalsOverIntegers;
		bool shouldPreferSignExpressionForPositiveValues;
		bool shouldPreferLeadingZeroOverWholelessNumbers;
		bool shouldPreferTrailingZeroOverEmptyDecimalPlace;


		IntermediateProcessConfig(const CmdCalculator::ProcessConfiguration<ExpressionStringT>& defaultConfig) :
			givenExpression{ defaultConfig.givenExpression },
			precision{ defaultConfig.calculationConfiguration.getPrecision() },
			shouldPreferDecimalsOverIntegers{ defaultConfig.calculationConfiguration.shouldPreferDecimalsOverIntegers() },
			shouldPreferSignExpressionForPositiveValues{ defaultConfig.calculationConfiguration.shouldPreferSignExpressionForPositiveValues() },
			shouldPreferLeadingZeroOverWholelessNumbers{ defaultConfig.calculationConfiguration.shouldPreferLeadingZeroOverWholelessNumbers() },
			shouldPreferTrailingZeroOverEmptyDecimalPlace{ defaultConfig.calculationConfiguration.shouldPreferTrailingZeroOverEmptyDecimalPlace() }
		{}
	};


	inline ECmdLineArgKind getCmdLineArgKind(std::string arg);


	template<CmdCalculator::String StringT>
	inline void throwIfContradictingArgs
	(
		const std::map<ECmdLineArgKind, std::reference_wrapper<const StringT>>& parsedConfigValues,
		const StringT& arg,
		const ECmdLineArgKind contradictingArgKind
	);




	inline ECmdLineArgKind getCmdLineArgKind(std::string arg)
	{
		if (arg == "-e")
			return ECmdLineArgKind::Expression;
		if (arg == "-p")
			return ECmdLineArgKind::Precision;
		if (arg == "-d")
			return ECmdLineArgKind::TruePreferDecimalsOverIntegers;
		if (arg == "-D")
			return ECmdLineArgKind::FalsePreferDecimalsOverIntegers;
		if (arg == "-s")
			return ECmdLineArgKind::TruePreferSignExpressionForPositiveValues;
		if (arg == "-S")
			return ECmdLineArgKind::FalsePreferSignExpressionForPositiveValues;
		if (arg == "-l")
			return ECmdLineArgKind::TruePreferLeadingZeroOverWholelessNumbers;
		if (arg == "-L")
			return ECmdLineArgKind::FalsePreferLeadingZeroOverWholelessNumbers;
		if (arg == "-t")
			return ECmdLineArgKind::TruePreferTrailingZeroOverEmptyDecimalPlace;
		if (arg == "-T")
			return ECmdLineArgKind::FalsePreferTrailingZeroOverEmptyDecimalPlace;

		return ECmdLineArgKind::None;
	}


	template<CmdCalculator::String StringT>
	inline void throwIfContradictingArgs
	(
		const std::map<ECmdLineArgKind, std::reference_wrapper<const StringT>>& parsedConfigValues,
		const StringT& arg,
		const ECmdLineArgKind contradictingArgKind
	)
	{
		if (parsedConfigValues.contains(contradictingArgKind))
		{
			throw CmdCalculator::ContradictingCmdLineArgException<StringT>
			{
				arg, parsedConfigValues.at(contradictingArgKind)
			};
		}
	}
}


template<CmdCalculator::String ExpressionStringT>
inline CmdCalculator::ProcessConfiguration<ExpressionStringT>
	CmdCalculator::BasicRawCmdLineArgParser<ExpressionStringT>::parseRawCmdLineArgs
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
{
	using ArgStringType = std::ranges::range_value_t<decltype(rawCmdLineArgs)>;

	std::map<ECmdLineArgKind, std::reference_wrapper<const ArgStringType>> parsedConfigValues{};

	IntermediateProcessConfig<ExpressionStringT> config{ defaultConfiguration };

	ECmdLineArgKind expectedArgValueKind{ ECmdLineArgKind::None };

	for (const ArgStringType& arg : rawCmdLineArgs)
	{
		if (expectedArgValueKind == ECmdLineArgKind::Expression)
		{
			config.givenExpression = arg;
			expectedArgValueKind = ECmdLineArgKind::None;
		}

		else if (expectedArgValueKind == ECmdLineArgKind::Precision)
		{
			config.precision = std::stoi(convertString<char>(arg));
			expectedArgValueKind = ECmdLineArgKind::None;
		}

		else
		{
			assert(expectedArgValueKind == ECmdLineArgKind::None);

			const ECmdLineArgKind argKind{ getCmdLineArgKind(convertString<char>(arg)) };

			if (parsedConfigValues.contains(argKind))
				throw DuplicateCmdLineArgException<ArgStringType>{ arg };

			switch (argKind)
			{
			case ECmdLineArgKind::None:
				throw UnknownCmdLineArgException<ArgStringType>{ arg };

			case ECmdLineArgKind::Expression:
				[[fallthrough]];
			case ECmdLineArgKind::Precision:
				expectedArgValueKind = argKind;
				break;

			case ECmdLineArgKind::FalsePreferDecimalsOverIntegers:
				throwIfContradictingArgs(parsedConfigValues, arg, ECmdLineArgKind::TruePreferDecimalsOverIntegers);
				config.shouldPreferDecimalsOverIntegers = false;
				break;
			case ECmdLineArgKind::TruePreferDecimalsOverIntegers:
				throwIfContradictingArgs(parsedConfigValues, arg, ECmdLineArgKind::FalsePreferDecimalsOverIntegers);
				config.shouldPreferDecimalsOverIntegers = true;
				break;

			case ECmdLineArgKind::FalsePreferSignExpressionForPositiveValues:
				throwIfContradictingArgs(parsedConfigValues, arg, ECmdLineArgKind::TruePreferSignExpressionForPositiveValues);
				config.shouldPreferSignExpressionForPositiveValues = false;
				break;
			case ECmdLineArgKind::TruePreferSignExpressionForPositiveValues:
				throwIfContradictingArgs(parsedConfigValues, arg, ECmdLineArgKind::FalsePreferSignExpressionForPositiveValues);
				config.shouldPreferSignExpressionForPositiveValues = true;
				break;

			case ECmdLineArgKind::FalsePreferLeadingZeroOverWholelessNumbers:
				throwIfContradictingArgs(parsedConfigValues, arg, ECmdLineArgKind::TruePreferLeadingZeroOverWholelessNumbers);
				config.shouldPreferLeadingZeroOverWholelessNumbers = false;
				break;
			case ECmdLineArgKind::TruePreferLeadingZeroOverWholelessNumbers:
				throwIfContradictingArgs(parsedConfigValues, arg, ECmdLineArgKind::FalsePreferLeadingZeroOverWholelessNumbers);
				config.shouldPreferLeadingZeroOverWholelessNumbers = true;
				break;

			case ECmdLineArgKind::FalsePreferTrailingZeroOverEmptyDecimalPlace:
				throwIfContradictingArgs(parsedConfigValues, arg, ECmdLineArgKind::TruePreferTrailingZeroOverEmptyDecimalPlace);
				config.shouldPreferTrailingZeroOverEmptyDecimalPlace = false;
				break;
			case ECmdLineArgKind::TruePreferTrailingZeroOverEmptyDecimalPlace:
				throwIfContradictingArgs(parsedConfigValues, arg, ECmdLineArgKind::FalsePreferTrailingZeroOverEmptyDecimalPlace);
				config.shouldPreferTrailingZeroOverEmptyDecimalPlace = true;
				break;

			default:
				Polyfills::unreachable();
			}

			parsedConfigValues.emplace(argKind, arg);
		}
	}

	if (expectedArgValueKind != ECmdLineArgKind::None)
	{
		assert(!std::ranges::empty(rawCmdLineArgs));
		throw MissingCmdLineArgValueException<ExpressionStringT>{ *std::ranges::rbegin(rawCmdLineArgs) };
	}

	return ProcessConfiguration<ExpressionStringT>
	{
		.givenExpression{ config.givenExpression },
		.calculationConfiguration
		{
			config.precision,
			config.shouldPreferDecimalsOverIntegers,
			config.shouldPreferSignExpressionForPositiveValues,
			config.shouldPreferLeadingZeroOverWholelessNumbers,
			config.shouldPreferTrailingZeroOverEmptyDecimalPlace
		}
	};
}