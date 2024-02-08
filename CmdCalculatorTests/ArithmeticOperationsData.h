#pragma once

#include <concepts>
#include <ranges>
#include <array>
#include <map>

#include "../CmdCalculator/ESign.h"


namespace CmdCalculatorTests::SharedTestData
{
	template<class ValueT>
	struct ArithmeticOperationsData
	{
		using ValueType = ValueT;

		ValueType value;

		CmdCalculator::Arithmetic::ESign sign;
		ValueType negation;
		ValueType absoluteValue;

		// Mappings from right operand to result of operation.
		std::map<ValueType, ValueType> additionValues;
		std::map<ValueType, ValueType> subtractionValues;
		std::map<ValueType, ValueType> multiplicationValues;
		std::map<ValueType, ValueType> divisionValues;
		std::map<ValueType, ValueType> exponentiationValues;
		std::map<ValueType, ValueType> nthRootValues;
		std::map<ValueType, ValueType> moduloValues;
	};

	template<class T>
	concept ArithmeticOperationsDataRange =
		std::ranges::input_range<T>
		&& std::same_as
		<
			std::ranges::range_value_t<T>,
			ArithmeticOperationsData
			<
				typename std::ranges::range_value_t<T>::ValueType
			>
		>
	;


	ArithmeticOperationsDataRange auto getArithmeticOperationsDataValues()
	{
		return std::initializer_list<ArithmeticOperationsData<double>>
		{
			{
				.value{ 12.34 },
				.sign{ CmdCalculator::Arithmetic::ESign::Positive },
				.negation{ -12.34 },
				.absoluteValue{ 12.34 },
				.additionValues
				{
					{  }
				},
				.subtractionValues{},
				.multiplicationValues{},
				.divisionValues{},
				.nthRootValues{},
				.moduloValues{}
			}
		};
	};
}