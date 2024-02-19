#include "pch.h"

#include <string>
#include <memory>
#include <ranges>

#include "../CmdCalculator/DynamicExpressionNode.h"
#include "../CmdCalculator/ExpressionNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"


namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(DynamicExpressionNodeTests, DynamicExpressionNode$satisfies$ExpressionNode$concept)
	{
		static_assert
		(
			CmdCalculator::MathAst::ExpressionNode<CmdCalculator::MathAst::DynamicExpressionNode<std::string>>
		);
	}

#pragma endregion


#pragma region State

	struct DynamicExpressionNode_TestParams
	{
		std::string leadingTrivia;
		std::string trailingTrivia;
		std::vector<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>> parts;
		std::string stringRepresentation;
	};

	class DynamicExpressionNodeWithCtorParamsTests :
		public testing::TestWithParam<DynamicExpressionNode_TestParams>
	{};

#pragma region Instantiate DynamicExpressionNodeWithCtorParamsTests
	INSTANTIATE_TEST_CASE_P
	(
		DynamicExpressionNodeTests,
		DynamicExpressionNodeWithCtorParamsTests,
		testing::Values
		(
			DynamicExpressionNode_TestParams
			{
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.parts{},
				.stringRepresentation{ "" }
			},
			DynamicExpressionNode_TestParams
			{
				.leadingTrivia{ " " },
				.trailingTrivia{ "  " },
				.parts{},
				.stringRepresentation{ "   " }
			},
			DynamicExpressionNode_TestParams
			{
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.parts
				{
					CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
						{ false, "", "", "Part" }
				},
				.stringRepresentation{ "Part" }
			},
			DynamicExpressionNode_TestParams
			{
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.parts
				{
					CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
						{  false, "", "", "<Part1>" },
					CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
						{  false, "", "", "<Part2>" },
					CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
						{  false, "", "", "<Part3>" }
				},
				.stringRepresentation{ "<Part1><Part2><Part3>" }
			},
			DynamicExpressionNode_TestParams
			{
				.leadingTrivia{ " " },
				.trailingTrivia{ "  " },
				.parts
				{
					CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
						{ false,  "", "", "<Part1>" },
					CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
						{  false, "", "", "<Part2>" },
					CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
						{  false, "", "", "<Part3>" }
				},
				.stringRepresentation{ " <Part1><Part2><Part3>  " }
			}
		)
	);
#pragma endregion

	TEST_P(DynamicExpressionNodeWithCtorParamsTests, DynamicExpressionNode$has$expected$state)
	{
		// Arrange
		const std::string leadingTriviaToPass{ GetParam().leadingTrivia };
		const std::string trailingTriviaToPass{ GetParam().trailingTrivia };
		auto partsView
		{
			GetParam().parts
			| std::views::transform
			(
				[](auto& part)
				{
					return std::move
					(
						std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>>
							(part)
					);
				}
			)
		};
		std::ranges::owning_view<std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>>> partsToPass
		{
			std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>>
			{
				partsView.begin(),
				partsView.end()
			}
		};

		const std::string expectedLeadingTrivia{ GetParam().leadingTrivia };
		const std::string expectedTrailingTrivia{ GetParam().trailingTrivia };
		const auto expectedPartStringRepresentations
		{
			GetParam().parts
			| std::views::transform
			(
				[](auto& part)
				{
					return part.getStringRepresentation();
				}
			)
		};
		const std::string expectedStringRepresentation{ GetParam().stringRepresentation };

		// Act
		CmdCalculator::MathAst::DynamicExpressionNode<std::string> instance
		{
			leadingTriviaToPass,
			trailingTriviaToPass,
			std::move(partsToPass)
		};

		// Assert
		EXPECT_EQ(expectedLeadingTrivia, instance.getLeadingTrivia());
		EXPECT_EQ(expectedTrailingTrivia, instance.getTrailingTrivia());
		EXPECT_TRUE
		(
			std::ranges::equal
			(
				expectedPartStringRepresentations,
				instance.getParts()
				| std::views::transform
				(
					[](auto* part)
					{
						return part->getStringRepresentation();
					}
				)
			)
		);
		EXPECT_EQ(expectedStringRepresentation, instance.getStringRepresentation());
	}

#pragma endregion
}