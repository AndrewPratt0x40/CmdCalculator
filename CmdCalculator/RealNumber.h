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
	template<class T>
	concept RealNumber =
		IntendsToSatisfy<T, RealNumber_IntendedSatisfaction>
		&& std::copyable<T>
		&& std::totally_ordered<T>
		&& requires()
		{
			{ T::getZero() } -> std::same_as<T>;
		}
		&& requires(T&& instance)
		{
			{ instance.getStringRepresentation() } -> String;
			{ ++instance } -> std::same_as<T&>;
			{ instance++ } -> std::same_as<T>;
			{ --instance } -> std::same_as<T&>;
			{ instance-- } -> std::same_as<T>;
			{ instance.getSign() } -> std::same_as<ESign>;
			{ instance.getAbsoluteValue() } -> std::same_as<T>;
		}
		&& requires(T&& instance, T&& operand)
		{
			{ instance + operand } -> std::same_as<T>;
			{ instance += operand } -> std::same_as<T&>;
			{ instance - operand } -> std::same_as<T>;
			{ instance -= operand } -> std::same_as<T&>;
			{ instance * operand } -> std::same_as<T>;
			{ instance *= operand } -> std::same_as<T&>;
			{ instance / operand } -> std::same_as<T>;
			{ instance /= operand } -> std::same_as<T&>;
			{ instance % operand } -> std::same_as<T>;
			{ instance %= operand } -> std::same_as<T&>;
			{ instance.pow(operand) } -> std::same_as<T>;
			{ instance.nthRoot(operand) } -> std::same_as<T>;
		}
	;
}