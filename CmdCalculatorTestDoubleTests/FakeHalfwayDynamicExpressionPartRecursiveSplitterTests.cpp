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
#include "shared_splitting_test_utils.h"


//using namespace std::string_literals;


namespace CmdCalculatorTestDoubleTests
{
#pragma region Result equality testing utilities
	/*
	bool areResultsEqual
	(
		const CmdCalculatorTestDoubles::StubTrackingDynamicExpressionPartRecursiveSplitResult<std::string>& lhs,
		const CmdCalculatorTestDoubles::StubTrackingDynamicExpressionPartRecursiveSplitResult<std::string>& rhs
	);


	bool areResultPtrsEqual
	(
		const CmdCalculatorTestDoubles::StubTrackingDynamicExpressionPartRecursiveSplitResult<std::string>* lhs,
		const CmdCalculatorTestDoubles::StubTrackingDynamicExpressionPartRecursiveSplitResult<std::string>* rhs
	)
	{
		return lhs && rhs && areResultsEqual(*lhs, *rhs);
	}


	bool areResultsEqual
	(
		const CmdCalculatorTestDoubles::StubTrackingDynamicExpressionPartRecursiveSplitResult<std::string>& lhs,
		const CmdCalculatorTestDoubles::StubTrackingDynamicExpressionPartRecursiveSplitResult<std::string>& rhs
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
		const std::optional<CmdCalculatorTestDoubles::StubTrackingDynamicExpressionPartRecursiveSplitResult<std::string>>& expected,
		const std::optional<CmdCalculatorTestDoubles::StubTrackingDynamicExpressionPartRecursiveSplitResult<std::string>>& actual
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
				::CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartRecursiveSplitter
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
		using PartType = CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>;

		std::vector<PartType> parts;
		// TODO: Consider using a more direct way of comparing results.
		std::optional<std::string> expectedResult;


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const FakeHalfwayDynamicExpressionPartRecursiveSplitter_tryToSplit_TestData& testData
		)
		{
			ostream
				<< "FakeHalfwayDynamicExpressionPartRecursiveSplitter.tryToSplit({"
				<< stringifySplittingParts(testData.parts)
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
			.parts{ makeExpressionParts({ "Part1" }) },
			.expectedResult{ std::make_optional<std::string>("{[Part1]->null<Part1>null}") }
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2" }) },
			.expectedResult{}
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3" }) },
			.expectedResult{ std::make_optional<std::string>("{[Part1,Part2,Part3]->{[Part1]->null<Part1>null}<Part2>{[Part3]->null<Part3>null}}") }
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4" }) },
			.expectedResult{}
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4", "Part5" }) },
			.expectedResult{ std::make_optional<std::string>("{[Part1,Part2,Part3,Part4,Part5]->{null<Part1>null}<Part2>{[Part3,Part4,Part5]->{[Part3]->null<Part3>null}<Part4>{[Part5]->null<Part5>null}}}") }
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6" }) },
			.expectedResult{}
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7" }) },
			.expectedResult{ std::make_optional<std::string>("{[Part1,Part2,Part3,Part4,Part5,Part6,Part7]->{[Part1,Part2,Part3]->{[Part1]->null<Part1>null}<Part2>{[Part3]->null<Part3>null}}<Part4>{[Part5,Part6,Part7]->{[Part5]->null<Part5>null}<Part6>{[Part7]->null<Part7>null}}}") }
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7", "Part8" }) },
			.expectedResult{}
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7", "Part8", "Part9" }) },
			.expectedResult{ std::make_optional<std::string>("{[Part1,Part2,Part3,Part4,Part5,Part6,Part7,Part8,Part9]->{[Part1,Part2,Part3]->{[Part1]->null<Part1>null}<Part2>{[Part3]->null<Part3>null}}<Part4>{[Part5,Part6,Part7,Part8,Part9]->{[Part5]->null<Part5>null}<Part6>{[Part7,Part8,Part9]->{[Part7]->null<Part7>null}<Part8>{[Part9]->null<Part9>null}}}}") }
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7", "Part8", "Part9", "Part10" }) },
			.expectedResult{}
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7", "Part8", "Part9", "Part10", "Part11" }) },
			.expectedResult{ std::make_optional<std::string>("{[Part1,Part2,Part3,Part4,Part5,Part6,Part7,Part8,Part9,Part10,Part11]->{[Part1,Part2,Part3,Part4,Part5]->{[Part1]->null<Part1>null}<Part2>{[Part3,Part4,Part5]->{[Part3]->null<Part3>null}<Part4>{[Part5]->null<Part5>null}}}<Part6>{[Part7,Part8,Part9,Part10,Part11]->{[Part1]->null<Part7>null}<Part8>{[Part9,Part10,Part11]->{[Part9]->null<Part9>null}<Part10>{[Part11]->null<Part11>null}}}}") }
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
		const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto partsView
		{
			GetParam().parts
			| std::views::transform
			(
				[](const auto& part)
				{ return std::ref(part); }
			)
		};
		const std::optional<std::string> expectedReturnValue{ GetParam().expectedResult };
		::CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartRecursiveSplitter<std::string> instance{};

		// Act
		CmdCalculator::Optional auto returnValue
		{
			instance.tryToSplit(partsView)
		};

		// Assert
		ASSERT_EQ(expectedReturnValue.has_value(), returnValue.has_value());
		if (expectedReturnValue.has_value())
			EXPECT_EQ(expectedReturnValue.value(), returnValue.value().STUB_getStringRepresentation());
	}

#pragma endregion
}