#include "pch.h"

#include <string>
#include <string_view>
#include <ranges>
#include <concepts>
#include <memory>
#include <functional>
#include <vector>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/SingularInvokingDEPSplitter.h"
#include "../CmdCalculator/DynamicExpressionPartRecursiveSplitter.h"
#include "../CmdCalculatorTestDoubles/FakeHalfwayDynamicExpressionPartSingleSplitter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"


namespace CmdCalculatorTests
{
#pragma region Concept satisfaction
	
	TEST(SingularInvokingDEPSplitterTests, SingularInvokingDEPSplitter$satisfies$the$DynamicExpressionPartRecursiveSplitter$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicExpressionPartRecursiveSplitter
			<
				CmdCalculator::SingularInvokingDEPSplitter
				<
					CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSingleSplitter<std::string>
				>
			>
		);
	}

#pragma endregion


#pragma region tryToSplit

	struct SingularInvokingDEPSplitter_tryToSplit_result_TestData
	{
		std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData> leftPart;
		std::string splitPart;
		std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData> rightPart;
		
		
		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const SingularInvokingDEPSplitter_tryToSplit_result_TestData& testData
		)
		{
			ostream << '{';
			if (testData.leftPart)
				ostream << *testData.leftPart;
			else
				ostream << "null";
			ostream
				<< '<'
				<< testData.splitPart
				<< '>'
			;
			if (testData.rightPart)
				ostream << *testData.rightPart;
			else
				ostream << "null";
			ostream << '}';

			return ostream;
		}
	};


#pragma region Utility funcs to compare tryToSplit Results

	static bool compare_tryToSplitResult
	(
		const SingularInvokingDEPSplitter_tryToSplit_result_TestData& expected,
		const CmdCalculator::BasicDEPRecursiveSplitResult<std::string>& actual
	);

	static bool compare_tryToSplitSidePartResult
	(
		const std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>& expected,
		const CmdCalculator::BasicDEPRecursiveSplitResult<std::string>* actual
	)
	{
		return expected
			? actual && compare_tryToSplitResult(*expected, *actual)
			: !actual
		;
	}

	static bool compare_tryToSplitSplitPartResult
	(
		const std::string_view expected,
		const CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>& actual
	)
	{
		return expected == actual.getStringRepresentation();
	}

	static bool compare_tryToSplitResult
	(
		const SingularInvokingDEPSplitter_tryToSplit_result_TestData& expected,
		const CmdCalculator::BasicDEPRecursiveSplitResult<std::string>& actual
	)
	{
		return
			compare_tryToSplitSidePartResult(expected.leftPart, actual.getLeftPart())
			&& compare_tryToSplitSplitPartResult(expected.splitPart, actual.getSplitPart())
			&& compare_tryToSplitSidePartResult(expected.rightPart, actual.getRightPart())
		;
	}

#pragma endregion


	struct SingularInvokingDEPSplitter_tryToSplit_TestData
	{
		std::vector<std::string> parts;
		std::function<std::optional<SingularInvokingDEPSplitter_tryToSplit_result_TestData>()> expected;
		
		
		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const SingularInvokingDEPSplitter_tryToSplit_TestData& testData
		)
		{
			ostream
				<< "SingularInvokingDEPSplitter.tryToSplit("
				<< CmdCalculatorTestUtils::joinStrings(testData.parts)
				<< ") = "
			;

			const auto expected{ testData.expected() };
			if (expected.has_value())
				ostream << expected.value();
			else
				ostream << "{}";

			return ostream;
		}
	};

	class SingularInvokingDEPSplitter$tryToSplit$Tests :
		public testing::TestWithParam<SingularInvokingDEPSplitter_tryToSplit_TestData>
	{};

	const SingularInvokingDEPSplitter_tryToSplit_TestData SingularInvokingDEPSplitter_tryToSplit_TestDataValues[]
	{
		// TODO: This is pretty hard to read; consider using an external data source such as a json file.
		{
			.parts{},
			.expected
			{
				[]()
				{
					return std::optional<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{};
				}
			}
		},
		{
			.parts{ "Part1" },
			.expected
			{
				[]()
				{
					return std::optional<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{};
				}
			}
		},
		{
			.parts{ "Part1", "Part2" },
			.expected
			{
				[]()
				{
					return std::optional<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{};
				}
			}
		},
		{
			.parts{ "Part1", "Part2", "Part3" },
			.expected
			{
				[]()
				{
					return std::make_optional<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
					(
						std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
						(
							std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
							"Part1",
							std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
						),
						"Part2",
						std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
						(
							std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
							"Part3",
							std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
						)
					);
				}
			}
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4" },
			.expected
			{
				[]()
				{
					return std::optional<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{};
				}
			}
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4", "Part5" },
			.expected
			{
				[]()
				{
					return std::optional<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{};
				}
			}
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6" },
			.expected
			{
				[]()
				{
					return std::optional<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{};
				}
			}
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7" },
			.expected
			{
				[]()
				{
					return std::make_optional<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
					(
						std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
						(
								std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
								(
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
									"Part1",
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
								),
								"Part2",
								std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
								(
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
									"Part3",
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
								)
						),
						"Part4",
						std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
						(
								std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
								(
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
									"Part5",
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
								),
								"Part6",
								std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
								(
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
									"Part7",
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
								)
						)
					);
				}
			}
		},
		{
			.parts{ "Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7" },
			.expected
			{
				[]()
				{
					return std::make_optional<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
					(
						std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
						(
								std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
								(
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
									"Part1",
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
								),
								"Part2",
								std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
								(
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
									"Part3",
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
								)
						),
						"Part4",
						std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
						(
								std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
								(
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
									"Part5",
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
								),
								"Part6",
								std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
								(
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
									"Part7",
									std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
								)
						)
					);
				}
			}
		},
		{
			.parts
			{
				"Part1", "Part2", "Part3", "Part4", "Part5", "Part6", "Part7", "Part8",
				"Part9", "Part10", "Part11", "Part12", "Part13", "Part14", "Part15"
			},
			.expected
			{
				[]()
				{
					return std::make_optional<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
					(
						std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
						(
								std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
								(
									std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
									(
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
										"Part1",
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
									),
									"Part2",
									std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
									(
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
										"Part3",
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
									)
								),
								"Part4",
								std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
								(
									std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
									(
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
										"Part5",
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
									),
									"Part6",
									std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
									(
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
										"Part7",
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
									)
								)
						),
						"Part8",
						std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
						(
								std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
								(
									std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
									(
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
										"Part9",
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
									),
									"Part10",
									std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
									(
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
										"Part11",
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
									)
								),
								"Part12",
								std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
								(
									std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
									(
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
										"Part13",
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
									),
									"Part14",
									std::make_unique<SingularInvokingDEPSplitter_tryToSplit_result_TestData>
									(
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{},
										"Part15",
										std::unique_ptr<SingularInvokingDEPSplitter_tryToSplit_result_TestData>{}
									)
								)
						)
					);
				}
			}
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		SingularInvokingDEPSplitterTests,
		SingularInvokingDEPSplitter$tryToSplit$Tests,
		testing::ValuesIn(SingularInvokingDEPSplitter_tryToSplit_TestDataValues)
	);

	TEST_P(SingularInvokingDEPSplitter$tryToSplit$Tests, calling$tryToSplit$returns$expected$result)
	{
		// Arrange
		using SingularSplitterType = CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSingleSplitter<std::string>;

		const std::optional<SingularInvokingDEPSplitter_tryToSplit_result_TestData> expected
		{
			GetParam().expected()
		};

		const std::ranges::range auto expressionPartsRange
		{
			GetParam().parts
			| std::views::transform
			(
				[](const std::string& part)
				{
					return CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
					{
						false, "", "", part
					};
				}
			)
		};
		const std::vector<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>> expressionParts
		{
			std::ranges::begin(expressionPartsRange),
			std::ranges::end(expressionPartsRange)
		};
		const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto expressionPartRefsView
		{
			expressionParts
			| std::views::transform
			(
				[](const CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>& part)
				{ return std::ref(part); }
			)
		};

		SingularSplitterType singularSplitter{};
		CmdCalculator::SingularInvokingDEPSplitter<SingularSplitterType> instance
		{
			std::move(singularSplitter)
		};

		// Act
		const std::optional<CmdCalculator::BasicDEPRecursiveSplitResult<std::string>> returnValue
		{
			instance.tryToSplit(expressionPartRefsView)
		};

		// Assert
		if (!expected.has_value())
			EXPECT_FALSE(returnValue.has_value());
		else
		{
			ASSERT_TRUE(returnValue.has_value());
			EXPECT_TRUE(compare_tryToSplitResult(expected.value(), returnValue.value()));
		}
	}

#pragma endregion
}