#include "pch.h"

#include <string>
#include <optional>
#include <vector>
#include <format>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/DynamicExpressionPartRecursiveSplitter.h"
#include "../CmdCalculator/std_polyfills.h"
#include "../CmdCalculatorTestDoubles/FakeHalfwayDynamicExpressionPartRecursiveSplitter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"


using namespace std::string_literals;


namespace CmdCalculatorTestDoubleTests
{
#pragma region Result equality testing utilities
	/*
	bool areResultsEqual
	(
		const CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult<std::string>& lhs,
		const CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult<std::string>& rhs
	);


	bool areResultPtrsEqual
	(
		const CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult<std::string>* lhs,
		const CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult<std::string>* rhs
	)
	{
		return lhs && rhs && areResultsEqual(*lhs, *rhs);
	}


	bool areResultsEqual
	(
		const CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult<std::string>& lhs,
		const CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult<std::string>& rhs
	)
	{
		return
			areResultPtrsEqual(lhs.getLeftPart(), rhs.getLeftPart())
			&& lhs.getSplitPart().getStringRepresentation() == rhs.getSplitPart().getStringRepresentation()
			&& areResultPtrsEqual(lhs.getRightPart(), rhs.getRightPart())
			;
	}


	bool isExpectedResult
	(
		const std::optional<CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult<std::string>>& expected,
		const std::optional<CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult<std::string>>& actual
	)
	{
		if (expected.has_value() && actual.has_value())
			return areResultsEqual(expected.value(), actual.value());
		return expected.has_value() == actual.has_value();
	}
	*/
#pragma endregion


#pragma region Concept satisfaction

	TEST(FakeHalfwayDynamicExpressionPartRecursiveSplitterTests, FakeHalfwayDynamicExpressionPartRecursiveSplitter$satisfies$DynamicExpressionPartRecursiveSplitter$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicExpressionPartRecursiveSplitter
			<
				CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartRecursiveSplitter
				<
					std::string
				>
			>
		);
	}

#pragma endregion


#pragma region tryToSplit

	struct FakeHalfwayDynamicExpressionPartRecursiveSplitter_tryToSplit_TestData
	{
		std::vector<std::string> parts;
		// TODO: Consider using a more direct way of comparing results.
		std::optional<std::string> expectedResult;


		static std::string stringifyParts(const std::vector<std::string>& parts)
		{
			return parts.empty()
				? ""
				:
					CmdCalculator::Polyfills::ranges::fold_left
					(
						parts
							| std::views::take(parts.size() - 1)
							| std::views::drop(1)
							| std::views::transform
							(
								[](const std::string& part)
								{ return std::format("\"{}\", ", part); }
							)
						,
						std::format("\"{}\", ", parts.front()),
						std::plus<std::string>()
					)
					+ std::format("\"{}\"", parts.back())
			;
		}


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const FakeHalfwayDynamicExpressionPartRecursiveSplitter_tryToSplit_TestData& testData
		)
		{
			ostream
				<< "FakeHalfwayDynamicExpressionPartRecursiveSplitter.tryToSplit({"
				<< FakeHalfwayDynamicExpressionPartRecursiveSplitter_tryToSplit_TestData::stringifyParts(testData.parts)
				<< "}) = "
				<< testData.expectedResult.value_or("{}")
			;

			return ostream;
		}
	};

	class FakeHalfwayDynamicExpressionPartRecursiveSplitter$tryToSplit$Tests :
		public testing::TestWithParam<FakeHalfwayDynamicExpressionPartRecursiveSplitter_tryToSplit_TestData>
	{};

	const FakeHalfwayDynamicExpressionPartRecursiveSplitter_tryToSplit_TestData
		FakeHalfwayDynamicExpressionPartRecursiveSplitter_tryToSplit_TestDataValues[]
	{
		{
			.parts{},
			.expectedResult{}
		},
		{
			.parts{ "Part1" },
			.expectedResult{ std::make_optional<std::string>("{null<Part1>null}") }
		},
		{
			.parts{ "Part1", "Part2" },
			.expectedResult{}
		},
		{
			.parts{ "Part1", "Part2", "Part3" },
			.expectedResult{ std::make_optional<std::string>("{{null<Part1>null}<Part2>{null<Part3>null}}") }
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4" },
			.expectedResult{}
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4", "Part5" },
			.expectedResult{ std::make_optional<std::string>("{{null<Part1>null}<Part2>{{null<Part3>null}<Part4>{null<Part5>null}}}") }
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6" },
			.expectedResult{}
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7" },
			.expectedResult{ std::make_optional<std::string>("{{{null<Part1>null}<Part2>{null<Part3>null}}<Part4>{{null<Part5>null}<Part6>{null<Part7>null}}}") }
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7", "Part8" },
			.expectedResult{}
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7", "Part8", "Part9" },
			.expectedResult{ std::make_optional<std::string>("{{{null<Part1>null}<Part2>{null<Part3>null}}<Part4>{{null<Part5>null}<Part6>{{null<Part7>null}<Part8>{null<Part9>null}}}}") }
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7", "Part8", "Part9", "Part10" },
			.expectedResult{}
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7", "Part8", "Part9", "Part10", "Part11" },
			.expectedResult{ std::make_optional<std::string>("{{{null<Part1>null}<Part2>{{null<Part3>null}<Part4>{null<Part5>null}}}<Part6>{{null<Part7>null}<Part8>{{null<Part9>null}<Part10>{null<Part11>null}}}}") }
		}
	};


	INSTANTIATE_TEST_CASE_P
	(
		FakeHalfwayDynamicExpressionPartRecursiveSplitterTests,
		FakeHalfwayDynamicExpressionPartRecursiveSplitter$tryToSplit$Tests,
		testing::ValuesIn(FakeHalfwayDynamicExpressionPartRecursiveSplitter_tryToSplit_TestDataValues)
	);

	TEST_P(FakeHalfwayDynamicExpressionPartRecursiveSplitter$tryToSplit$Tests, calling$tryToSplit$returns$expected$result)
	{
		// Arrange
		CmdCalculatorTestUtils::StdVector auto parts
		{
			CmdCalculatorTestUtils::moveRangeToVector
			(
				GetParam().parts
				| std::views::transform
				(
					[](const std::string& partStringRepresentation)
					{
						return CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
							{ false, "", "", partStringRepresentation }
						;
					}
				)
			)
		};
		const std::optional<std::string> expectedReturnValue{ GetParam().expectedResult };
		CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartRecursiveSplitter<std::string> instance{};

		// Act
		const std::optional<CmdCalculatorTestDoubles::StubDynamicExpressionPartRecursiveSplitResult<std::string>> returnValue
		{
			instance.tryToSplit(parts)
		};

		// Assert
		ASSERT_EQ(expectedReturnValue.has_value(), returnValue.has_value());
		if (expectedReturnValue.has_value())
			EXPECT_EQ(expectedReturnValue.value(), returnValue.value().STUB_getStringRepresentation());
	}

#pragma endregion
}