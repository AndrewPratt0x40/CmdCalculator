#include "pch.h"

#include <string>
#include <algorithm>
#include <ranges>
#include <optional>
#include <vector>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/DynamicExpressionPartSingleSplitter.h"
#include "../CmdCalculatorTestDoubles/FakeHalfwayDynamicExpressionPartSingleSplitter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(FakeHalfwayDynamicExpressionPartSingleSplitterTests, FakeHalfwayDynamicExpressionPartSingleSplitter$satisfies$DynamicExpressionPartSingleSplitter$concept)
	{
		static_assert
		(
			::CmdCalculator::DynamicExpressionPartSingleSplitter
			<
				CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSingleSplitter
				<
					std::string
				>
			>
		);
	}

#pragma endregion


#pragma region Shared test data

	struct FakeHalfwayDynamicExpressionPartSingleSplitter_TestData
	{
		using PartType = CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>;

		std::vector<PartType> parts;
		bool expectCanSplit;
		std::vector<std::string> expectedLeftParts;
		std::optional<std::string> expectedSplitPart;
		std::vector<std::string> expectedRightParts;
	};


	CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
		makeExpressionPart(std::string stringRepresentation)
	{
		return CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
		{
			false,
			"",
			"",
			stringRepresentation
		};
	}


	std::optional<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>>
		makeOptionalExpressionPart(std::string stringRepresentation)
	{
		return std::make_optional<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>>
			(makeExpressionPart(stringRepresentation))
		;
	}


	std::vector<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>>
		makeExpressionParts(std::initializer_list<std::string> stringRepresentations)
	{
		std::ranges::input_range auto partsView
		{
			stringRepresentations
			| std::views::transform
			(
				[](const std::string& stringRepresentation)
				{ return makeExpressionPart(stringRepresentation); }
			)
		};

		return std::vector<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>>
		{
			std::ranges::begin(partsView),
			std::ranges::end(partsView)
		};
	}


	const FakeHalfwayDynamicExpressionPartSingleSplitter_TestData FakeHalfwayDynamicExpressionPartSingleSplitter_TestDataValues[]
	{
		{
			.parts{},
			.expectCanSplit{ false },
			.expectedLeftParts{},
			.expectedSplitPart{},
			.expectedRightParts{}
		},
		{
			.parts{ makeExpressionParts({ "Part1" }) },
			.expectCanSplit{ false },
			.expectedLeftParts{},
			.expectedSplitPart{},
			.expectedRightParts{}
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2" }) },
			.expectCanSplit{ false },
			.expectedLeftParts{},
			.expectedSplitPart{},
			.expectedRightParts{}
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3" }) },
			.expectCanSplit{ true },
			.expectedLeftParts{ "Part1" },
			.expectedSplitPart{ "Part2" },
			.expectedRightParts{ "Part3" }
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4" }) },
			.expectCanSplit{ true },
			.expectedLeftParts{ "Part1", "Part2" },
			.expectedSplitPart{ "Part3" },
			.expectedRightParts{ "Part4" }
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4", "Part5" }) },
			.expectCanSplit{ true },
			.expectedLeftParts{ "Part1", "Part2" },
			.expectedSplitPart{ "Part3" },
			.expectedRightParts{ "Part4", "Part5" }
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6" })},
			.expectCanSplit{ true },
			.expectedLeftParts{ "Part1", "Part2", "Part3" },
			.expectedSplitPart{ "Part4" },
			.expectedRightParts{ "Part5", "Part6" }
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7" })},
			.expectCanSplit{ true },
			.expectedLeftParts{ "Part1", "Part2", "Part3" },
			.expectedSplitPart{ "Part4" },
			.expectedRightParts{ "Part5", "Part6", "Part7" }
		}
	};


	TEST(FakeHalfwayDynamicExpressionPartSingleSplitter$TestDataTests, canSplit$IFF$has$at$least$3$parts)
	{
		EXPECT_TRUE
		(
			std::ranges::all_of
			(
				FakeHalfwayDynamicExpressionPartSingleSplitter_TestDataValues,
				[](const FakeHalfwayDynamicExpressionPartSingleSplitter_TestData& testData)
				{ return testData.expectCanSplit == (testData.parts.size() >= 3); }
			)
		);
	}


	TEST(FakeHalfwayDynamicExpressionPartSingleSplitter$TestDataTests, expectedLeftParts$given$IFF$canSplit)
	{
		EXPECT_TRUE
		(
			std::ranges::all_of
			(
				FakeHalfwayDynamicExpressionPartSingleSplitter_TestDataValues,
				[](const FakeHalfwayDynamicExpressionPartSingleSplitter_TestData& testData)
				{
					return testData.expectCanSplit != testData.expectedLeftParts.empty();
				}
			)
		);
	}


	TEST(FakeHalfwayDynamicExpressionPartSingleSplitter$TestDataTests, expectedSplitPart$given$IFF$canSplit)
	{
		EXPECT_TRUE
		(
			std::ranges::all_of
			(
				FakeHalfwayDynamicExpressionPartSingleSplitter_TestDataValues,
				[](const FakeHalfwayDynamicExpressionPartSingleSplitter_TestData& testData)
				{
					return testData.expectCanSplit == testData.expectedSplitPart.has_value();
				}
			)
		);
	}


	TEST(FakeHalfwayDynamicExpressionPartSingleSplitter$TestDataTests, expectedRightParts$given$IFF$canSplit)
	{
		EXPECT_TRUE
		(
			std::ranges::all_of
			(
				FakeHalfwayDynamicExpressionPartSingleSplitter_TestDataValues,
				[](const FakeHalfwayDynamicExpressionPartSingleSplitter_TestData& testData)
				{
					return testData.expectCanSplit != testData.expectedRightParts.empty();
				}
			)
		);
	}

#pragma endregion


#pragma region canSplit

#pragma region canSplit with less than 3 parts

	class FakeHalfwayDynamicExpressionPartSingleSplitter$canSplit$withLessThan3Parts$Tests :
		public testing::TestWithParam<FakeHalfwayDynamicExpressionPartSingleSplitter_TestData>
	{};

	const std::ranges::input_range auto FakeHalfwayDynamicExpressionPartSingleSplitter_lessThan3Parts_TestDataValues
	{
		FakeHalfwayDynamicExpressionPartSingleSplitter_TestDataValues
		| std::views::filter
		(
			[](const FakeHalfwayDynamicExpressionPartSingleSplitter_TestData& testData)
			{ return testData.parts.size() < 3; }
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FakeHalfwayDynamicExpressionPartSingleSplitterTests,
		FakeHalfwayDynamicExpressionPartSingleSplitter$canSplit$withLessThan3Parts$Tests,
		CmdCalculatorTestUtils::ValuesInRange(FakeHalfwayDynamicExpressionPartSingleSplitter_lessThan3Parts_TestDataValues)
	);


	TEST_P(FakeHalfwayDynamicExpressionPartSingleSplitter$canSplit$withLessThan3Parts$Tests, calling$canSplit$with$less$than$3$parts$returns$false)
	{
		// Arrange
		ASSERT_FALSE(GetParam().expectCanSplit);
		const ::CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto parts
		{
			GetParam().parts
			| std::views::transform
			(
				[](const CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>& part)
				{ return std::ref(part); }
			)
		};
		CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSingleSplitter<std::string> instance{};

		// Act
		const bool returnValue{ instance.canSplit(parts) };

		// Assert
		EXPECT_FALSE(returnValue);
	}

#pragma endregion


#pragma region canSplit with at least 3 parts

	class FakeHalfwayDynamicExpressionPartSingleSplitter$canSplit$withAtLeast3Parts$Tests :
		public testing::TestWithParam<FakeHalfwayDynamicExpressionPartSingleSplitter_TestData>
	{};

	const std::ranges::input_range auto FakeHalfwayDynamicExpressionPartSingleSplitter_atLeast3Parts_TestDataValues
	{
		FakeHalfwayDynamicExpressionPartSingleSplitter_TestDataValues
		| std::views::filter
		(
			[](const FakeHalfwayDynamicExpressionPartSingleSplitter_TestData& testData)
			{ return testData.parts.size() >= 3; }
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FakeHalfwayDynamicExpressionPartSingleSplitterTests,
		FakeHalfwayDynamicExpressionPartSingleSplitter$canSplit$withAtLeast3Parts$Tests,
		CmdCalculatorTestUtils::ValuesInRange(FakeHalfwayDynamicExpressionPartSingleSplitter_atLeast3Parts_TestDataValues)
	);


	TEST_P(FakeHalfwayDynamicExpressionPartSingleSplitter$canSplit$withAtLeast3Parts$Tests, calling$canSplit$with$at$least$3$parts$returns$true)
	{
		// Arrange
		ASSERT_FALSE(GetParam().expectCanSplit);
		const ::CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto parts
		{
			GetParam().parts
			| std::views::transform
			(
				[](const CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>& part)
				{ return std::ref(part); }
			)
		};
		CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSingleSplitter<std::string> instance{};

		// Act
		const bool returnValue{ instance.canSplit(parts) };

		// Assert
		EXPECT_TRUE(returnValue);
	}

#pragma endregion

#pragma endregion


#pragma region tryToSplit

#pragma region tryToSplit with any parts

	class FakeHalfwayDynamicExpressionPartSingleSplitter$tryToSplit$withAnyParts$Tests :
		public testing::TestWithParam<FakeHalfwayDynamicExpressionPartSingleSplitter_TestData>
	{};

	INSTANTIATE_TEST_CASE_P
	(
		FakeHalfwayDynamicExpressionPartSingleSplitterTests,
		FakeHalfwayDynamicExpressionPartSingleSplitter$tryToSplit$withAnyParts$Tests,
		testing::ValuesIn(FakeHalfwayDynamicExpressionPartSingleSplitter_TestDataValues)
	);


	TEST_P(FakeHalfwayDynamicExpressionPartSingleSplitter$tryToSplit$withAnyParts$Tests, calling$tryToSplit$returns$value$IFF$canSplit$returns$true)
	{
		// Arrange
		const ::CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto parts
		{
			GetParam().parts
			| std::views::transform
			(
				[](const CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>& part)
				{ return std::ref(part); }
			)
		};
		CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSingleSplitter<std::string> instance{};

		// Act
		const bool canSplitReturnValue{ instance.canSplit(parts) };
		const bool tryToSplitReturnedNonEmptyValue{ instance.tryToSplit(parts).has_value() };

		// Assert
		EXPECT_EQ(canSplitReturnValue, tryToSplitReturnedNonEmptyValue);
	}

#pragma endregion


#pragma region tryToSplit with splittable parts

	class FakeHalfwayDynamicExpressionPartSingleSplitter$tryToSplit$withSplittableParts$Tests :
		public testing::TestWithParam<FakeHalfwayDynamicExpressionPartSingleSplitter_TestData>
	{};

	const std::ranges::input_range auto FakeHalfwayDynamicExpressionPartSingleSplitter_splittableParts_TestDataValues
	{
		FakeHalfwayDynamicExpressionPartSingleSplitter_TestDataValues
		| std::views::filter
		(
			[](const FakeHalfwayDynamicExpressionPartSingleSplitter_TestData& testData)
			{ return testData.expectCanSplit; }
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FakeHalfwayDynamicExpressionPartSingleSplitterTests,
		FakeHalfwayDynamicExpressionPartSingleSplitter$tryToSplit$withSplittableParts$Tests,
		CmdCalculatorTestUtils::ValuesInRange(FakeHalfwayDynamicExpressionPartSingleSplitter_splittableParts_TestDataValues)
	);


	TEST_P(FakeHalfwayDynamicExpressionPartSingleSplitter$tryToSplit$withSplittableParts$Tests, calling$tryToSplit$with$splittable$parts$returns$split$parts)
	{
		// Arrange
		const ::CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto parts
		{
			GetParam().parts
			| std::views::transform
			(
				[](const CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>& part)
				{ return std::ref(part); }
			)
		};
		CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSingleSplitter<std::string> instance{};

		// Act
		const std::optional<CmdCalculatorTestDoubles::StubDynamicExpressionPartSingleSplitResult<std::string>> returnValue
		{
			instance.tryToSplit(parts)
		};

		// Assert
		ASSERT_TRUE(returnValue.has_value());
		EXPECT_TRUE
		(
			std::ranges::equal
			(
				GetParam().expectedLeftParts,
				returnValue.value().getLeftParts()
				| std::views::transform
				(
					[](const ::CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>& expressionPart)
					{ return expressionPart.getStringRepresentation(); }
				)
			)
		);
		EXPECT_EQ(GetParam().expectedSplitPart, returnValue.value().getSplitPart().getStringRepresentation());
		EXPECT_TRUE
		(
			std::ranges::equal
			(
				GetParam().expectedRightParts,
				returnValue.value().getRightParts()
				| std::views::transform
				(
					[](const ::CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>& expressionPart)
					{ return expressionPart.getStringRepresentation(); }
				)
			)
		);
	}

#pragma endregion

#pragma endregion
}