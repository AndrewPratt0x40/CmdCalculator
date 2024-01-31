#pragma once

#include <concepts>


namespace CmdCalculator::Arithmetic
{
	/// \brief A real number.
	/// \tparam T The real number type.
	template<class T>
	concept RealNumber =
		std::constructible_from<T, int>
		&& std::copyable<T>
		&& std::totally_ordered<T>
		&& requires(T&& instance)
		{
			{ instance.getAbsoluteValue() } -> std::same_as<T>;
		}
		&& requires(T&& instance, T&& operand)
		{
			{ instance + operand } -> std::same_as<T>;
			{ instance - operand } -> std::same_as<T>;
			{ instance * operand } -> std::same_as<T>;
			{ instance / operand } -> std::same_as<T>;
			{ instance % operand } -> std::same_as<T>;
			{ instance.pow(operand) } -> std::same_as<T>;
			{ instance.root(operand) } -> std::same_as<T>;
			{ instance.abs(operand) } -> std::same_as<T>;
		}
	;
}