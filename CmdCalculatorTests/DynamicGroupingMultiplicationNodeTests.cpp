#include "pch.h"

#include <string>
#include <algorithm>
#include <iterator>
#include <memory>
#include <span>
#include <functional>
#include <vector>

#include "../CmdCalculator/DynamicGroupingMultiplicationNode.h"
#include "../CmdCalculator/DynamicOperandNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicOperandNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicGroupingNode.h"

namespace CmdCalculatorTestDoubleTests
{
	struct DynamicGroupingMultiplicationNode_TestParams
	{
		using HeadType = CmdCalculator::MathAst::DynamicOperandNode<std::string>;
		using TailType = CmdCalculator::MathAst::DynamicGroupingNode<std::string>;
		using TailRangeType = std::vector<std::unique_ptr<TailType>>;
		using TailViewType = std::ranges::owning_view<TailRangeType>;

		std::function<std::unique_ptr<HeadType>()> headMultiplicand;
		std::function<TailViewType()> tailMultiplicands;
		std::string leadingTrivia;
		std::string trailingTrivia;
		std::string stringRepresentation;
	};

	class DynamicGroupingMultiplicationNodeWithCtorParamsTests :
		public testing::TestWithParam<DynamicGroupingMultiplicationNode_TestParams>
	{};

	DynamicGroupingMultiplicationNode_TestParams DynamicGroupingMultiplicationNode_TestParamsValues[]
	{
		DynamicGroupingMultiplicationNode_TestParams
		{
			.headMultiplicand
			{
				[]()
				{
					return std::move
					(
						std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string>>
							("", "", "Head")
					);
				}
			},
			.tailMultiplicands
			{
				[]
				()
				{
					return DynamicGroupingMultiplicationNode_TestParams::TailViewType
					{};
				}
			},
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.stringRepresentation{ "Head" }
		},
		DynamicGroupingMultiplicationNode_TestParams
		{
			.headMultiplicand
			{
				[]()
				{
					return std::move
					(
						std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string>>
							("", "", "Head")
					);
				}
			},
			.tailMultiplicands
			{
				[]()
				{
					return DynamicGroupingMultiplicationNode_TestParams::TailViewType
					{
						std::move
						(
							DynamicGroupingMultiplicationNode_TestParams::TailRangeType
							{
								std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>>
									(nullptr, "", "", "(Tail)")
							}
						)
					};
				}
			},
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.stringRepresentation{ "Head(Tail)" }
		},
		DynamicGroupingMultiplicationNode_TestParams
		{
			.headMultiplicand
			{
				[]()
				{
					return std::move
					(
						std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string>>
							("", "", "Head")
					);
				}
			},
			.tailMultiplicands
			{
				[]()
				{
					return DynamicGroupingMultiplicationNode_TestParams::TailViewType
					{
						std::move
						(
							DynamicGroupingMultiplicationNode_TestParams::TailRangeType
							{
								std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>>
									(nullptr, "", "", "(Tail1)"),
								std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>>
									(nullptr, "", "", "(Tail2)"),
								std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>>
									(nullptr, "", "", "(Tail3)")
							}
						)
					};
				},
			},
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.stringRepresentation{ "Head(Tail1)(Tail2)(Tail3)" }
		},
		DynamicGroupingMultiplicationNode_TestParams
		{
			.headMultiplicand
			{
				[]()
				{
					return std::move
					(
						std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string>>
							("", "", "Head")
					);
				}
			},
			.tailMultiplicands
			{
				[]()
				{
					return DynamicGroupingMultiplicationNode_TestParams::TailViewType
					{
						std::move
						(
							DynamicGroupingMultiplicationNode_TestParams::TailRangeType
							{
								std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>>
									(nullptr, "", "", "(Tail)")
							}
						)
					};
				}
			},
			.leadingTrivia{ "  " },
			.trailingTrivia{ " " },
			.stringRepresentation{ "  Head(Tail) " }
		},
		DynamicGroupingMultiplicationNode_TestParams
		{
			.headMultiplicand
			{
				[]()
				{
					return std::move
					(
						std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string>>
							("", "", "Head")
					);
				}
			},
			.tailMultiplicands
			{
				[]()
				{
					return DynamicGroupingMultiplicationNode_TestParams::TailViewType
					{
						std::move
						(
							DynamicGroupingMultiplicationNode_TestParams::TailRangeType
							{
								std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>>
									(nullptr, "", "", "(Tail)")
							}
						)
					};
				}
			},
			.leadingTrivia{ "  " },
			.trailingTrivia{ "  " },
			.stringRepresentation{ "  Head(Tail)  " }
		},
		DynamicGroupingMultiplicationNode_TestParams
		{
			.headMultiplicand
			{
				[]()
				{
					return std::move
					(
						std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string>>
							("", "", "Head")
					);
				}
			},
			.tailMultiplicands
			{
				[]()
				{
					return DynamicGroupingMultiplicationNode_TestParams::TailViewType
					{
						std::move
						(
							DynamicGroupingMultiplicationNode_TestParams::TailRangeType
							{
								std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>>
									(nullptr, "", "", "(Tail)")
							}
						)
					};
				}
			},
			.leadingTrivia{ " " },
			.trailingTrivia{ "  " },
			.stringRepresentation{ " Head(Tail)  " }
		}
	};

#pragma region Instantiate DynamicGroupingMultiplicationNodeWithCtorParamsTests
	INSTANTIATE_TEST_CASE_P
	(
		DynamicGroupingMultiplicationNodeTests,
		DynamicGroupingMultiplicationNodeWithCtorParamsTests,
		testing::ValuesIn(DynamicGroupingMultiplicationNode_TestParamsValues)
	);
#pragma endregion


	TEST_P(DynamicGroupingMultiplicationNodeWithCtorParamsTests, DynamicGroupingMultiplicationNode$has$expected$state)
	{
		// Arrange
		auto headMultiplicandToPass{ GetParam().headMultiplicand() };
		std::ranges::owning_view<decltype(GetParam().tailMultiplicands())> tailMultiplicandsToPass
		{
			GetParam().tailMultiplicands()
		};
		const std::string leadingTriviaToPass{ GetParam().leadingTrivia };
		const std::string trailingTriviaToPass{ GetParam().trailingTrivia };

		const std::string expectedHeadMultiplicandStringRepresentation
		{
			GetParam().headMultiplicand()->getStringRepresentation()
		};
		const auto expectedTailMultiplicandStringRepresentations
		{
			GetParam().tailMultiplicands()
			| std::views::transform
			(
				[](auto& tailMultiplicand)
				{
					return tailMultiplicand->getStringRepresentation();
				}
			)
		};
		const std::string expectedLeadingTrivia{ GetParam().leadingTrivia };
		const std::string expectedTrailingTrivia{ GetParam().trailingTrivia };
		const std::string expectedStringRepresentation{ GetParam().stringRepresentation };

		// Act
		CmdCalculator::MathAst::DynamicGroupingMultiplicationNode<std::string> instance
		{
			std::move(headMultiplicandToPass),
			std::move(tailMultiplicandsToPass),
			leadingTriviaToPass,
			trailingTriviaToPass
		};

		// Assert
		EXPECT_EQ(expectedHeadMultiplicandStringRepresentation, instance.getHeadMultiplicand()->getStringRepresentation());
		EXPECT_TRUE
		(
			std::ranges::equal
			(
				expectedTailMultiplicandStringRepresentations,
				instance.getTailMultiplicands()
				| std::views::transform
				(
					[](auto* tailMultiplicand)
					{
						return tailMultiplicand->getStringRepresentation();
					}
				)
			)
		);
		EXPECT_EQ(expectedLeadingTrivia, instance.getLeadingTrivia());
		EXPECT_EQ(expectedTrailingTrivia, instance.getTrailingTrivia());
		EXPECT_EQ(expectedStringRepresentation, instance.getStringRepresentation());
	}
}