#include "pch.h"

#include <concepts>

#include "common.h"
#include "..\CmdCalculator\NotImplementedException.h"
#include "..\CmdCalculator\strings.h"

namespace CmdCalculatorTests
{
#pragma region StringOfChar
	
	template<class StringT, class CharT, bool shouldSatisfyT>
	struct StringOfChar_TypeParams
	{
		using StringType = StringT;
		using CharType = CharT;
		static constexpr bool shouldSatisfy = shouldSatisfyT;
	};


	template<class T>
	class StringOfCharFixture :
		public testing::Test
	{};
	TYPED_TEST_CASE_P(StringOfCharFixture);

	using StringOfChar_TypeParamValues = testing::Types
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


	TYPED_TEST_P(StringOfCharFixture, Only$expected$types$satisfy)
	{
		// Arrange
		const bool expectSatisfaction{ TypeParam::shouldSatisfy };
		const bool isSatisfactory{ CmdCalculator::StringOfChar<typename TypeParam::StringType, typename TypeParam::CharType> };

		// Assert
		EXPECT_EQ(expectSatisfaction, isSatisfactory);
	}


	REGISTER_TYPED_TEST_CASE_P(StringOfCharFixture, Only$expected$types$satisfy);
	INSTANTIATE_TYPED_TEST_CASE_P(SimpleTypes, StringOfCharFixture, StringOfChar_TypeParamValues);

#pragma endregion


#pragma region String

	template<class StringT, bool shouldSatisfyT>
	struct String_TypeParams
	{
		using StringType = StringT;
		static constexpr bool shouldSatisfy = shouldSatisfyT;
	};


	template<class T>
	class StringFixture :
		public testing::Test
	{};
	TYPED_TEST_CASE_P(StringFixture);

	using String_TypeParamValues = testing::Types
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


	TYPED_TEST_P(StringFixture, Only$expected$types$satisfy)
	{
		// Arrange
		const bool expectSatisfaction{ TypeParam::shouldSatisfy };
		const bool isSatisfactory{ CmdCalculator::String<typename TypeParam::StringType> };

		// Assert
		EXPECT_EQ(expectSatisfaction, isSatisfactory);
	}


	REGISTER_TYPED_TEST_CASE_P(StringFixture, Only$expected$types$satisfy);
	INSTANTIATE_TYPED_TEST_CASE_P(SimpleTypes, StringFixture, String_TypeParamValues);

#pragma endregion
}