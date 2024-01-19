#pragma once

#include <concepts>
#include <ranges>
#include <iterator>
#include <utility>

/// \internal
namespace CmdCalculator::Polyfills
{
#ifdef __cpp_lib_unreachable
	using std::unreachable;
#else
	// Source code from Cppreference.
	// Minor modifications were made to allow code to compile in this project.
	// See original: https://en.cppreference.com/w/cpp/utility/unreachable
	// See Cppreference copyright: https://en.cppreference.com/w/Cppreference:Copyright/CC-BY-SA

	[[noreturn]] inline void unreachable()
	{
		// Uses compiler specific extensions if possible.
		// Even if no extension is used, undefined behavior is still raised by
		// an empty function body and the noreturn attribute.
#if defined(_MSC_VER) && !defined(__clang__) // MSVC
		__assume(false);
#else // GCC, Clang
		__builtin_unreachable();
#endif
	}
#endif


	namespace ranges
	{
#ifdef __cpp_lib_ranges_fold
		using std::ranges::fold_left;
#else
		// Source code from Cppreference.
		// Minor modifications were made to allow code to compile in this project.
		// See original: https://en.cppreference.com/w/cpp/algorithm/ranges/fold_left
		// See Cppreference copyright: https://en.cppreference.com/w/Cppreference:Copyright/CC-BY-SA

		template< class F, class T, class I, class U >
		concept __indirectly_binary_left_foldable_impl =
			std::movable<T> &&
			std::movable<U> &&
			std::convertible_to<T, U>&&
			std::invocable<F&, U, std::iter_reference_t<I>>&&
			std::assignable_from<U&,
			std::invoke_result_t<F&, U, std::iter_reference_t<I>>>;
		
		
		template< class F, class T, class I >
		concept __indirectly_binary_left_foldable =
			std::copy_constructible<F> &&
			std::indirectly_readable<I> &&
			std::invocable<F&, T, std::iter_reference_t<I>>&&
			std::convertible_to<std::invoke_result_t<F&, T, std::iter_reference_t<I>>,
			std::decay_t<std::invoke_result_t<F&, T, std::iter_reference_t<I>>>>&&
			__indirectly_binary_left_foldable_impl<F, T, I,
			std::decay_t<std::invoke_result_t<F&, T, std::iter_reference_t<I>>>>;
		
		struct fold_left_fn
		{
			template<std::input_iterator I, std::sentinel_for<I> S, class T,
					 __indirectly_binary_left_foldable<T, I> F>
			constexpr auto operator()( I first, S last, T init, F f ) const
			{
				using U = std::decay_t<std::invoke_result_t<F&, T, std::iter_reference_t<I>>>;
				if (first == last)
					return U(std::move(init));
				U accum = std::invoke(f, std::move(init), *first);
				for (++first; first != last; ++first)
					accum = std::invoke(f, std::move(accum), *first);
				return std::move(accum);
			}
 
			template<std::ranges::input_range R, class T,
					 __indirectly_binary_left_foldable<T, std::ranges::iterator_t<R>> F>
			constexpr auto operator()( R&& r, T init, F f ) const
			{
				return (*this)(std::ranges::begin(r), std::ranges::end(r), std::move(init), std::ref(f));
			}
		};
 
		inline constexpr fold_left_fn fold_left;
#endif // !__cpp_lib_ranges_fold
	}
}
/// \endinternal