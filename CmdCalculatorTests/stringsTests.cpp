#include "pch.h"

#include <concepts>
#include <string>

#include "common.h"
#include "..\CmdCalculator\NotImplementedException.h"
#include "..\CmdCalculator\strings.h"

using namespace std::string_literals;
using namespace std::string_view_literals;

namespace CmdCalculatorTests
{
#pragma region StringOfChar
	
	template<class StringT, class CharT, bool shouldSatisfyT>
	struct StringOfChar_TypeParams
	{
		using StringType = StringT;
		using CharType = CharT;
		static constexpr bool shouldSatisfy{ shouldSatisfyT };
	};


	template<class T>
	class StringOfCharTests :
		public testing::Test
	{};

	using StringOfCharTests_Types = testing::Types
	<
		StringOfChar_TypeParams<int, EmptyStruct, false>,
		StringOfChar_TypeParams<int, char, false>,
		StringOfChar_TypeParams<int, wchar_t, false>,
		StringOfChar_TypeParams<std::basic_string<char>, EmptyStruct, false>,
		StringOfChar_TypeParams<std::basic_string<char>, char, true>,
		StringOfChar_TypeParams<std::basic_string<char>, wchar_t, false>,
		StringOfChar_TypeParams<std::basic_string<wchar_t>, EmptyStruct, false>,
		StringOfChar_TypeParams<std::basic_string<wchar_t>, char, false>,
		StringOfChar_TypeParams<std::basic_string<wchar_t>, wchar_t, true>
	>;

	TYPED_TEST_CASE(StringOfCharTests, StringOfCharTests_Types);


	TYPED_TEST(StringOfCharTests, Only$expected$types$satisfy)
	{
		// Arrange
		const bool expectSatisfaction{ TypeParam::shouldSatisfy };
		const bool isSatisfactory{ CmdCalculator::StringOfChar<typename TypeParam::StringType, typename TypeParam::CharType> };

		// Assert
		EXPECT_EQ(expectSatisfaction, isSatisfactory);
	}

#pragma endregion


#pragma region String

	template<class StringT, bool shouldSatisfyT>
	struct String_TypeParams
	{
		using StringType = StringT;
		static constexpr bool shouldSatisfy = shouldSatisfyT;
	};


	template<class T>
	class StringTests :
		public testing::Test
	{};

	using StringTests_Types = testing::Types
	<
		String_TypeParams<int, false>,
		String_TypeParams<EmptyStruct, false>,
		String_TypeParams<char, false>,
		String_TypeParams<wchar_t, false>,
		String_TypeParams<std::basic_string<int>, true>,
		String_TypeParams<std::basic_string<EmptyStruct>, true>,
		String_TypeParams<std::basic_string<char>, true>,
		String_TypeParams<std::basic_string<wchar_t>, true>
	>;

	TYPED_TEST_CASE(StringTests, StringTests_Types);


	TYPED_TEST(StringTests, Only$expected$types$satisfy)
	{
		// Arrange
		const bool expectSatisfaction{ TypeParam::shouldSatisfy };
		const bool isSatisfactory{ CmdCalculator::String<typename TypeParam::StringType> };

		// Assert
		EXPECT_EQ(expectSatisfaction, isSatisfactory);
	}

#pragma endregion


#pragma region StringViewOfChar

	template<class StringViewT, class CharT, bool shouldSatisfyT>
	struct StringViewOfChar_TypeParams
	{
		using StringViewType = StringViewT;
		using CharType = CharT;
		static constexpr bool shouldSatisfy = shouldSatisfyT;
	};


	template<class T>
	class StringViewOfCharTests :
		public testing::Test
	{};

	using StringViewOfCharTests_Types = testing::Types
	<
		StringViewOfChar_TypeParams<int, EmptyStruct, false>,
		StringViewOfChar_TypeParams<int, char, false>,
		StringViewOfChar_TypeParams<int, wchar_t, false>,
		StringViewOfChar_TypeParams<std::basic_string_view<char>, EmptyStruct, false>,
		StringViewOfChar_TypeParams<std::basic_string_view<char>, char, true>,
		StringViewOfChar_TypeParams<std::basic_string_view<char>, wchar_t, false>,
		StringViewOfChar_TypeParams<std::basic_string_view<wchar_t>, EmptyStruct, false>,
		StringViewOfChar_TypeParams<std::basic_string_view<wchar_t>, char, false>,
		StringViewOfChar_TypeParams<std::basic_string_view<wchar_t>, wchar_t, true>
	>;

	TYPED_TEST_CASE(StringViewOfCharTests, StringViewOfCharTests_Types);


	TYPED_TEST(StringViewOfCharTests, Only$expected$types$satisfy)
	{
		// Arrange
		const bool expectSatisfaction{ TypeParam::shouldSatisfy };
		const bool isSatisfactory{ CmdCalculator::StringViewOfChar<typename TypeParam::StringViewType, typename TypeParam::CharType> };

		// Assert
		EXPECT_EQ(expectSatisfaction, isSatisfactory);
	}

#pragma endregion


#pragma region StringView

	template<class StringViewT, bool shouldSatisfyT>
	struct StringView_TypeParams
	{
		using StringViewType = StringViewT;
		static constexpr bool shouldSatisfy = shouldSatisfyT;
	};


	template<class T>
	class StringViewTests :
		public testing::Test
	{};

	using StringViewTests_Types = testing::Types
	<
		StringView_TypeParams<int, false>,
		StringView_TypeParams<EmptyStruct, false>,
		StringView_TypeParams<char, false>,
		StringView_TypeParams<wchar_t, false>,
		StringView_TypeParams<std::basic_string_view<int>, true>,
		StringView_TypeParams<std::basic_string_view<EmptyStruct>, true>,
		StringView_TypeParams<std::basic_string_view<char>, true>,
		StringView_TypeParams<std::basic_string_view<wchar_t>, true>
	>;

	TYPED_TEST_CASE(StringViewTests, StringViewTests_Types);


	TYPED_TEST(StringViewTests, Only$expected$types$satisfy)
	{
		// Arrange
		const bool expectSatisfaction{ TypeParam::shouldSatisfy };
		const bool isSatisfactory{ CmdCalculator::StringView<typename TypeParam::StringViewType> };

		// Assert
		EXPECT_EQ(expectSatisfaction, isSatisfactory);
	}

#pragma endregion


#pragma region convertString

	namespace convertString_TypeParams_StringInfo
	{
		template<class T>
		concept StringInfo = requires()
		{
			typename T::CharType;
			{ T::getValue() } -> std::same_as<std::basic_string<typename T::CharType>>;
		};


		struct CharStringInfo
		{
			using CharType = char;
			static std::basic_string<char> getValue()
			{
				return "Hello, world!"s;
			}
		};

		struct WCharStringInfo
		{
			using CharType = wchar_t;
			static std::basic_string<wchar_t> getValue()
			{
				return L"Hello, world!"s;
			}
		};

		struct Char8StringInfo
		{
			using CharType = char8_t;
			static std::basic_string<char8_t> getValue()
			{
				return u8"Hello, world!"s;
			}
		};

		struct Char16StringInfo
		{
			using CharType = char16_t;
			static std::basic_string<char16_t> getValue()
			{
				return u"Hello, world!"s;
			}
		};

		struct Char32StringInfo
		{
			using CharType = char32_t;
			static std::basic_string<char32_t> getValue()
			{
				return U"Hello, world!"s;
			}
		};
	}


	template
	<
		convertString_TypeParams_StringInfo::StringInfo FromT,
		convertString_TypeParams_StringInfo::StringInfo ToT
	>
	struct convertString_TypeParams
	{
		using FromStringType = std::basic_string<typename FromT::CharType>;
		using ToCharType = ToT::CharType;

		static FromStringType getFrom()
		{
			return FromT::getValue();
		}

		static std::basic_string<ToCharType> getExpected()
		{
			return ToT::getValue();
		}
	};
	
	
	template<class T>
	class convertStringTests :
		public testing::Test
	{};

	using convertString_Types = testing::Types
	<
		// See: https://en.cppreference.com/w/cpp/locale/codecvt#Specializations
		// TODO: Remove deprecated conversions?
		convertString_TypeParams
		<
			convertString_TypeParams_StringInfo::CharStringInfo,
			convertString_TypeParams_StringInfo::CharStringInfo
		>,
		convertString_TypeParams
		<
			convertString_TypeParams_StringInfo::Char16StringInfo,
			convertString_TypeParams_StringInfo::CharStringInfo
		>,
		convertString_TypeParams
		<
			convertString_TypeParams_StringInfo::CharStringInfo,
			convertString_TypeParams_StringInfo::Char16StringInfo
		>,
		convertString_TypeParams
		<
			convertString_TypeParams_StringInfo::Char16StringInfo,
			convertString_TypeParams_StringInfo::Char8StringInfo
		>,
		convertString_TypeParams
		<
			convertString_TypeParams_StringInfo::Char8StringInfo,
			convertString_TypeParams_StringInfo::Char16StringInfo
		>,
		convertString_TypeParams
		<
			convertString_TypeParams_StringInfo::Char32StringInfo,
			convertString_TypeParams_StringInfo::CharStringInfo
		>,
		convertString_TypeParams
		<
			convertString_TypeParams_StringInfo::CharStringInfo,
			convertString_TypeParams_StringInfo::Char32StringInfo
		>,
		convertString_TypeParams
		<
			convertString_TypeParams_StringInfo::Char32StringInfo,
			convertString_TypeParams_StringInfo::Char8StringInfo
		>,
		convertString_TypeParams
		<
			convertString_TypeParams_StringInfo::Char8StringInfo,
			convertString_TypeParams_StringInfo::Char32StringInfo
		>,
		convertString_TypeParams
		<
			convertString_TypeParams_StringInfo::WCharStringInfo,
			convertString_TypeParams_StringInfo::CharStringInfo
		>,
		convertString_TypeParams
		<
			convertString_TypeParams_StringInfo::CharStringInfo,
			convertString_TypeParams_StringInfo::WCharStringInfo
		>
	>;

	TYPED_TEST_CASE(convertStringTests, convertString_Types);


	TYPED_TEST(convertStringTests, convertString$returns$expected$value)
	{
		// Arrange
		using FromStringType = typename TypeParam::FromStringType;
		using ToCharType = typename TypeParam::ToCharType;
		FromStringType from{ TypeParam::getFrom()};
		std::basic_string<ToCharType> expected{ TypeParam::getExpected()};

		// Act
		std::basic_string<ToCharType> actual{ CmdCalculator::convertString<ToCharType>(from) };

		// Assert
		//EXPECT_EQ(expected, actual); // <- Causes issues with gtest
		EXPECT_TRUE(expected == actual);
	}


	TYPED_TEST(convertStringTests, convertString$with$empty$string$returns$empty$converted$string)
	{
		// Arrange
		using FromStringType = typename TypeParam::FromStringType;
		using ToCharType = typename TypeParam::ToCharType;
		FromStringType from{};

		// Act
		std::basic_string<ToCharType> actual{ CmdCalculator::convertString<ToCharType>(from) };

		// Assert
		EXPECT_TRUE(actual.empty());
	}

#pragma endregion
}