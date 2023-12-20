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

	TEST(FakeConsoleDefaultConstructorTests, Default$constructor$sets$default$input$to$a$valid$value)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{};

		// Assert
		EXPECT_NO_THROW( instance.FAKE_getDefaultInput(); );
	}


	TEST(FakeConsoleDefaultConstructorTests, Default$constructor$sets$no$next$inputs)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{};

		// Assert
		EXPECT_TRUE(std::ranges::empty(instance.FAKE_getNextInputs()));
	}


	TEST(FakeConsoleDefaultConstructorTests, Default$constructor$sets$number$of$calls$to$getInput$to$zero)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{};

		// Assert
		EXPECT_EQ(0, instance.FAKE_getNumberOfCallsTo_getInput());
	}


	TEST(FakeConsoleDefaultConstructorTests, Default$constructor$sets$no$text$spans)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{};

		// Assert
		EXPECT_TRUE(std::ranges::empty(instance.FAKE_getTextSpans()));
	}

#pragma endregion


#pragma region Constructor with two params

	const std::string ValidDefaultInputCtorValues[]
	{
		"",
		"Hello, world!"
	};

	const std::initializer_list<CmdCalculatorTestDoubles::FakeConsole<char>::TextSpan> ValidTextSpansCtorValues[]
	{
		{},
		{
			CmdCalculatorTestDoubles::FakeConsole<char>::TextSpan
			{
				"Some text span contents",
				CmdCalculator::EWriteMode::Error
			}
		}
	};
	
	
	struct FakeConsole_CtorWithTwoParamsData
	{
		const std::string defaultInput;
		const std::initializer_list<CmdCalculatorTestDoubles::FakeConsole<char>::TextSpan> textSpans;
	};
	
	
	class FakeConsoleConstructorWithTwoParamsTests :
		public testing::TestWithParam<FakeConsole_CtorWithTwoParamsData>
	{};


	const std::vector<FakeConsole_CtorWithTwoParamsData> FakeConsole_CtorWithTwoParamsDataItems
	{
		[=]()
		{
			std::vector<FakeConsole_CtorWithTwoParamsData> data{};

			for (const auto& defaultInputCtorValue : ValidDefaultInputCtorValues)
			for (const auto& textSpansCtorValue : ValidTextSpansCtorValues)
			{
				data.push_back
				(
					FakeConsole_CtorWithTwoParamsData
					{
						.defaultInput{ defaultInputCtorValue },
						.textSpans{ textSpansCtorValue }
					}
				);
			}

			return data;
		}()
	};


	INSTANTIATE_TEST_CASE_P
	(
		FakeConsoleTests,
		FakeConsoleConstructorWithTwoParamsTests,
		testing::ValuesIn(FakeConsole_CtorWithTwoParamsDataItems)
	);


	TEST_P(FakeConsoleConstructorWithTwoParamsTests, Constructor$with$two$params$sets$members)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{GetParam().defaultInput, GetParam().textSpans};

		// Assert
		EXPECT_EQ(GetParam().defaultInput, instance.FAKE_getDefaultInput());
		EXPECT_TRUE(std::ranges::empty(instance.FAKE_getNextInputs()));
		EXPECT_EQ(0, instance.FAKE_getNumberOfCallsTo_getInput());
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


#pragma region Constructor with three params

	struct FakeConsole_CtorWithThreeParamsData
	{
		const std::string defaultInput;
		const std::vector<std::string> nextInputs;
		const std::initializer_list<CmdCalculatorTestDoubles::FakeConsole<char>::TextSpan> textSpans;
	};


	const std::vector<std::string> ValidNextInputsCtorValues[]
	{
		{},
		{ "Some input" },
		{ "Some input", "another input" }
	};
	
	
	class FakeConsoleConstructorWithThreeParamsTests :
		public testing::TestWithParam<FakeConsole_CtorWithThreeParamsData>
	{};


	const std::vector<FakeConsole_CtorWithThreeParamsData> FakeConsole_CtorWithThreeParamsDataItems
	{
		[=]()
		{
			std::vector<FakeConsole_CtorWithThreeParamsData> data{};

			for (const auto& twoParamData : FakeConsole_CtorWithTwoParamsDataItems)
			for (const auto& nextInputsCtorValue : ValidNextInputsCtorValues)
			{
				data.push_back
				(
					FakeConsole_CtorWithThreeParamsData
					{
						.defaultInput{ twoParamData.defaultInput },
						.nextInputs{ nextInputsCtorValue },
						.textSpans{ twoParamData.textSpans }
					}
				);
			}

			return data;
		}()
	};


	INSTANTIATE_TEST_CASE_P
	(
		FakeConsoleTests,
		FakeConsoleConstructorWithThreeParamsTests,
		testing::ValuesIn(FakeConsole_CtorWithThreeParamsDataItems)
	);


	TEST_P(FakeConsoleConstructorWithThreeParamsTests, Constructor$with$three$params$sets$members)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{GetParam().defaultInput, GetParam().nextInputs, GetParam().textSpans};

		// Assert
		EXPECT_EQ(GetParam().defaultInput, instance.FAKE_getDefaultInput());
		// TODO: Why doesn't std::ranges::equal work?
		EXPECT_TRUE
		(
			std::equal
			(
				GetParam().nextInputs.begin(),
				GetParam().nextInputs.end(),
				instance.FAKE_getNextInputs().begin()
			)
		);
		EXPECT_EQ(0, instance.FAKE_getNumberOfCallsTo_getInput());
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

#pragma endregion


#pragma region Fake member mutators

	TEST(FakeConsoleTests, FAKE_setDefaultInput_sets_default_input)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{};
		std::string defaultInputToSetTo{ "abc" };

		// Act
		instance.FAKE_setDefaultInput(defaultInputToSetTo);

		// Assert
		EXPECT_EQ(defaultInputToSetTo, instance.FAKE_getDefaultInput());
	}

	TEST(FakeConsoleTests, FAKE_setNextInputs_sets_next_inputs)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{};
		std::vector<std::string> nextInputsToSetTo{ "Input", "More input"};

		// Act
		instance.FAKE_setNextInputs(nextInputsToSetTo);

		// Assert
		EXPECT_TRUE
		(
			std::equal
			(
				nextInputsToSetTo.begin(),
				nextInputsToSetTo.end(),
				instance.FAKE_getNextInputs().begin()
			)
		);
	}

#pragma endregion


#pragma region getInput

	struct FakeConsole$getInput$ReturnValueTestData
	{
		std::string defaultInput;
		std::vector<std::string> nextInputs;
		size_t timesToCall;
		std::vector<std::string> expectedReturnValues;
		std::vector<size_t> expectedNextInputsSizes;
	};
	
	
	class FakeConsole$getInput$ReturnValueTests :
		public testing::TestWithParam<FakeConsole$getInput$ReturnValueTestData>
	{};


	INSTANTIATE_TEST_CASE_P
	(
		FakeConsoleTests,
		FakeConsole$getInput$ReturnValueTests,
		testing::Values
		(
			FakeConsole$getInput$ReturnValueTestData
			{
				.defaultInput{ "Default input" },
				.nextInputs{},
				.timesToCall{ 2 },
				.expectedReturnValues
				{
					"Default input",
					"Default input"
				},
				.expectedNextInputsSizes{0, 0}
			},
			FakeConsole$getInput$ReturnValueTestData
			{
				.defaultInput{ "Default input" },
				.nextInputs
				{
					"Second input",
					"first input"
				},
				.timesToCall{ 4 },
				.expectedReturnValues
				{
					"first input",
					"Second input",
					"Default input",
					"Default input"
				},
				.expectedNextInputsSizes{2, 1, 0, 0}
			}
		)
	);


	TEST_P(FakeConsole$getInput$ReturnValueTests, getInput$returns$expected$value)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{ GetParam().defaultInput, GetParam().nextInputs, {} };
		std::vector<std::string> returnValues{};

		// Act
		for (size_t i{ 0 }; i < GetParam().timesToCall; i++)
			returnValues.push_back(instance.getInput());

		// Assert
		EXPECT_TRUE
		(
			std::equal
			(
				GetParam().expectedReturnValues.begin(),
				GetParam().expectedReturnValues.end(),
				returnValues.begin()
			)
		);
	}


	TEST_P(FakeConsole$getInput$ReturnValueTests, Calling$getInput$pops$value$from$nextInputs$if$any)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{ GetParam().defaultInput, GetParam().nextInputs, {} };
		std::vector<size_t> actualNextInputsSizes{};

		// Act
		for (size_t i{ 0 }; i < GetParam().timesToCall; i++)
		{
			instance.getInput();
			actualNextInputsSizes.push_back(instance.FAKE_getNextInputs().size());
		}

		// Assert
		EXPECT_TRUE
		(
			std::equal
			(
				GetParam().expectedNextInputsSizes.begin(),
				GetParam().expectedNextInputsSizes.end(),
				actualNextInputsSizes.begin()
			)
		);
	}


	TEST(FakeConsole$getInput$Tests, Calling$getInput$increments$number$of$calls$to$getInput)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{};
		size_t numberOfTimesToCall{ 3 };
		size_t initialNumberOfCallsTo_getInput{ instance.FAKE_getNumberOfCallsTo_getInput() };
		std::vector<size_t> expectedReturnValues{};
		for (size_t i{ 1 }; i <= numberOfTimesToCall; i++)
			expectedReturnValues.push_back(i);
		std::vector<size_t> actualReturnValues{};

		// Act
		for (size_t i{ 0 }; i <= numberOfTimesToCall; i++)
		{
			instance.getInput();
			actualReturnValues.push_back(instance.FAKE_getNumberOfCallsTo_getInput());
		}

		// Assert
		EXPECT_TRUE
		(
			std::equal
			(
				expectedReturnValues.begin(),
				expectedReturnValues.end(),
				actualReturnValues.begin()
			)
		);
	}

#pragma endregion


#pragma region write(Line)

	struct FakeConsole_write_Params
	{
		const std::string_view text;
		const CmdCalculator::EWriteMode writeMode;
	};
	
	struct FakeConsole_write_testData
	{
		FakeConsole_CtorWithTwoParamsData ctorParams;
		FakeConsole_write_Params writeParams;
	};
	
	class FakeConsole$write$Tests :
		public testing::TestWithParam<FakeConsole_write_testData>
	{};

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
						.ctorParams = FakeConsole_CtorWithTwoParamsData
						{
							.defaultInput = "",
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


	TEST_P(FakeConsole$write$Tests, calling$write$appends$to$text$spans)
	{
		// Arrange
		CmdCalculatorTestDoubles::FakeConsole<char> instance{ GetParam().ctorParams.defaultInput, GetParam().ctorParams.textSpans };

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
		CmdCalculatorTestDoubles::FakeConsole<char> instance{ GetParam().ctorParams.defaultInput, GetParam().ctorParams.textSpans };

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

#pragma endregion
}