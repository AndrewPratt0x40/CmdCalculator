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

		template<class T>
		concept ArithmeticOperationValueRange =
			std::ranges::input_range<T>
			&& ArithmeticOperationValue
			<
				std::ranges::range_value_t<T>
			>
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


		constexpr inline ArithmeticOperationValueRange auto positiveNumbers
		{
			std::initializer_list<double>
			{
				std::numeric_limits<double>::min(),
				0.5,
				1.0,
				1.5,
				2.0,
				12.34,
				56.78,
				std::numeric_limits<double>::max()
			}
		};


		constexpr inline ArithmeticOperationValueRange auto negativeNumbers
		{
			std::initializer_list<double>
			{
				-std::numeric_limits<double>::min(),
				-0.5,
				-1.0,
				-1.5,
				-2.0,
				-12.34,
				-56.78,
				std::numeric_limits<double>::lowest()
			}
		};
		
		
		constexpr inline UnaryArithmeticOperationDataRange auto negationOperationsDataValues
		{
			std::initializer_list<UnaryArithmeticOperationData<double>>
			{
				{-56.78, 56.78},
				{-12.34, 12.34},
				{-2.0, 2.0},
				{-1.5, 1.5},
				{-1.0, 1.0},
				{-0.5, 0.5},
				{-std::numeric_limits<double>::min(), std::numeric_limits<double>::min()},
				{0.0, 0.0},
				{std::numeric_limits<double>::min(), -std::numeric_limits<double>::min()},
				{0.5, -0.5},
				{1.0, -1.0},
				{1.5, -1.5},
				{2.0, -2.0},
				{12.34, -12.34},
				{56.78, -56.78}
			}
		};


		constexpr inline UnaryArithmeticOperationDataRange auto absoluteValueOperationsDataValues
		{
			std::initializer_list<UnaryArithmeticOperationData<double>>
			{
				{-56.78, 56.78},
				{-12.34, 12.34},
				{-2.0, 2.0},
				{-1.5, 1.5},
				{-1.0, 1.0},
				{-0.5, 0.5},
				{-std::numeric_limits<double>::min(), std::numeric_limits<double>::min()},
				{0.0, 0.0},
				{std::numeric_limits<double>::min(), std::numeric_limits<double>::min()},
				{0.5, 0.5},
				{1.0, 1.0},
				{1.5, 1.5},
				{2.0, 2.0},
				{12.34, 12.34},
				{56.78, 56.78},
				{std::numeric_limits<double>::max(), std::numeric_limits<double>::max()}
			}
		};


		constexpr inline BinaryArithmeticOperationDataRange auto additionOperationsDataValues
		{
			std::initializer_list<BinaryArithmeticOperationData<double>>
			{
				{0.0, 0.0, 0.0},
				{0.0, 0.5, 0.5},
				{0.0, 1.0, 1.0},
				{0.0, 1.5, 1.5},
				{0.0, 2.0, 2.0},

				{0.5, 0.0, 0.5},
				{0.5, 0.5, 1.0},
				{0.5, 1.0, 1.5},
				{0.5, 1.5, 2.0},
				{0.5, 2.0, 2.5},

				{1.0, 0.0, 1.0},
				{1.0, 0.5, 1.5},
				{1.0, 1.0, 2.0},
				{1.0, 1.5, 2.5},
				{1.0, 2.0, 3.0},

				{1.5, 0.0, 1.5},
				{1.5, 0.5, 2.0},
				{1.5, 1.0, 2.5},
				{1.5, 1.5, 3.0},
				{1.5, 2.0, 3.5},

				{2.0, 0.0, 2.0},
				{2.0, 0.5, 2.5},
				{2.0, 1.0, 3.0},
				{2.0, 1.5, 3.5},
				{2.0, 2.0, 4.0},

				{12.34, 56.78, 69.12},
				{56.78, 12.34, 69.12},

				{12.34, -56.78, -44.44},
				{-56.78, 12.34, -44.44},

				{-12.34, 56.78, 44.44},
				{56.78, -12.34, 44.44},

				{-12.34, -56.78, -69.12},
				{-56.78, -12.34, -69.12}
			}
		};


		constexpr inline BinaryArithmeticOperationDataRange auto subtractionOperationsDataValues
		{
			std::initializer_list<BinaryArithmeticOperationData<double>>
			{
				{0.0, 0.0, 0.0},
				{0.0, 0.5, -0.5},
				{0.0, 1.0, -1.0},
				{0.0, 1.5, -1.5},
				{0.0, 2.0, -2.0},

				{0.5, 0.0, 0.5},
				{0.5, 0.5, 0.0},
				{0.5, 1.0, -0.5},
				{0.5, 1.5, -1.0},
				{0.5, 2.0, -1.5},

				{1.0, 0.0, 1.0},
				{1.0, 0.5, 0.5},
				{1.0, 1.0, 0.0},
				{1.0, 1.5, -0.5},
				{1.0, 2.0, -1.0},

				{1.5, 0.0, 1.5},
				{1.5, 0.5, 1.0},
				{1.5, 1.0, 0.5},
				{1.5, 1.5, 0.0},
				{1.5, 2.0, -0.5},

				{2.0, 0.0, 2.0},
				{2.0, 0.5, 1.5},
				{2.0, 1.0, 1.0},
				{2.0, 1.5, 0.5},
				{2.0, 2.0, 0.0},

				{12.34, 56.78, -44.44},
				{56.78, 12.34, 44.44},

				{12.34, -56.78, 69.12},
				{-56.78, 12.34, -69.12},

				{-12.34, 56.78, -69.12},
				{56.78, -12.34, 69.12},

				{-12.34, -56.78, 44.44},
				{-56.78, -12.34, -44.44}
			}
		};


		constexpr inline BinaryArithmeticOperationDataRange auto multiplicationOperationsDataValues
		{
			std::initializer_list<BinaryArithmeticOperationData<double>>
			{
				{0.0, 0.0, 0.00},
				{0.0, 0.5, 0.00},
				{0.0, 1.0, 0.00},
				{0.0, 1.5, 0.00},
				{0.0, 2.0, 0.00},

				{0.5, 0.0, 0.00},
				{0.5, 0.5, 0.25},
				{0.5, 1.0, 0.50},
				{0.5, 1.5, 0.75},
				{0.5, 2.0, 1.00},

				{1.0, 0.0, 0.00},
				{1.0, 0.5, 0.50},
				{1.0, 1.0, 1.00},
				{1.0, 1.5, 1.50},
				{1.0, 2.0, 2.00},

				{1.5, 0.0, 0.00},
				{1.5, 0.5, 0.75},
				{1.5, 1.0, 1.50},
				{1.5, 1.5, 2.25},
				{1.5, 2.0, 3.00},

				{2.0, 0.0, 0.00},
				{2.0, 0.5, 1.00},
				{2.0, 1.0, 2.00},
				{2.0, 1.5, 3.00},
				{2.0, 2.0, 4.00},

				{12.34, 56.78, 700.6652},
				{56.78, 12.34, 700.6652},

				{12.34, -56.78, -700.6652},
				{-56.78, 12.34, -700.6652},

				{-12.34, 56.78, -700.6652},
				{56.78, -12.34, -700.6652},

				{-12.34, -56.78, 700.6652},
				{-56.78, -12.34, 700.6652}
			}
		};


		constexpr inline BinaryArithmeticOperationDataRange auto divisionOperationsDataValues
		{
			std::initializer_list<BinaryArithmeticOperationData<double>>
			{
				{0.0, 0.5, 0.00},
				{0.0, 1.0, 0.00},
				{0.0, 1.5, 0.00},
				{0.0, 2.0, 0.00},

				{0.5, 0.5, 1.00},
				{0.5, 1.0, 0.50},
				{0.5, 1.5, 0.33333333333333333},
				{0.5, 2.0, 0.25},

				{1.0, 0.5, 2.00},
				{1.0, 1.0, 1.00},
				{1.0, 1.5, 0.66666666666666666},
				{1.0, 2.0, 0.50},

				{1.5, 0.5, 3.00},
				{1.5, 1.0, 1.50},
				{1.5, 1.5, 1.00},
				{1.5, 2.0, 0.75},

				{2.0, 0.5, 4.00},
				{2.0, 1.0, 2.00},
				{2.0, 1.5, 1.33333333333333333},
				{2.0, 2.0, 1.0},

				{12.34, 56.78, 0.21733004579077139},
				{56.78, 12.34, 4.60129659643435980},

				{12.34, -56.78, -0.21733004579077139},
				{-56.78, 12.34, -4.60129659643435980},

				{-12.34, 56.78, -0.21733004579077139},
				{56.78, -12.34, -4.60129659643435980},

				{-12.34, -56.78, 0.21733004579077139},
				{-56.78, -12.34, 4.60129659643435980}
			}
		};


		constexpr inline BinaryArithmeticOperationDataRange auto exponentiationOperationsDataValues
		{
			std::initializer_list<BinaryArithmeticOperationData<double>>
			{
				{0.0, 0, 1.0},
				{0.0, 1, 0.0},
				{0.0, 2, 0.0},
				{0.0, 3, 0.0},
				{0.0, 10, 0.0},

				{0.5, 0, 1.0},
				{0.5, 1, 0.5},
				{0.5, 2, 0.25},
				{0.5, 3, 0.125},
				{0.5, 10, 0.0009765625},

				{1.0, 0, 1.0},
				{1.0, 1, 1.0},
				{1.0, 2, 1.0},
				{1.0, 3, 1.0},
				{1.0, 10, 1.0},

				{1.5, 0, 1.0},
				{1.5, 1, 1.5},
				{1.5, 2, 2.25},
				{1.5, 3, 3.375},
				{1.5, 10, 57.6650390625},

				{2.0, 0, 1.0},
				{2.0, 1, 2.0},
				{2.0, 2, 4.0},
				{2.0, 3, 8.0},
				{2.0, 10, 1024.0},

				{-1.0, 0, 1.0},
				{-1.0, 1, -1.0},
				{-1.0, 2, 1.0},
				{-1.0, 3, -1.0}
			}
		};


		constexpr inline BinaryArithmeticOperationDataRange auto nthRootOperationsDataValues
		{
			std::initializer_list<BinaryArithmeticOperationData<double>>
			{
				{1.0, 0.0, 0.0},
				{2.0, 0.0, 0.0},
				{3.0, 0.0, 0.0},

				{1.0, 0.5, 0.5},
				{2.0, 0.5, 0.70710678118654752},
				{3.0, 0.5, 0.79370052598409973},

				{1.0, 1.0, 1.0},
				{2.0, 1.0, 1.0},
				{3.0, 1.0, 1.0},

				{1.0, 1.5, 1.5},
				{2.0, 1.5, 1.22474487139158904},
				{3.0, 1.5, 1.14471424255333186},

				{1.0, 2.0, 2.0},
				{2.0, 2.0, 1.41421356237309504},
				{3.0, 2.0, 1.25992104989487316},

				{1.0, 16.0, 16.0},
				{2.0, 16.0, 4.0},
				{3.0, 16.0, 2.51984209978974632},

				{1.0, 125.0, 125.0},
				{2.0, 125.0, 11.1803398874989484},
				{3.0, 125.0, 5.0}
			}
		};


		constexpr inline BinaryArithmeticOperationDataRange auto moduloOperationsDataValues
		{
			std::initializer_list<BinaryArithmeticOperationData<double>>
			{
				{0.00, 1.0, 0.00},
				{0.25, 1.0, 0.25},
				{0.50, 1.0, 0.50},
				{0.75, 1.0, 0.75},
				{1.00, 1.0, 0.00},
				{1.25, 1.0, 0.25},
				{1.50, 1.0, 0.50},
				{2.00, 1.0, 0.00},

				{0.00, 3.0, 0.00},
				{1.00, 3.0, 1.00},
				{2.00, 3.0, 2.00},
				{3.00, 3.0, 0.00},
				{4.00, 3.0, 1.00},
				{5.00, 3.0, 2.00},
				{6.00, 3.0, 0.00},
				{7.00, 3.0, 1.00},

				{0.00, 1.5, 0.00},
				{0.50, 1.5, 0.50},
				{1.00, 1.5, 1.00},
				{1.50, 1.5, 0.00},
				{2.00, 1.5, 0.50},

				{12.34, 56.78, 12.34},
				{56.78, 12.34, 7.42},

				{12.34, -56.78, -12.34},
				{-56.78, 12.34, -7.42},

				{-12.34, 56.78, -12.34},
				{56.78, -12.34, -7.42},

				{-12.34, -56.78, 12.34},
				{-56.78, -12.34, 7.42}
			}
		};
	}
}