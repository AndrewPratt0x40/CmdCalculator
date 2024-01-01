#pragma once

#include<string>


namespace CmdCalculator
{
	/// \brief A string type.
	/// \tparam T The string type.
	/// \tparam CharT The type of the characters of \p T.
	/// \details To satisfy this concept, \p T must be able to be represented by std::basic_string<\p CharT>>.
	template<class T, class CharT>
	concept StringOfChar = std::convertible_to<T, std::basic_string<CharT>>;

	/// \brief A string type.
	/// \tparam T The string type.
	/// \details To satisfy this concept, \p T must be able to be represented by std::basic_string.
	template<class T>
	concept String =
		requires()
		{
			typename T::value_type;
			typename T::traits_type;
			typename T::allocator_type;
		}
		&& StringOfChar<T, typename T::value_type>
	;


	/// \brief A string view type.
	/// \tparam T The string view type.
	/// \tparam CharT The type of the characters of \p T.
	/// \details To satisfy this concept, \p T must be able to be represented by std::basic_string_view<\p CharT>>.
	template<class T, class CharT>
	concept StringViewOfChar = std::convertible_to<T, std::basic_string_view<CharT>>;

	/// \brief A string view type.
	/// \tparam T The string view type.
	/// \details To satisfy this concept, \p T must be able to be represented by std::basic_string_view.
	template<class T>
	concept StringView =
		requires()
		{
			typename T::value_type;
			typename T::traits_type;
		}
		&& StringViewOfChar<T, typename T::value_type>
	;
}