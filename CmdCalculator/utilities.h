#pragma once

#include <type_traits>
#include <optional>

#include "NotImplementedException.h"

namespace CmdCalculator
{
	/// \brief Describes any type that is \ref std::optional.
	/// \tparam T The optional type.
	template<class T>
	concept Optional = std::same_as<T, std::optional<typename T::value_type>>;


	/// \brief Describes any type that may be dereferenced via the * operator.
	/// \tparam The dereferenceable type.
	template<class T>
	concept Dereferenceable =
		requires(T && instance)
		{
			*instance;
		}
	;


	/// \brief Determines the type that results from dereferencing a given type.
	/// \tparam DereferenceableT The type to dereference.
	/// \example <tt>DereferencedType<int*></tt> would yield <tt>int</tt>.
	/// \example <tt>DereferencedType<int**></tt> would yield <tt>int*</tt>.
	/// \example <tt>DereferencedType<std::shared_ptr<int>></tt> would yield <tt>int</tt>.
	template<Dereferenceable DereferenceableT>
	using DereferencedType = decltype(*declval<DereferenceableT>());


	/// \brief Describes any type that is a range of elements that may be dereferenced via the * operator.
	/// \tparam The range of dereferenceable elements type.
	template<class T>
	concept RangeOfDereferenceableElements =
		std::ranges::range<T>
		&& Dereferenceable<std::ranges::range_value_t<T>>
	;


	/// \brief Determines the type that results from dereferencing an element of a given range type.
	/// \tparam RangeOfDereferenceableElementsT The type who's element type to dereference.
	/// \example <tt>DereferencedRangeElementType<std::vector<int*>></tt> would yield <tt>int</tt>.
	/// \example <tt>DereferencedRangeElementType<std::vector<std::shared_ptr<int>>></tt> would yield <tt>int</tt>.
	template<RangeOfDereferenceableElements RangeOfDereferenceableElementsT>
	using DereferencedRangeElementType = decltype(*std::declval<std::ranges::range_value_t<RangeOfDereferenceableElementsT>>());


	/// \brief Converts a pointer to an optional reference object.
	/// \tparam ValueT The type pointed to.
	/// \param pointer The pointer to convert.
	/// \returns An optional object holding a reference to the value pointed to by \p pointer, or an empty value if \p pointer is null.
	template<class ValueT>
	std::optional<std::reference_wrapper<ValueT>> pointerAsOptionalReference(ValueT* pointer)
	{
		return pointer
			? std::make_optional(std::ref(*pointer))
			: std::optional<std::reference_wrapper<ValueT>>{}
		;
	}


	/// \brief Converts a pointer to an optional read-only reference object.
	/// \tparam ValueT The type pointed to.
	/// \param pointer The pointer to convert.
	/// \returns An optional object holding a reference to the value pointed to by \p pointer, or an empty value if \p pointer is null.
	template<class ValueT>
	std::optional<std::reference_wrapper<const ValueT>> pointerAsOptionalConstReference(const ValueT* pointer)
	{
		return pointer
			? std::make_optional(std::cref(*pointer))
			: std::optional<std::reference_wrapper<const ValueT>>{}
		;
	}
}