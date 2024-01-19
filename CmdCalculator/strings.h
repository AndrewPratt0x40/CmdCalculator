#pragma once

#include<string>
#include<assert.h>
#include<locale>


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


	/// \brief Converts the character type of a string.
	/// \tparam ToCharT The type of characters to convert to.
	/// \tparam FromT The type of string to convert from.
	/// \param from The string to convert.
	/// /param locale The locale to use.
	/// \returns \p from as a string of \p ToCharT characters.
	template<class ToCharT, String FromT>
	std::basic_string<ToCharT> convertString(const FromT& from, const std::locale& locale)
	{
		using CharConvertFacetType = std::codecvt
		<
			typename FromT::value_type,
			ToCharT,
			std::mbstate_t
		>;

		assert(std::has_facet<CharConvertFacetType>(locale));

		if (from.empty())
			return std::basic_string<ToCharT>{};

		const CharConvertFacetType& charConvertFacet{ std::use_facet<CharConvertFacetType>(locale) };
		
		std::basic_string<typename FromT::value_type> fromAsStdString{ from };

		assert(!charConvertFacet.always_noconv());

		std::mbstate_t state{};
		const typename FromT::value_type* fromAsStdStringNext;
		ToCharT* toNext;

		std::basic_string<ToCharT> to{};
		to.resize
		(
			fromAsStdString.size() * static_cast<decltype(fromAsStdString.size())>(charConvertFacet.max_length()),
			static_cast<ToCharT>(0)
		);

		const std::codecvt_base::result result
		{
			charConvertFacet.out
			(
				state,
				&fromAsStdString.front(),
				&fromAsStdString[fromAsStdString.size()],
				fromAsStdStringNext,
				&to.front(),
				&to[to.size()],
				toNext
			)
		};

		assert(result != std::codecvt_base::noconv);

		if (result != std::codecvt_base::ok)
			throw std::runtime_error{ "Failed to convert string for unknown reason" };

		to.resize(std::distance(&to.front(), toNext));

		return to;
	}


	/// \brief Converts the character type of a string.
	/// \tparam ToCharT The type of characters to convert to.
	/// \tparam FromT The type of string to convert from.
	/// \param from The string to convert.
	/// /param locale The locale to use.
	/// \returns \p from as a string of \p ToCharT characters.
	template<class ToCharT, String FromT>
		requires StringOfChar<FromT, ToCharT>
	std::basic_string<ToCharT> convertString(const FromT& from, const std::locale& locale)
	{
		return static_cast<std::basic_string<ToCharT>>(from);
	}


	/// \brief Converts the character type of a string.
	/// \tparam ToCharT The type of characters to convert to.
	/// \tparam FromT The type of string to convert from.
	/// \param from The string to convert.
	/// /param locale The locale to use.
	/// \returns \p from as a string of \p ToCharT characters.
	template<class ToCharT, String FromT>
	std::basic_string<ToCharT> convertString(FromT&& from, const std::locale& locale)
	{
		// Calls version with from as an lvalue reference
		return convertString<ToCharT>(from, locale);
	}


	/// \brief Converts the character type of a string.
	/// \tparam ToCharT The type of characters to convert to.
	/// \tparam FromT The type of string to convert from.
	/// \param from The string to convert.
	/// \returns \p from as a string of \p ToCharT characters.
	/// \remark The current global \ref std::locale instance will be used.
	template<class ToCharT, String FromT>
	std::basic_string<ToCharT> convertString(const FromT& from)
	{
		std::locale locale{};
		return convertString<ToCharT, FromT>(from, locale);
	}


	/// \brief Converts the character type of a string.
	/// \tparam ToCharT The type of characters to convert to.
	/// \tparam FromT The type of string to convert from.
	/// \param from The string to convert.
	/// \returns \p from as a string of \p ToCharT characters.
	/// \remark The current global \ref std::locale instance will be used.
	template<class ToCharT, String FromT>
	std::basic_string<ToCharT> convertString(FromT&& from)
	{
		// Calls version with from as an lvalue reference
		return convertString<ToCharT, FromT>(from);
	}


	/// \brief Converts a character's type.
	/// \tparam ToT The type of character to convert to.
	/// \tparam FromT The type of character to convert from.
	/// \param from The character to convert.
	/// /param locale The locale to use.
	/// \returns \p from as a \p ToT value.
	template<class ToT, class FromT>
	ToT convertChar(const FromT from, const std::locale& locale)
	{
		const std::basic_string<ToT> convertedString{ convertString<ToT>(std::basic_string<FromT>{ from }, locale) };
		assert(convertedString.length() == 1);
		return convertedString.front();
	}


	/// \brief Converts a character's type.
	/// \tparam ToT The type of character to convert to.
	/// \tparam FromT The type of character to convert from.
	/// \param from The character to convert.
	/// \returns \p from as a \p ToT value.
	/// \remark The current global \ref std::locale instance will be used.
	template<class ToT, class FromT>
	ToT convertChar(const FromT from)
	{
		std::locale locale{};
		return convertChar<ToT>(from, locale);
	}
}