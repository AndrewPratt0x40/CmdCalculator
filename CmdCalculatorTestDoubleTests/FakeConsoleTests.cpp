#include "pch.h"

#include <string>
#include <string_view>
#include <initializer_list>
#include <ranges>
#include <algorithm>

#include "../CmdCalculator/NotImplementedException.h"
#include "../CmdCalculatorTestDoubles/FakeConsole.h"

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	template<class T>
	class FakeConsoleWithCharTypeTests :
		public testing::Test
	{};

	using FakeConsoleWithCharTypeTests_Types = testing::Types
	<
		char,
		wchar_t
	>;

	TYPED_TEST_CASE(FakeConsoleWithCharTypeTests, FakeConsoleWithCharTypeTests_Types);


	TYPED_TEST(FakeConsoleWithCharTypeTests, FakeConsole$satisfies$Console$concept)
	{
		EXPECT_TRUE(CmdCalculator::Console<CmdCalculatorTestDoubles::FakeConsole<TypeParam>>);
	}

#pragma endregion


#pragma region Constructors

#pragma region Default constructor

	TEST(FakeConsoleDefaultConstructorTests, Default$constructor$sets$next$input$to$a$valid$value)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{};

		// Assert
		EXPECT_NO_THROW( instance.FAKE_getNextInput(); );
	}


	TEST(FakeConsoleDefaultConstructorTests, Default$constructor$sets$no$text$spans)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{};

		// Assert
		EXPECT_TRUE(std::ranges::empty(instance.FAKE_getTextSpans()));
	}

#pragma endregion


#pragma region Constructor with text spans

	struct FakeConsole_CtorParams
	{
		const std::string nextInput;
		const std::initializer_list<CmdCalculatorTestDoubles::FakeConsole<char>::TextSpan> textSpans;
	};
	
	
	class FakeConsoleConstructorWithParamsTests :
		public testing::TestWithParam<FakeConsole_CtorParams>
	{};


	TEST_P(FakeConsoleConstructorWithParamsTests, Constructor$with$params$sets$members)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{GetParam().nextInput, GetParam().textSpans};

		// Assert
		EXPECT_EQ(GetParam().nextInput, instance.FAKE_getNextInput());
		// TODO: Why doesn't std::ranges::equal work?
		EXPECT_TRUE
		(
			std::equal
			(
				GetParam().textSpans.begin(),
				GetParam().textSpans.end(),
				instance.FAKE_getTextSpans().begin()
			)
		);
	}

#pragma endregion


#pragma region Fake member mutators

	TEST(FakeConsoleTests, FAKE_setNextInput_sets_next_input)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{};
		std::string nextInputToSetTo{ "abc" };

		// Act
		instance.FAKE_setNextInput(nextInputToSetTo);

		// Assert
		EXPECT_EQ(nextInputToSetTo, instance.FAKE_getNextInput());
	}

#pragma endregion

#pragma endregion


#pragma region getInput

	class FakeConsole$getInput$Tests :
		public testing::TestWithParam<std::string>
	{};


	TEST_P(FakeConsole$getInput$Tests, getInput$returns$expected$value)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{ GetParam(), {} };

		// Assert
		EXPECT_EQ(GetParam(), instance.getInput());
	}


	INSTANTIATE_TEST_CASE_P
	(
		FakeConsoleTests,
		FakeConsole$getInput$Tests,
		testing::Values
		(
			"",
			"a",
			"XYZ",
			"Hello, world!\tMore text..."
		)
	);

#pragma endregion


#pragma region write(Line)

	struct FakeConsole_write_Params
	{
		const std::string_view text;
		const CmdCalculator::EWriteMode writeMode;
	};
	
	struct FakeConsole_write_testData
	{
		FakeConsole_CtorParams ctorParams;
		FakeConsole_write_Params writeParams;
	};
	
	class FakeConsole$write$Tests :
		public testing::TestWithParam<FakeConsole_write_testData>
	{};


	TEST_P(FakeConsole$write$Tests, calling$write$appends$to$text$spans)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{ GetParam().ctorParams.nextInput, GetParam().ctorParams.textSpans };

		std::string_view textToWrite{ GetParam().writeParams.text };
		CmdCalculator::EWriteMode modeToWriteIn{ GetParam().writeParams.writeMode };
		std::string_view expectedTextToBeWritten{ textToWrite };
		
		std::vector<CmdCalculatorTestDoubles::FakeConsole<char>::TextSpan> textSpansBefore;
		std::ranges::copy(instance.FAKE_getTextSpans(), std::back_inserter(textSpansBefore));

		const size_t expectedTextSpansAfterSize{ textSpansBefore.size() + 1 };

		// Act
		instance.write(textToWrite, modeToWriteIn);

		// Assert
		auto textSpansAfter{ instance.FAKE_getTextSpans() };
		EXPECT_EQ(expectedTextSpansAfterSize, std::ranges::size(textSpansAfter));
		CmdCalculatorTestDoubles::FakeConsole<char>::TextSpan lastAddedTextSpan
		{
			*(textSpansAfter | std::views::reverse | std::views::take(1)).begin()
		};
		
		EXPECT_EQ(expectedTextToBeWritten, lastAddedTextSpan.text);
		EXPECT_EQ(modeToWriteIn, lastAddedTextSpan.writeMode);
	}


	TEST_P(FakeConsole$write$Tests, calling$writeLine$appends$to$text$spans)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{ GetParam().ctorParams.nextInput, GetParam().ctorParams.textSpans };

		std::string_view textToWrite{ GetParam().writeParams.text };
		CmdCalculator::EWriteMode modeToWriteIn{ GetParam().writeParams.writeMode };
		std::string expectedTextToBeWritten{ std::string{textToWrite} + '\n' };

		std::vector<CmdCalculatorTestDoubles::FakeConsole<char>::TextSpan> textSpansBefore;
		std::ranges::copy(instance.FAKE_getTextSpans(), std::back_inserter(textSpansBefore));

		const size_t expectedTextSpansAfterSize{ textSpansBefore.size() + 1 };

		// Act
		instance.writeLine(textToWrite, modeToWriteIn);

		// Assert
		auto textSpansAfter{ instance.FAKE_getTextSpans() };
		EXPECT_EQ(expectedTextSpansAfterSize, std::ranges::size(textSpansAfter));
		CmdCalculatorTestDoubles::FakeConsole<char>::TextSpan lastAddedTextSpan
		{
			*(textSpansAfter | std::views::reverse | std::views::take(1)).begin()
		};

		EXPECT_EQ(expectedTextToBeWritten, lastAddedTextSpan.text);
		EXPECT_EQ(modeToWriteIn, lastAddedTextSpan.writeMode);
	}


	constexpr std::string_view FakeConsole_write_textSpansToWrite[]
	{
		""sv,
		"a"sv,
		"XYZ"sv,
		"Hello world!\tMore text...\nNew line with trailing whitespace! "sv
	};

	constexpr CmdCalculator::EWriteMode FakeConsole_write_textModesToWriteIn[]
	{
		CmdCalculator::EWriteMode::Info,
		CmdCalculator::EWriteMode::Error,
		CmdCalculator::EWriteMode::Debug
	};


	const std::initializer_list<CmdCalculatorTestDoubles::FakeConsole<char>::TextSpan> FakeConsole_write_existingTextSpanCollections[]
	{
		{},
		{
			{"firstSpan", CmdCalculator::EWriteMode::Info}
		},
		{
			{"firstSpan", CmdCalculator::EWriteMode::Info},
			{"secondSpan", CmdCalculator::EWriteMode::Info},
			{"thirdSpan", CmdCalculator::EWriteMode::Info}
		},
	};


	const auto FakeConsole_write_testDataValues
	{
		[]()
		{
			std::vector<FakeConsole_write_testData> data{};

			for (const auto textSpanToWrite : FakeConsole_write_textSpansToWrite)
			for (const auto textModeToWriteIn : FakeConsole_write_textModesToWriteIn)
			for (const auto existingTextSpans : FakeConsole_write_existingTextSpanCollections)
			{
				data.push_back
				(
					FakeConsole_write_testData
					{
						.ctorParams = FakeConsole_CtorParams
						{
							.nextInput = "",
							.textSpans = existingTextSpans
						},
						.writeParams = FakeConsole_write_Params
						{
							.text = textSpanToWrite,
							.writeMode = textModeToWriteIn
						}
					}
				);
			}

			return data;
		}()
	};
	

	INSTANTIATE_TEST_CASE_P
	(
		FakeConsoleTests,
		FakeConsole$write$Tests,
		testing::ValuesIn(FakeConsole_write_testDataValues)
	);

#pragma endregion
}