#include "pch.h"

#include <string>
#include <string_view>
#include <iostream>

#include "../CmdCalculator/StreamBasedConsole.h"
#include "../CmdCalculator/Console.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StreamBasedConsoleTests, StreamBasedConsole$satisfies$Console$concept)
	{
		static_assert
		(
			CmdCalculator::Console
			<
				CmdCalculator::StreamBasedConsole<char>
			>
		);
	}

#pragma endregion


#pragma region getInput

	struct StreamBasedConsole_getInput_TestData
	{
		std::string inputStreamData;
		std::string expected;

		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const StreamBasedConsole_getInput_TestData& testData
		)
		{
			ostream
				<< "StreamBasedConsole{inputStream=\""
				<< testData.inputStreamData
				<< "\"}.getInput() = \""
				<< testData.expected
				<< '\"'
			;

			return ostream;
		}
	};

	class StreamBasedConsole$getInput$Tests :
		public testing::TestWithParam<StreamBasedConsole_getInput_TestData>
	{};

	StreamBasedConsole_getInput_TestData StreamBasedConsole_getInput_TestDataValues[]
	{
		{
			.inputStreamData{ "" },
			.expected{ "" }
		},
		{
			.inputStreamData{ " " },
			.expected{ " " }
		},
		{
			.inputStreamData{ "   \t  " },
			.expected{ "   \t  " }
		},
		{
			.inputStreamData{ "\n" },
			.expected{ "" }
		},
		{
			.inputStreamData{ "\n\n\n" },
			.expected{ "" }
		},
		{
			.inputStreamData{ "x" },
			.expected{ "x" }
		},
		{
			.inputStreamData{ "abc123" },
			.expected{ "abc123" }
		},
		{
			.inputStreamData{ "Hello, world!" },
			.expected{ "Hello, world!" }
		},
		{
			.inputStreamData{ " x" },
			.expected{ " x" }
		},
		{
			.inputStreamData{ " abc123" },
			.expected{ " abc123" }
		},
		{
			.inputStreamData{ " Hello, world!" },
			.expected{ " Hello, world!" }
		},
		{
			.inputStreamData{ "\n   \t  " },
			.expected{ "" }
		},
		{
			.inputStreamData{ "\nx" },
			.expected{ "" }
		},
		{
			.inputStreamData{ "\nabc123" },
			.expected{ "" }
		},
		{
			.inputStreamData{ "\nHello, world!" },
			.expected{ "" }
		},
		{
			.inputStreamData{ "   \t  \n" },
			.expected{ "   \t  " }
		},
		{
			.inputStreamData{ "x\n" },
			.expected{ "x" }
		},
		{
			.inputStreamData{ "abc123\n" },
			.expected{ "abc123" }
		},
		{
			.inputStreamData{ "Hello, world!\n" },
			.expected{ "Hello, world!" }
		},
		{
			.inputStreamData{ "Hello, world!\nMore text" },
			.expected{ "Hello, world!" }
		},
	};

	INSTANTIATE_TEST_CASE_P
	(
		StreamBasedConsoleTests,
		StreamBasedConsole$getInput$Tests,
		testing::ValuesIn(StreamBasedConsole_getInput_TestDataValues)
	);

	TEST_P(StreamBasedConsole$getInput$Tests, calling$getInput$returns$line$of$text$from$input$stream)
	{
		// Arrange
		std::ostringstream outputStream{};

		std::string inputStreamData{ GetParam().inputStreamData };
		std::istringstream inputStream{ inputStreamData };

		const std::string expected{ GetParam().expected };

		CmdCalculator::StreamBasedConsole<char> instance
		{
			inputStream,
			outputStream,
			outputStream,
			outputStream
		};

		// Act
		const std::string actual{ instance.getInput() };

		// Assert
		EXPECT_EQ(expected, actual);
	}

#pragma endregion


#pragma region write/writeLine

	struct StreamBasedConsole_write_TestData
	{
		std::string textToWrite;
		std::string expectedWrittenTextFor_write;
		std::string expectedWrittenTextFor_writeLine;

		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const StreamBasedConsole_write_TestData& testData
		)
		{
			ostream
				<< "StreamBasedConsole.write(\""
				<< testData.textToWrite
				<< "\") writes \""
				<< testData.expectedWrittenTextFor_write
				<< "\" and StreamBasedConsole.writeLine() writes \""
				<< testData.expectedWrittenTextFor_writeLine
				<< '\"'
			;

			return ostream;
		}
	};

	class StreamBasedConsole$write$Tests :
		public testing::TestWithParam<StreamBasedConsole_write_TestData>
	{};

	StreamBasedConsole_write_TestData StreamBasedConsole_write_TestDataValues[]
	{
		{
			.textToWrite{ "" },
			.expectedWrittenTextFor_write{ "" },
			.expectedWrittenTextFor_writeLine{ "\n" }
		},
		{
			.textToWrite{ "\n" },
			.expectedWrittenTextFor_write{ "\n" },
			.expectedWrittenTextFor_writeLine{ "\n" }
		},
		{
			.textToWrite{ "\n\n\n" },
			.expectedWrittenTextFor_write{ "\n\n\n" },
			.expectedWrittenTextFor_writeLine{ "\n\n\n" }
		},
		{
			.textToWrite{ " " },
			.expectedWrittenTextFor_write{ " " },
			.expectedWrittenTextFor_writeLine{ " \n" }
		},
		{
			.textToWrite{ " \n" },
			.expectedWrittenTextFor_write{ " \n" },
			.expectedWrittenTextFor_writeLine{ " \n" }
		},
		{
			.textToWrite{ "   \t " },
			.expectedWrittenTextFor_write{ "   \t " },
			.expectedWrittenTextFor_writeLine{ "   \t \n" }
		},
		{
			.textToWrite{ "   \t \n" },
			.expectedWrittenTextFor_write{ "   \t \n" },
			.expectedWrittenTextFor_writeLine{ "   \t \n" }
		},
		{
			.textToWrite{ "x" },
			.expectedWrittenTextFor_write{ "x" },
			.expectedWrittenTextFor_writeLine{ "x\n" }
		},
		{
			.textToWrite{ "x\n" },
			.expectedWrittenTextFor_write{ "x\n" },
			.expectedWrittenTextFor_writeLine{ "x\n" }
		},
		{
			.textToWrite{ "abc123" },
			.expectedWrittenTextFor_write{ "abc123" },
			.expectedWrittenTextFor_writeLine{ "abc123\n" }
		},
		{
			.textToWrite{ "abc123\n" },
			.expectedWrittenTextFor_write{ "abc123\n" },
			.expectedWrittenTextFor_writeLine{ "abc123\n" }
		},
		{
			.textToWrite{ "Hello, world!" },
			.expectedWrittenTextFor_write{ "Hello, world!" },
			.expectedWrittenTextFor_writeLine{ "Hello, world!\n" }
		},
		{
			.textToWrite{ "Hello, world!\n" },
			.expectedWrittenTextFor_write{ "Hello, world!\n" },
			.expectedWrittenTextFor_writeLine{ "Hello, world!\n" }
		},
		{
			.textToWrite{ "\nHello, world!" },
			.expectedWrittenTextFor_write{ "\nHello, world!" },
			.expectedWrittenTextFor_writeLine{ "\nHello, world!\n" }
		},
		{
			.textToWrite{ "\nHello, world!\n" },
			.expectedWrittenTextFor_write{ "\nHello, world!\n" },
			.expectedWrittenTextFor_writeLine{ "\nHello, world!\n" }
		},
		{
			.textToWrite{ "Hello, world!\n More text..." },
			.expectedWrittenTextFor_write{ "Hello, world!\n More text..." },
			.expectedWrittenTextFor_writeLine{ "Hello, world!\n More text...\n" }
		},
		{
			.textToWrite{ "Hello, world!\n More text...\n" },
			.expectedWrittenTextFor_write{ "Hello, world!\n More text...\n" },
			.expectedWrittenTextFor_writeLine{ "Hello, world!\n More text...\n" }
		},
		{
			.textToWrite{ "Hello, world!\n More text...\n\n" },
			.expectedWrittenTextFor_write{ "Hello, world!\n More text...\n\n" },
			.expectedWrittenTextFor_writeLine{ "Hello, world!\n More text...\n\n" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		StreamBasedConsoleTests,
		StreamBasedConsole$write$Tests,
		testing::ValuesIn(StreamBasedConsole_write_TestDataValues)
	);


#pragma region write

	TEST_P(StreamBasedConsole$write$Tests, calling$write$with$info$mode$writes$text$to$info$stream$only)
	{
		// Arrange
		std::istringstream inputStream{};
		std::ostringstream infoStream{};
		std::ostringstream errorStream{};
		std::ostringstream debugStream{};

		const std::string textToPass{ GetParam().textToWrite };
		const std::string expected{ GetParam().expectedWrittenTextFor_write };

		CmdCalculator::StreamBasedConsole<char> instance
		{
			inputStream,
			infoStream,
			errorStream,
			debugStream
		};

		// Act
		instance.write(textToPass, CmdCalculator::EWriteMode::Info);

		// Assert
		std::string inputStreamAfter;
		inputStream.str(inputStreamAfter);

		EXPECT_TRUE(inputStreamAfter.empty());
		EXPECT_EQ(expected, infoStream.str());
		EXPECT_TRUE(errorStream.str().empty());
		EXPECT_TRUE(debugStream.str().empty());
	}


	TEST_P(StreamBasedConsole$write$Tests, calling$write$with$error$mode$writes$text$to$error$stream$only)
	{
		// Arrange
		std::istringstream inputStream{};
		std::ostringstream infoStream{};
		std::ostringstream errorStream{};
		std::ostringstream debugStream{};

		const std::string textToPass{ GetParam().textToWrite };
		const std::string expected{ GetParam().expectedWrittenTextFor_write };

		CmdCalculator::StreamBasedConsole<char> instance
		{
			inputStream,
			infoStream,
			errorStream,
			debugStream
		};

		// Act
		instance.write(textToPass, CmdCalculator::EWriteMode::Error);

		// Assert
		std::string inputStreamAfter;
		inputStream.str(inputStreamAfter);

		EXPECT_TRUE(inputStreamAfter.empty());
		EXPECT_TRUE(infoStream.str().empty());
		EXPECT_EQ(expected, errorStream.str());
		EXPECT_TRUE(debugStream.str().empty());
	}


	TEST_P(StreamBasedConsole$write$Tests, calling$write$with$debug$mode$writes$text$to$debug$stream$only)
	{
		// Arrange
		std::istringstream inputStream{};
		std::ostringstream infoStream{};
		std::ostringstream errorStream{};
		std::ostringstream debugStream{};

		const std::string textToPass{ GetParam().textToWrite };
		const std::string expected{ GetParam().expectedWrittenTextFor_write };

		CmdCalculator::StreamBasedConsole<char> instance
		{
			inputStream,
			infoStream,
			errorStream,
			debugStream
		};

		// Act
		instance.write(textToPass, CmdCalculator::EWriteMode::Error);

		// Assert
		std::string inputStreamAfter;
		inputStream.str(inputStreamAfter);

		EXPECT_TRUE(inputStreamAfter.empty());
		EXPECT_TRUE(infoStream.str().empty());
		EXPECT_TRUE(errorStream.str().empty());
		EXPECT_EQ(expected, debugStream.str());
	}

#pragma endregion


#pragma region writeLine

	TEST_P(StreamBasedConsole$write$Tests, calling$writeLine$with$info$mode$writes$text$with$newline$to$info$stream$only)
	{
		// Arrange
		std::istringstream inputStream{};
		std::ostringstream infoStream{};
		std::ostringstream errorStream{};
		std::ostringstream debugStream{};

		const std::string textToPass{ GetParam().textToWrite };
		const std::string expected{ GetParam().expectedWrittenTextFor_writeLine };

		CmdCalculator::StreamBasedConsole<char> instance
		{
			inputStream,
			infoStream,
			errorStream,
			debugStream
		};

		// Act
		instance.write(textToPass, CmdCalculator::EWriteMode::Info);

		// Assert
		std::string inputStreamAfter;
		inputStream.str(inputStreamAfter);

		EXPECT_TRUE(inputStreamAfter.empty());
		EXPECT_EQ(expected, infoStream.str());
		EXPECT_TRUE(errorStream.str().empty());
		EXPECT_TRUE(debugStream.str().empty());
	}


	TEST_P(StreamBasedConsole$write$Tests, calling$write$with$error$mode$writes$text$with$newline$to$error$stream$only)
	{
		// Arrange
		std::istringstream inputStream{};
		std::ostringstream infoStream{};
		std::ostringstream errorStream{};
		std::ostringstream debugStream{};

		const std::string textToPass{ GetParam().textToWrite };
		const std::string expected{ GetParam().expectedWrittenTextFor_writeLine };

		CmdCalculator::StreamBasedConsole<char> instance
		{
			inputStream,
			infoStream,
			errorStream,
			debugStream
		};

		// Act
		instance.write(textToPass, CmdCalculator::EWriteMode::Error);

		// Assert
		std::string inputStreamAfter;
		inputStream.str(inputStreamAfter);

		EXPECT_TRUE(inputStreamAfter.empty());
		EXPECT_TRUE(infoStream.str().empty());
		EXPECT_EQ(expected, errorStream.str());
		EXPECT_TRUE(debugStream.str().empty());
	}


	TEST_P(StreamBasedConsole$write$Tests, calling$write$with$debug$mode$writes$text$with$newline$to$debug$stream$only)
	{
		// Arrange
		std::istringstream inputStream{};
		std::ostringstream infoStream{};
		std::ostringstream errorStream{};
		std::ostringstream debugStream{};

		const std::string textToPass{ GetParam().textToWrite };
		const std::string expected{ GetParam().expectedWrittenTextFor_writeLine };

		CmdCalculator::StreamBasedConsole<char> instance
		{
			inputStream,
			infoStream,
			errorStream,
			debugStream
		};

		// Act
		instance.write(textToPass, CmdCalculator::EWriteMode::Error);

		// Assert
		std::string inputStreamAfter;
		inputStream.str(inputStreamAfter);

		EXPECT_TRUE(inputStreamAfter.empty());
		EXPECT_TRUE(infoStream.str().empty());
		EXPECT_TRUE(errorStream.str().empty());
		EXPECT_EQ(expected, debugStream.str());
	}

#pragma endregion

#pragma endregion
}