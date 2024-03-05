#pragma once

#include "pch.h"

#include <algorithm>
#include <concepts>
#include <format>
#include <ranges>
#include <vector>
#include <array>
#include <optional>
#include <utility>

#include "../CmdCalculator/std_polyfills.h"
#include "../CmdCalculator/ESign.h"
#include "../CmdCalculator/EBinaryOperator.h"


namespace CmdCalculatorTestUtils
{
	template<class T>
	concept StdVector = std::same_as<T, std::vector<typename T::value_type>>;

	StdVector auto moveRangeToVector(std::ranges::input_range auto range)
	{
		std::vector<std::ranges::range_value_t<decltype(range)>> values{};
		std::ranges::move(range, std::back_inserter(values));
		return values;
	}

	StdVector auto copyRangeToVector(std::ranges::input_range auto range)
	{
		std::vector<std::ranges::range_value_t<decltype(range)>> values{};
		std::ranges::copy(range, std::back_inserter(values));
		return values;
	}


	auto ValuesInRange(std::ranges::range auto range)
	{
		return testing::ValuesIn(copyRangeToVector(range));
	}
	
	auto ValuesInRange(std::ranges::forward_range auto range)
	{
		return testing::ValuesIn(std::ranges::begin(range), std::ranges::end(range));
	}


	template<class T>
	concept SizedForwardStringRange =
		std::ranges::forward_range<T>
		&& std::ranges::sized_range<T>
		&& std::convertible_to<std::string, std::ranges::range_value_t<T>>
	;


	constexpr std::string joinStrings
	(
		const SizedForwardStringRange auto parts,
		const std::string sep
	)
	{
		if (std::ranges::empty(parts))
			return "";

		const std::integral auto numParts{ std::ranges::size(parts) };

		if (numParts == 1)
			return *std::ranges::begin(parts);

		return parts.empty()
			? ""
			:
				CmdCalculator::Polyfills::ranges::fold_left
				(
					parts
					| std::views::take(numParts - 1)
					| std::views::drop(1)
					| std::views::transform
					(
						[&sep](const std::string& part)
						{ return std::format("{}{}", part, sep); }
					)
					,
					std::format("{}{}", *std::ranges::begin(parts), sep),
					std::plus<std::string>()
				)
				+ *(std::ranges::next(std::ranges::begin(parts), numParts - 1))
		;
	}


	std::string joinStrings
	(
		const SizedForwardStringRange auto parts
	)
	{
		return joinStrings(parts, ",");
	}


	constexpr std::string getBinaryOperatorName(const CmdCalculator::MathAst::EBinaryOperator binaryOperator)
	{
		switch (binaryOperator)
		{
		case CmdCalculator::MathAst::EBinaryOperator::Addition:
			return "Addition";
		case CmdCalculator::MathAst::EBinaryOperator::Subtraction:
			return "Subtraction";
		case CmdCalculator::MathAst::EBinaryOperator::Multiplication:
			return "Multiplication";
		case CmdCalculator::MathAst::EBinaryOperator::Division:
			return "Division";
		case CmdCalculator::MathAst::EBinaryOperator::Exponentiation:
			return "Exponentiation";
		case CmdCalculator::MathAst::EBinaryOperator::NthRoot:
			return "NthRoot";
		case CmdCalculator::MathAst::EBinaryOperator::Modulo:
			return "Modulo";
		default:
			return "Unknown";
		}
	}


	struct EmptyStruct {};


	namespace SharedTestData
	{

		template<class T>
		concept IntegralRange = 
			std::ranges::forward_range<T>
			&& std::integral<std::ranges::range_value_t<T>>
		;
		
		
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
		struct TrueBinaryBooleanOperationData
		{
			using ValueType = ValueT;

			ValueType leftOperand;
			ValueType rightOperand;
		};

		template<class T>
		concept TrueBinaryBooleanOperationDataRange =
			std::ranges::input_range<T>
			&& std::same_as
			<
				std::ranges::range_value_t<T>,
				TrueBinaryBooleanOperationData
				<
					typename std::ranges::range_value_t<T>::ValueType
				>
			>
		;


		template<ArithmeticOperationValue ValueT = double>
		struct BinaryBooleanOperationData
		{
			using ValueType = ValueT;

			ValueType leftOperand;
			ValueType rightOperand;
			bool result;
		};

		template<class T>
		concept BinaryBooleanOperationDataRange =
			std::ranges::input_range<T>
			&& std::same_as
			<
				std::ranges::range_value_t<T>,
				BinaryBooleanOperationData
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


		template<ArithmeticOperationValue ValueT = double>
		struct BinaryThreeWayComparisonOperationData
		{
			using ValueType = ValueT;

			ValueType leftOperand;
			ValueType rightOperand;
			CmdCalculator::Arithmetic::ESign result;
		};

		template<class T>
		concept BinaryThreeWayComparisonOperationDataRange =
			std::ranges::input_range<T>
			&& std::same_as
			<
				std::ranges::range_value_t<T>,
				BinaryThreeWayComparisonOperationData
				<
					typename std::ranges::range_value_t<T>::ValueType
				>
			>
		;


		template<ArithmeticOperationValue ValueT = double>
		struct CompositeOperandData
		{
			using ValueType = ValueT;

			ValueType value;
			CmdCalculator::Arithmetic::ESign sign;
			std::optional<ValueType> absoluteValue;
			std::optional<ValueType> negatedValue;
			std::optional<ValueType> incrementedValue;
			std::optional<ValueType> decrementedValue;

			constexpr friend bool operator==(const CompositeOperandData& lhs, const CompositeOperandData& rhs)
			{
				return lhs.value == rhs.value;
			}
			
			constexpr friend auto operator<=>(const CompositeOperandData& lhs, const CompositeOperandData& rhs)
			{
				return lhs.value <=> rhs.value;
			}
		};
		static_assert(std::totally_ordered<CompositeOperandData<>>);

		template<class T>
		concept CompositeOperandDataRange =
			std::ranges::input_range<T>
			&& std::same_as
			<
				std::ranges::range_value_t<T>,
				CompositeOperandData
				<
					typename std::ranges::range_value_t<T>::ValueType
				>
			>
		;

		template<class T>
		concept CompositeOperandDataPairRange =
			std::ranges::input_range<T>
			&& std::same_as
			<
				std::remove_cvref_t<decltype(std::declval<std::ranges::range_value_t<T>>().first)>,
				CompositeOperandData
				<
					typename decltype(std::declval<std::ranges::range_value_t<T>>().first)::ValueType
				>
			>
			&& std::same_as
			<
				std::remove_cvref_t<decltype(std::declval<std::ranges::range_value_t<T>>().second)>,
				CompositeOperandData
				<
					typename decltype(std::declval<std::ranges::range_value_t<T>>().second)::ValueType
				>
			>
		;


		constexpr inline CompositeOperandDataRange auto orderedOperandDataValues =
		{
			CompositeOperandData<double>
			{
				.value{ std::numeric_limits<double>::lowest() },
				.sign{ CmdCalculator::Arithmetic::ESign::Negative },
				.absoluteValue{},
				.negatedValue{},
				.incrementedValue{ std::numeric_limits<double>::lowest() + 1 },
				.decrementedValue{}
			},
			CompositeOperandData<double>
			{
				.value{ -56.78 },
				.sign{ CmdCalculator::Arithmetic::ESign::Negative },
				.absoluteValue{ std::make_optional<double>(56.78) },
				.negatedValue{ std::make_optional<double>(56.78) },
				.incrementedValue{ std::make_optional<double>(-55.78) },
				.decrementedValue{ std::make_optional<double>(-57.78) }
			},
			CompositeOperandData<double>
			{
				.value{ -12.34 },
				.sign{ CmdCalculator::Arithmetic::ESign::Negative },
				.absoluteValue{ std::make_optional<double>(12.34) },
				.negatedValue{ std::make_optional<double>(12.34) },
				.incrementedValue{ std::make_optional<double>(-11.34) },
				.decrementedValue{ std::make_optional<double>(-13.34) }
			},
			CompositeOperandData<double>
			{
				.value{ -2.0 },
				.sign{ CmdCalculator::Arithmetic::ESign::Negative },
				.absoluteValue{ std::make_optional<double>(2.0) },
				.negatedValue{ std::make_optional<double>(2.0) },
				.incrementedValue{ std::make_optional<double>(-1.0) },
				.decrementedValue{ std::make_optional<double>(-3.0) }
			},
			CompositeOperandData<double>
			{
				.value{ -1.5 },
				.sign{ CmdCalculator::Arithmetic::ESign::Negative },
				.absoluteValue{ std::make_optional<double>(1.5) },
				.negatedValue{ std::make_optional<double>(1.5) },
				.incrementedValue{ std::make_optional<double>(-0.5) },
				.decrementedValue{ std::make_optional<double>(-2.5) }
			},
			CompositeOperandData<double>
			{
				.value{ -1.0 },
				.sign{ CmdCalculator::Arithmetic::ESign::Negative },
				.absoluteValue{ std::make_optional<double>(1.0) },
				.negatedValue{ std::make_optional<double>(1.0) },
				.incrementedValue{ std::make_optional<double>(0.0) },
				.decrementedValue{ std::make_optional<double>(-2.0) }
			},
			CompositeOperandData<double>
			{
				.value{ -0.5 },
				.sign{ CmdCalculator::Arithmetic::ESign::Negative },
				.absoluteValue{ std::make_optional<double>(0.5) },
				.negatedValue{ std::make_optional<double>(0.5) },
				.incrementedValue{ std::make_optional<double>(0.5) },
				.decrementedValue{ std::make_optional<double>(-1.5) }
			},
			CompositeOperandData<double>
			{
				.value{ -std::numeric_limits<double>::min() },
				.sign{ CmdCalculator::Arithmetic::ESign::Negative },
				.absoluteValue{ std::make_optional<double>(std::numeric_limits<double>::min()) },
				.negatedValue{ std::make_optional<double>(std::numeric_limits<double>::min()) },
				.incrementedValue{ std::make_optional<double>(-std::numeric_limits<double>::min() + 1.0) },
				.decrementedValue{ std::make_optional<double>(-std::numeric_limits<double>::min() - 1.0) }
			},
			CompositeOperandData<double>
			{
				.value{ 0.0 },
				.sign{ CmdCalculator::Arithmetic::ESign::Neutral },
				.absoluteValue{ std::make_optional<double>(0.0) },
				.negatedValue{ std::make_optional<double>(0.0) },
				.incrementedValue{ std::make_optional<double>(1.0) },
				.decrementedValue{ std::make_optional<double>(-1.0) }
			},
			CompositeOperandData<double>
			{
				.value{ std::numeric_limits<double>::min() },
				.sign{ CmdCalculator::Arithmetic::ESign::Positive },
				.absoluteValue{ std::make_optional<double>(std::numeric_limits<double>::min()) },
				.negatedValue{ std::make_optional<double>(-std::numeric_limits<double>::min()) },
				.incrementedValue{ std::make_optional<double>(std::numeric_limits<double>::min() + 1.0) },
				.decrementedValue{ std::make_optional<double>(std::numeric_limits<double>::min() - 1.0) }
			},
			CompositeOperandData<double>
			{
				.value{ 0.5 },
				.sign{ CmdCalculator::Arithmetic::ESign::Positive },
				.absoluteValue{ std::make_optional<double>(0.5) },
				.negatedValue{ std::make_optional<double>(-0.5) },
				.incrementedValue{ std::make_optional<double>(1.5) },
				.decrementedValue{ std::make_optional<double>(-0.5) }
			},
			CompositeOperandData<double>
			{
				.value{ 1.0 },
				.sign{ CmdCalculator::Arithmetic::ESign::Positive },
				.absoluteValue{ std::make_optional<double>(1.0) },
				.negatedValue{ std::make_optional<double>(-1.0) },
				.incrementedValue{ std::make_optional<double>(2.0) },
				.decrementedValue{ std::make_optional<double>(0.0) }
			},
			CompositeOperandData<double>
			{
				.value{ 1.5 },
				.sign{ CmdCalculator::Arithmetic::ESign::Positive },
				.absoluteValue{ std::make_optional<double>(1.5) },
				.negatedValue{ std::make_optional<double>(-1.5) },
				.incrementedValue{ std::make_optional<double>(2.5) },
				.decrementedValue{ std::make_optional<double>(0.5) }
			},
			CompositeOperandData<double>
			{
				.value{ 2.0 },
				.sign{ CmdCalculator::Arithmetic::ESign::Positive },
				.absoluteValue{ std::make_optional<double>(2.0) },
				.negatedValue{ std::make_optional<double>(-2.0) },
				.incrementedValue{ std::make_optional<double>(3.0) },
				.decrementedValue{ std::make_optional<double>(1.0) }
			},
			CompositeOperandData<double>
			{
				.value{ 12.34 },
				.sign{ CmdCalculator::Arithmetic::ESign::Positive },
				.absoluteValue{ std::make_optional<double>(12.34) },
				.negatedValue{ std::make_optional<double>(-12.34) },
				.incrementedValue{ std::make_optional<double>(13.34) },
				.decrementedValue{ std::make_optional<double>(11.34) }
			},
			CompositeOperandData<double>
			{
				.value{ 56.78 },
				.sign{ CmdCalculator::Arithmetic::ESign::Positive },
				.absoluteValue{ std::make_optional<double>(56.78) },
				.negatedValue{ std::make_optional<double>(-56.78) },
				.incrementedValue{ std::make_optional<double>(57.78) },
				.decrementedValue{ std::make_optional<double>(55.78) }
			},
			CompositeOperandData<double>
			{
				.value{ std::numeric_limits<double>::max() },
				.sign{ CmdCalculator::Arithmetic::ESign::Positive },
				.absoluteValue{ std::numeric_limits<double>::max() },
				.negatedValue{},
				.incrementedValue{},
				.decrementedValue{ std::make_optional<double>(std::numeric_limits<double>::max() - 1.0) }
			}
		};
		static_assert(std::ranges::sized_range<decltype(orderedOperandDataValues)>);
		static_assert(std::ranges::random_access_range<decltype(orderedOperandDataValues)>);
		static_assert(std::ranges::is_sorted(orderedOperandDataValues));


		constexpr inline std::ranges::input_range auto orderedOperandDataIndexes
		{
			std::views::iota(0, std::ranges::ssize(orderedOperandDataValues))
		};

		using OrderedOperandDataIndexType = std::ranges::range_value_t<decltype(orderedOperandDataIndexes)>;
		static_assert(std::constructible_from<OrderedOperandDataIndexType, int>);

		constexpr inline CompositeOperandData<double> orderedOperandDataAt(const OrderedOperandDataIndexType index)
		{
			return *(std::ranges::cbegin(orderedOperandDataValues) + index);
		};


		constexpr inline CompositeOperandDataPairRange auto orderedOperandDataValuePairs()
		{
			return
				orderedOperandDataIndexes
				| std::views::transform
				(
					[](const OrderedOperandDataIndexType lhsIndex) constexpr
					{
						return
							orderedOperandDataIndexes
							| std::views::transform
							(
								[lhsIndex](const OrderedOperandDataIndexType rhsIndex) constexpr
								{
									return std::make_pair
									(
										orderedOperandDataAt(lhsIndex),
										orderedOperandDataAt(rhsIndex)
									);
								}
							)
						;
					}
				)
				| std::views::join
			;
		}


		const inline ArithmeticOperationValueRange auto numbers()
		{
			return
				orderedOperandDataValues
				| std::views::transform
				(
					[](const CompositeOperandData<double>& operandDataValue)
					{
						return operandDataValue.value;
					}
				)
			;
		};


		inline constexpr BinaryThreeWayComparisonOperationDataRange auto threeWayComparisonOperationDataValues()
		{
			return
				orderedOperandDataValuePairs()
				| std::views::transform
				(
					[](const auto pair)
					{
						return BinaryThreeWayComparisonOperationData<double>
						{
							.leftOperand{ pair.first.value },
							.rightOperand{ pair.second.value },
							.result
							{
								pair.first < pair.second
									? CmdCalculator::Arithmetic::ESign::Negative
									: pair.first > pair.second
										? CmdCalculator::Arithmetic::ESign::Positive
										: CmdCalculator::Arithmetic::ESign::Neutral
							}
						};
					}
				)
			;
		};


		inline constexpr BinaryBooleanOperationDataRange auto equalityOperationDataValues()
		{
			return
				orderedOperandDataValuePairs()
				| std::views::transform
				(
					[](const auto pair)
					{
						return BinaryBooleanOperationData<double>
						{
							.leftOperand{ pair.first.value },
							.rightOperand{ pair.second.value },
							.result{ pair.first == pair.second }
						};
					}
				)
			;
		};


		inline constexpr BinaryBooleanOperationDataRange auto inequalityOperationDataValues()
		{
			return
				orderedOperandDataValuePairs()
				| std::views::transform
				(
					[](const auto pair)
					{
						return BinaryBooleanOperationData<double>
						{
							.leftOperand{ pair.first.value },
							.rightOperand{ pair.second.value },
							.result{ pair.first != pair.second }
						};
					}
				)
			;
		};


		inline constexpr BinaryBooleanOperationDataRange auto lessThanOperationDataValues()
		{
			return
				orderedOperandDataValuePairs()
				| std::views::transform
				(
					[](const auto pair)
					{
						return BinaryBooleanOperationData<double>
						{
							.leftOperand{ pair.first.value },
							.rightOperand{ pair.second.value },
							.result{ pair.first < pair.second }
						};
					}
				)
			;
		};


		inline constexpr BinaryBooleanOperationDataRange auto lessThanEqualToOperationDataValues()
		{
			return
				orderedOperandDataValuePairs()
				| std::views::transform
				(
					[](const auto pair)
					{
						return BinaryBooleanOperationData<double>
						{
							.leftOperand{ pair.first.value },
							.rightOperand{ pair.second.value },
							.result{ pair.first <= pair.second }
						};
					}
				)
			;
		};


		inline constexpr BinaryBooleanOperationDataRange auto greaterThanOperationDataValues()
		{
			return
				orderedOperandDataValuePairs()
				| std::views::transform
				(
					[](const auto pair)
					{
						return BinaryBooleanOperationData<double>
						{
							.leftOperand{ pair.first.value },
							.rightOperand{ pair.second.value },
							.result{ pair.first > pair.second }
						};
					}
				)
			;
		};


		inline constexpr BinaryBooleanOperationDataRange auto greaterThanEqualToOperationDataValues()
		{
			return
				orderedOperandDataValuePairs()
				| std::views::transform
				(
					[](const auto pair)
					{
						return BinaryBooleanOperationData<double>
						{
							.leftOperand{ pair.first.value },
							.rightOperand{ pair.second.value },
							.result{ pair.first >= pair.second }
						};
					}
				)
			;
		};


		constexpr inline UnaryArithmeticOperationDataRange auto negationOperationsDataValues()
		{
			return
				orderedOperandDataValues
				| std::views::filter
				(
					[](const CompositeOperandData<double> operandDataValue)
					{ return operandDataValue.negatedValue.has_value(); }
				)
				| std::views::transform
				(
					[](const CompositeOperandData<double> operandDataValue)
					{
						return UnaryArithmeticOperationData<double>
						{
							.operand{ operandDataValue.value },
							.result{ operandDataValue.negatedValue.value() }
						};
					}
				)
			;
		};


		constexpr inline UnaryArithmeticOperationDataRange auto incrementationOperationsDataValues()
		{
			return
				orderedOperandDataValues
				| std::views::filter
				(
					[](const CompositeOperandData<double> operandDataValue)
					{ return operandDataValue.incrementedValue.has_value(); }
				)
				| std::views::transform
				(
					[](const CompositeOperandData<double> operandDataValue)
					{
						return UnaryArithmeticOperationData<double>
						{
							.operand{ operandDataValue.value },
							.result{ operandDataValue.incrementedValue.value() }
						};
					}
				)
			;
		};


		constexpr inline UnaryArithmeticOperationDataRange auto decrementationOperationsDataValues()
		{
			return
				orderedOperandDataValues
				| std::views::filter
				(
					[](const CompositeOperandData<double> operandDataValue)
					{ return operandDataValue.decrementedValue.has_value(); }
				)
				| std::views::transform
				(
					[](const CompositeOperandData<double> operandDataValue)
					{
						return UnaryArithmeticOperationData<double>
						{
							.operand{ operandDataValue.value },
							.result{ operandDataValue.decrementedValue.value() }
						};
					}
				)
			;
		};


		constexpr inline UnaryArithmeticOperationDataRange auto absoluteValueOperationsDataValues()
		{
			return
				orderedOperandDataValues
				| std::views::filter
				(
					[](const CompositeOperandData<double> operandDataValue)
					{ return operandDataValue.absoluteValue.has_value(); }
				)
				| std::views::transform
				(
					[](const CompositeOperandData<double> operandDataValue)
					{
						return UnaryArithmeticOperationData<double>
						{
							.operand{ operandDataValue.value },
							.result{ operandDataValue.absoluteValue.value() }
						};
					}
				)
			;
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

				{12.34, -56.78, 12.34},
				{-56.78, 12.34, 4.92},

				{-12.34, 56.78, 44.44},
				{56.78, -12.34, 7.42},

				{-12.34, -56.78, 44.44},
				{-56.78, -12.34, 4.92}
			}
		};


		template<class T>
		concept BinaryOperatorRange =
			std::ranges::input_range<T>
			&& std::same_as
			<
				CmdCalculator::MathAst::EBinaryOperator,
				std::remove_cvref_t<std::ranges::range_value_t<T>>
			>
		;

		template<class T>
		concept BinaryOperator2dRange =
			std::ranges::input_range<T>
			&& BinaryOperatorRange
			<
				std::ranges::range_value_t<T>
			>
		;

		constexpr inline BinaryOperatorRange auto binaryOperators
		{
			std::initializer_list<CmdCalculator::MathAst::EBinaryOperator>
			{
				CmdCalculator::MathAst::EBinaryOperator::Addition,
				CmdCalculator::MathAst::EBinaryOperator::Subtraction,
				CmdCalculator::MathAst::EBinaryOperator::Multiplication,
				CmdCalculator::MathAst::EBinaryOperator::Division,
				CmdCalculator::MathAst::EBinaryOperator::Exponentiation,
				CmdCalculator::MathAst::EBinaryOperator::NthRoot,
				CmdCalculator::MathAst::EBinaryOperator::Modulo
			}
		};

		
		struct BinaryOperatorData
		{
			CmdCalculator::MathAst::EBinaryOperator binaryOperator;
			std::optional<CmdCalculator::MathAst::EBinaryOperator> inverse;
		};
		
		template<class T>
		concept BinaryOperatorDataRange =
			std::ranges::input_range<T>
			&& std::same_as
			<
				BinaryOperatorData,
				std::remove_cvref_t<std::ranges::range_value_t<T>>
			>
		;

		constexpr inline BinaryOperatorDataRange auto orderedBinaryOperatorDataValues
		{
			std::initializer_list<BinaryOperatorData>
			{
				BinaryOperatorData
				{
					.binaryOperator{ CmdCalculator::MathAst::EBinaryOperator::Modulo },
					.inverse{},
				},
				BinaryOperatorData
				{
					.binaryOperator{ CmdCalculator::MathAst::EBinaryOperator::Exponentiation },
					.inverse{ std::make_optional<CmdCalculator::MathAst::EBinaryOperator>(CmdCalculator::MathAst::EBinaryOperator::NthRoot) },
				},
				BinaryOperatorData
				{
					.binaryOperator{ CmdCalculator::MathAst::EBinaryOperator::Multiplication },
					.inverse{ std::make_optional<CmdCalculator::MathAst::EBinaryOperator>(CmdCalculator::MathAst::EBinaryOperator::Division) },
				},
				BinaryOperatorData
				{
					.binaryOperator{ CmdCalculator::MathAst::EBinaryOperator::Addition },
					.inverse{ std::make_optional<CmdCalculator::MathAst::EBinaryOperator>(CmdCalculator::MathAst::EBinaryOperator::Subtraction) },
				}
			}
		};


		constexpr inline BinaryOperator2dRange auto orderedBinaryOperators
		{
			orderedBinaryOperatorDataValues
			| std::views::transform
			(
				[](const BinaryOperatorData& data)
				{
					if (data.inverse.has_value())
					{
						return std::initializer_list<CmdCalculator::MathAst::EBinaryOperator>
						{
							data.binaryOperator,
							data.inverse.value()
						};
					}
					return std::initializer_list<CmdCalculator::MathAst::EBinaryOperator>
					{
						data.binaryOperator
					};
				}
			)
		};


		constexpr inline std::integral auto numberOfBinaryOperatorPrecedenceLevels{ std::ranges::ssize(orderedBinaryOperatorDataValues) };
		static_assert(numberOfBinaryOperatorPrecedenceLevels >= 0);

		constexpr inline IntegralRange auto binaryOperatorPrecedenceLevels
		{
			std::views::iota(0, numberOfBinaryOperatorPrecedenceLevels)
		};


		constexpr inline BinaryOperatorRange auto getBinaryOperatorsAtPrecedenceLevel(const std::integral auto level)
		{
			return *(std::ranges::begin(orderedBinaryOperators) + numberOfBinaryOperatorPrecedenceLevels - level);
		}
	}
}