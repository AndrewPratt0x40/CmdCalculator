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
		CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string> headMultiplicand;
		std::vector<CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>> tailMultiplicands;
		std::string leadingTrivia;
		std::string trailingTrivia;
		std::string stringRepresentation;
	};

	class DynamicGroupingMultiplicationNodeWithCtorParamsTests :
		public testing::TestWithParam<DynamicGroupingMultiplicationNode_TestParams>
	{};

#pragma region Instantiate DynamicGroupingMultiplicationNodeWithCtorParamsTests
	INSTANTIATE_TEST_CASE_P
	(
		DynamicGroupingMultiplicationNodeTests,
		DynamicGroupingMultiplicationNodeWithCtorParamsTests,
		testing::Values
		(
			DynamicGroupingMultiplicationNode_TestParams
			{
				.headMultiplicand{ "", "", "Head" },
				.tailMultiplicands{},
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.stringRepresentation{ "Head(Tail)" }
			},
			DynamicGroupingMultiplicationNode_TestParams
			{
				.headMultiplicand{ "", "", "Head" },
				.tailMultiplicands
				{
					CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>
						{ nullptr, "", "", "(Tail)" }
				},
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.stringRepresentation{ "Head(Tail)" }
			},
			DynamicGroupingMultiplicationNode_TestParams
			{
				.headMultiplicand{ "", "", "Head" },
				.tailMultiplicands
				{
					CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>
						{ nullptr, "", "", "(Tail1)" },
					CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>
						{ nullptr, "", "", "(Tail2)" },
					CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>
						{ nullptr, "", "", "(Tail3)" }
				},
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.stringRepresentation{ "Head(Tail1)(Tail2)(Tail3)" }
			},
			DynamicGroupingMultiplicationNode_TestParams
			{
				.headMultiplicand{ "", "", "Head" },
				.tailMultiplicands
				{
					CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>
						{ nullptr, "", "", "(Tail1)" },
					CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>
						{ nullptr, "", "", "(Tail2)" },
					CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>
						{ nullptr, "", "", "(Tail3)" }
				},
				.leadingTrivia{ " " },
				.trailingTrivia{ "  " },
				.stringRepresentation{ " Head(Tail1)(Tail2)(Tail3)  " }
			}
		)
	);
#pragma endregion


	TEST_P(DynamicGroupingMultiplicationNodeWithCtorParamsTests, DynamicGroupingMultiplicationNode$has$expected$state)
	{
		// Arrange
		auto headMultiplicandToPass
		{
			std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string>>
				(GetParam().headMultiplicand)
		};
		auto tailMultiplicandsView
		{
			GetParam().tailMultiplicands
			| std::views::transform
			(
				[](auto& tailMultiplicand)
				{
					return std::move
					(
						std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicGroupingNode<std::string>>
							(tailMultiplicand)
					);
				}
			)
		};
		std::ranges::owning_view<std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicGroupingNode<std::string>>>> tailMultiplicandsToPass
		{
			std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicGroupingNode<std::string>>>
			{
				tailMultiplicandsView.begin(),
				tailMultiplicandsView.end()
			}
		};
		const std::string leadingTriviaToPass{ GetParam().leadingTrivia };
		const std::string trailingTriviaToPass{ GetParam().trailingTrivia };

		const std::string expectedHeadMultiplicandStringRepresentation
		{
			GetParam().headMultiplicand.getStringRepresentation()
		};
		const auto expectedTailMultiplicandStringRepresentations
		{
			GetParam().tailMultiplicands
			| std::views::transform
			(
				[](auto& tailMultiplicand)
				{
					return tailMultiplicand.getStringRepresentation();
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