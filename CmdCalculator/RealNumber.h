#pragma once

#include <concepts>

#include "ESign.h"
#include "strings.h"
#include "utilities.h"


namespace CmdCalculator::Arithmetic
{
	/// \brief The base type for types that are intended to satisfy the \ref RealNumber concept.
	struct RealNumber_IntendedSatisfaction
	{};


	/// \brief A real number.
	/// \tparam T The real number type.
	/// \remark Modulo operations should use Euclidean division, and always return a positive value.
	template<class T>
	concept RealNumber =
		IntendsToSatisfy<T, RealNumber_IntendedSatisfaction>
		&& std::copyable<T>
		&& std::totally_ordered<T>
		&& requires()
		{
			{ T::getZero() } -> std::convertible_to<T>;
		}
		&& requires(T&& instance)
		{
			{ instance.getStringRepresentation() } -> String;
			{ instance.getSign() } -> std::same_as<ESign>;
			{ -instance } -> std::convertible_to<T>;
			{ ++instance } -> std::same_as<T&>;
			{ instance++ } -> std::convertible_to<T>;
			{ --instance } -> std::same_as<T&>;
			{ instance-- } -> std::convertible_to<T>;
			{ instance.getAbsoluteValue() } -> std::convertible_to<T>;
			{ instance.getWholePart() } -> std::convertible_to<T>;
		}
		&& requires(T&& instance, T&& operand)
		{
			{ instance + operand } -> std::convertible_to<T>;
			{ instance += operand } -> std::same_as<T&>;
			{ instance - operand } -> std::convertible_to<T>;
			{ instance -= operand } -> std::same_as<T&>;
			{ instance * operand } -> std::convertible_to<T>;
			{ instance *= operand } -> std::same_as<T&>;
			{ instance / operand } -> std::convertible_to<T>;
			{ instance /= operand } -> std::same_as<T&>;
			{ instance % operand } -> std::convertible_to<T>;
			{ instance %= operand } -> std::same_as<T&>;
			{ instance.pow(operand) } -> std::convertible_to<T>;
			{ instance.nthRoot(operand) } -> std::convertible_to<T>;
		}
	;
}