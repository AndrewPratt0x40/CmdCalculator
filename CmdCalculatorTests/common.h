#pragma once

#include <concepts>
#include <ranges>
#include <vector>


namespace CmdCalculatorTests
{
	auto ValuesInRange(std::ranges::input_range auto range)
	{
		return testing::ValuesIn(std::ranges::begin(range), std::ranges::end(range));
	}


	struct EmptyStruct {};


	namespace SharedTestData
	{

		template<class T>
		concept ArithmeticOperationValue =
			std::convertible_to<T, double>
		;


		template<ArithmeticOperationValue ValueT = double>
		struct UnaryArithmeticOperationData
		{
			using ValueType = ValueT;

			ValueType operand;
			ValueType result;
		};

		template<class T>
		concept UnaryArithmeticOperationDataRange =
			std::ranges::input_range<T>
			&& std::same_as
			<
				std::ranges::range_value_t<T>,
				UnaryArithmeticOperationData
				<
					typename std::ranges::range_value_t<T>::ValueType
				>
			>
		;


		template<ArithmeticOperationValue ValueT = double>
		struct BinaryArithmeticOperationData
		{
			using ValueType = ValueT;

			ValueType leftOperand;
			ValueType rightOperand;
			ValueType result;
		};

		template<class T>
		concept BinaryArithmeticOperationDataRange =
			std::ranges::input_range<T>
			&& std::same_as
			<
				std::ranges::range_value_t<T>,
				BinaryArithmeticOperationData
				<
					typename std::ranges::range_value_t<T>::ValueType
				>
			>
		;


		constexpr inline UnaryArithmeticOperationDataRange auto negationOperationsDataValues
		{
			std::initializer_list<UnaryArithmeticOperationData<double>>
			{
				{ -56.78, 56.78 },
				{ -12.34, 12.34 },
				{ -2.0, 2.0 },
				{ -1.5, 1.5 },
				{ -1.0, 1.0 },
				{ -0.5, 0.5 },
				{ -std::numeric_limits<double>::min(), std::numeric_limits<double>::min() },
				{ 0.0, 0.0 },
				{ std::numeric_limits<double>::min(), std::numeric_limits<double>::min() },
				{ 0.5, 0.5 },
				{ 1.0, 1.0 },
				{ 1.5, 1.5 },
				{ 2.0, 2.0 },
				{ 12.34, 12.34 },
				{ 56.78, 56.78 }
			}
		};
	}
}