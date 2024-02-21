#include "pch.h"

#include <string>
#include <algorithm>
#include <ranges>
#include <optional>
#include <vector>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/DynamicExpressionPartSplitter.h"
#include "../CmdCalculatorTestDoubles/FakeHalfwayDynamicExpressionPartSplitter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(FakeHalfwayDynamicExpressionPartSplitterTests, FakeHalfwayDynamicExpressionPartSplitter$satisfies$DynamicExpressionPartSplitter$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicExpressionPartSplitter
			<
				CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSplitter
				<
					std::string
				>,
				std::ranges::ref_view
				<
					std::vector
					<
						std::reference_wrapper
						<
							CmdCalculator::MathAst::DynamicExpressionPartNode
							<
								std::string
							>
						>
					>
				>
			>
		);
	}

#pragma endregion


#pragma region Shared test data

	struct FakeHalfwayDynamicExpressionPartSplitter_TestData
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


	const FakeHalfwayDynamicExpressionPartSplitter_TestData FakeHalfwayDynamicExpressionPartSplitter_TestDataValues[]
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
			.expectCanSplit{ false },
			.expectedLeftParts{},
			.expectedSplitPart{},
			.expectedRightParts{}
		},
		{
			.parts{ makeExpressionParts({ "Part1", "Part2", "Part3", "Part4", "Part5" }) },
			.expectCanSplit{ true },
			.expectedLeftParts{ "Part1", "Part2" },
			.expectedSplitPart{ "Part3" },
			.expectedRightParts{ "Part4", "Part5" }
		}
	};


	TEST(FakeHalfwayDynamicExpressionPartSplitter$TestDataTests, canSplit$IFF$less$than$3$or$odd$number$of$parts)
	{
		EXPECT_TRUE
		(
			std::ranges::all_of
			(
				FakeHalfwayDynamicExpressionPartSplitter_TestDataValues,
				[](const FakeHalfwayDynamicExpressionPartSplitter_TestData& testData)
				{
					return
						testData.expectCanSplit
						==
						(
							testData.parts.size() < 3
							|| testData.parts.size() % 2 != 0
						)
					;
				}
			)
		);
	}


	TEST(FakeHalfwayDynamicExpressionPartSplitter$TestDataTests, expectedLeftParts$given$IFF$canSplit)
	{
		EXPECT_TRUE
		(
			std::ranges::all_of
			(
				FakeHalfwayDynamicExpressionPartSplitter_TestDataValues,
				[](const FakeHalfwayDynamicExpressionPartSplitter_TestData& testData)
				{
					return testData.expectCanSplit != testData.expectedLeftParts.empty();
				}
			)
		);
	}


	TEST(FakeHalfwayDynamicExpressionPartSplitter$TestDataTests, expectedSplitPart$given$IFF$canSplit)
	{
		EXPECT_TRUE
		(
			std::ranges::all_of
			(
				FakeHalfwayDynamicExpressionPartSplitter_TestDataValues,
				[](const FakeHalfwayDynamicExpressionPartSplitter_TestData& testData)
				{
					return testData.expectCanSplit == testData.expectedSplitPart.has_value();
				}
			)
		);
	}


	TEST(FakeHalfwayDynamicExpressionPartSplitter$TestDataTests, expectedRightParts$given$IFF$canSplit)
	{
		EXPECT_TRUE
		(
			std::ranges::all_of
			(
				FakeHalfwayDynamicExpressionPartSplitter_TestDataValues,
				[](const FakeHalfwayDynamicExpressionPartSplitter_TestData& testData)
				{
					return testData.expectCanSplit != testData.expectedRightParts.empty();
				}
			)
		);
	}

#pragma endregion


#pragma region canSplit

#pragma region canSplit with less than 3 parts

	class FakeHalfwayDynamicExpressionPartSplitter$canSplit$withLessThan3Parts$Tests :
		public testing::TestWithParam<FakeHalfwayDynamicExpressionPartSplitter_TestData>
	{};

	const std::ranges::input_range auto FakeHalfwayDynamicExpressionPartSplitter_lessThan3Parts_TestDataValues
	{
		FakeHalfwayDynamicExpressionPartSplitter_TestDataValues
		| std::views::filter
		(
			[](const FakeHalfwayDynamicExpressionPartSplitter_TestData& testData)
			{ return testData.parts.size() < 3; }
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FakeHalfwayDynamicExpressionPartSplitterTests,
		FakeHalfwayDynamicExpressionPartSplitter$canSplit$withLessThan3Parts$Tests,
		CmdCalculatorTestUtils::ValuesInRange(FakeHalfwayDynamicExpressionPartSplitter_lessThan3Parts_TestDataValues)
	);


	TEST_P(FakeHalfwayDynamicExpressionPartSplitter$canSplit$withLessThan3Parts$Tests, calling$canSplit$with$less$than$3$parts$returns$false)
	{
		// Arrange
		ASSERT_FALSE(GetParam().expectCanSplit);
		const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto parts
		{
			GetParam().parts
			| std::views::transform
			(
				[](const CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>& part)
				{ return std::ref(part); }
			)
		};
		CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSplitter<std::string> instance{};

		// Act
		const bool returnValue{ instance.canSplit(parts) };

		// Assert
		EXPECT_FALSE(returnValue);
	}

#pragma endregion


#pragma region canSplit with an even amount of parts

	class FakeHalfwayDynamicExpressionPartSplitter$canSplit$withEvenNumParts$Tests :
		public testing::TestWithParam<FakeHalfwayDynamicExpressionPartSplitter_TestData>
	{};

	const std::ranges::input_range auto FakeHalfwayDynamicExpressionPartSplitter_evenNumParts_TestDataValues
	{
		FakeHalfwayDynamicExpressionPartSplitter_TestDataValues
		| std::views::filter
		(
			[](const FakeHalfwayDynamicExpressionPartSplitter_TestData& testData)
			{ return testData.parts.size() % 2 == 0; }
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FakeHalfwayDynamicExpressionPartSplitterTests,
		FakeHalfwayDynamicExpressionPartSplitter$canSplit$withEvenNumParts$Tests,
		CmdCalculatorTestUtils::ValuesInRange(FakeHalfwayDynamicExpressionPartSplitter_evenNumParts_TestDataValues)
	);


	TEST_P(FakeHalfwayDynamicExpressionPartSplitter$canSplit$withEvenNumParts$Tests, calling$canSplit$with$an$even$number$of$parts$returns$false)
	{
		// Arrange
		ASSERT_FALSE(GetParam().expectCanSplit);
		const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto parts
		{
			GetParam().parts
			| std::views::transform
			(
				[](const CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>& part)
				{ return std::ref(part); }
			)
		};
		CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSplitter<std::string> instance{};

		// Act
		const bool returnValue{ instance.canSplit(parts) };

		// Assert
		EXPECT_FALSE(returnValue);
	}

#pragma endregion


#pragma region canSplit with an odd number of at least 3 of parts

	class FakeHalfwayDynamicExpressionPartSplitter$canSplit$withOddNumParts$Tests :
		public testing::TestWithParam<FakeHalfwayDynamicExpressionPartSplitter_TestData>
	{};

	const std::ranges::input_range auto FakeHalfwayDynamicExpressionPartSplitter_oddNumParts_TestDataValues
	{
		FakeHalfwayDynamicExpressionPartSplitter_TestDataValues
		| std::views::filter
		(
			[](const FakeHalfwayDynamicExpressionPartSplitter_TestData& testData)
			{
				return
					(testData.parts.size() >= 3)
					&& (testData.parts.size() % 2 != 0)
				;
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FakeHalfwayDynamicExpressionPartSplitterTests,
		FakeHalfwayDynamicExpressionPartSplitter$canSplit$withOddNumParts$Tests,
		CmdCalculatorTestUtils::ValuesInRange(FakeHalfwayDynamicExpressionPartSplitter_oddNumParts_TestDataValues)
	);


	TEST_P(FakeHalfwayDynamicExpressionPartSplitter$canSplit$withOddNumParts$Tests, calling$canSplit$with$an$odd$number$of$at$least$3$of$parts$returns$true)
	{
		// Arrange
		ASSERT_TRUE(GetParam().expectCanSplit);
		const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto parts
		{
			GetParam().parts
			| std::views::transform
			(
				[](const CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>& part)
				{ return std::ref(part); }
			)
		};
		CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSplitter<std::string> instance{};

		// Act
		const bool returnValue{ instance.canSplit(parts) };

		// Assert
		EXPECT_TRUE(returnValue);
	}

#pragma endregion

#pragma endregion


#pragma region tryToSplit

#pragma region tryToSplit with any parts

	class FakeHalfwayDynamicExpressionPartSplitter$tryToSplit$withAnyParts$Tests :
		public testing::TestWithParam<FakeHalfwayDynamicExpressionPartSplitter_TestData>
	{};

	INSTANTIATE_TEST_CASE_P
	(
		FakeHalfwayDynamicExpressionPartSplitterTests,
		FakeHalfwayDynamicExpressionPartSplitter$tryToSplit$withAnyParts$Tests,
		testing::ValuesIn(FakeHalfwayDynamicExpressionPartSplitter_TestDataValues)
	);


	TEST_P(FakeHalfwayDynamicExpressionPartSplitter$tryToSplit$withAnyParts$Tests, calling$tryToSplit$returns$value$IFF$canSplit$returns$true)
	{
		// Arrange
		const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto parts
		{
			GetParam().parts
			| std::views::transform
			(
				[](const CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>& part)
				{ return std::ref(part); }
			)
		};
		CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSplitter<std::string> instance{};

		// Act
		const bool canSplitReturnValue{ instance.canSplit(parts) };
		const bool tryToSplitReturnedNonEmptyValue{ instance.tryToSplit(parts).has_value() };

		// Assert
		EXPECT_EQ(canSplitReturnValue, tryToSplitReturnedNonEmptyValue);
	}

#pragma endregion


#pragma region tryToSplit with splittable parts

	class FakeHalfwayDynamicExpressionPartSplitter$tryToSplit$withSplittableParts$Tests :
		public testing::TestWithParam<FakeHalfwayDynamicExpressionPartSplitter_TestData>
	{};

	const std::ranges::input_range auto FakeHalfwayDynamicExpressionPartSplitter_splittableParts_TestDataValues
	{
		FakeHalfwayDynamicExpressionPartSplitter_TestDataValues
		| std::views::filter
		(
			[](const FakeHalfwayDynamicExpressionPartSplitter_TestData& testData)
			{ return testData.expectCanSplit; }
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		FakeHalfwayDynamicExpressionPartSplitterTests,
		FakeHalfwayDynamicExpressionPartSplitter$tryToSplit$withSplittableParts$Tests,
		CmdCalculatorTestUtils::ValuesInRange(FakeHalfwayDynamicExpressionPartSplitter_splittableParts_TestDataValues)
	);


	TEST_P(FakeHalfwayDynamicExpressionPartSplitter$tryToSplit$withSplittableParts$Tests, calling$tryToSplit$with$splittable$parts$returns$split$parts)
	{
		// Arrange
		const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto parts
		{
			GetParam().parts
			| std::views::transform
			(
				[](const CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>& part)
				{ return std::ref(part); }
			)
		};
		CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSplitter<std::string> instance{};

		// Act
		const std::optional<CmdCalculatorTestDoubles::StubDynamicExpressionPartSplitResult<std::string>> returnValue
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
					[](const CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>& expressionPart)
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
					[](const CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>& expressionPart)
					{ return expressionPart.getStringRepresentation(); }
				)
			)
		);
	}

#pragma endregion

#pragma endregion
}