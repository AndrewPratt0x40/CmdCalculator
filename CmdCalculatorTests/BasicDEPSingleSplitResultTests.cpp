#include "pch.h"

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/BasicDEPSingleSplitResult.h"
#include "../CmdCalculator/DynamicExpressionPartSingleSplitResult.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <functional>


namespace CmdCalculatorTests
{
#pragma region Concept satisfaction
	
	TEST(BasicDEPSingleSplitResultTests, BasicDEPSingleSplitResult$satisfies$the$DynamicExpressionPartSingleSplitResult$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicExpressionPartSingleSplitResult
			<
				CmdCalculator::BasicDEPSingleSplitResult<std::string>
			>
		);
	}

#pragma endregion


#pragma region Expected state

	struct BasicDEPSingleSplitResult_TestData
	{
		std::vector<std::string> leftParts;
		std::string splitPart;
		std::vector<std::string> rightParts;
		
		
		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const BasicDEPSingleSplitResult_TestData& testData
		)
		{
			ostream
				<< "BasicDEPSingleSplitResult{"
				<< CmdCalculatorTestUtils::joinStrings(testData.leftParts)
				<< '<'
				<< testData.splitPart
				<< '>'
				<< CmdCalculatorTestUtils::joinStrings(testData.rightParts)
				<< '}'
			;

			return ostream;
		}
	};

	class BasicDEPSingleSplitResultWithParamsTests :
		public testing::TestWithParam<BasicDEPSingleSplitResult_TestData>
	{};

	const BasicDEPSingleSplitResult_TestData BasicDEPSingleSplitResult_TestDataValues[]
	{
		{
			.leftParts{},
			.splitPart{ "SplitPart" },
			.rightParts{}
		},
		{
			.leftParts{},
			.splitPart{ "SplitPart" },
			.rightParts{ "RightPart1", "RightPart2", "RightPart3" }
		},
		{
			.leftParts{ "LeftPart1", "LeftPart2", "LeftPart3" },
			.splitPart{ "SplitPart" },
			.rightParts{}
		},
		{
			.leftParts{ "LeftPart1", "LeftPart2", "LeftPart3" },
			.splitPart{ "SplitPart" },
			.rightParts{ "RightPart1", "RightPart2", "RightPart3" }
		}
	};

	INSTANTIATE_TEST_CASE_P
	(
		BasicDEPSingleSplitResultTests,
		BasicDEPSingleSplitResultWithParamsTests,
		testing::ValuesIn(BasicDEPSingleSplitResult_TestDataValues)
	);

	TEST_P(BasicDEPSingleSplitResultWithParamsTests, BasicDEPSingleSplitResult$has$expected$state)
	{
		// Arrange
		using StubPartNodeType = CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>;

		const auto makeParts
		{
			[](const std::vector<std::string>& partStrs)
			{
				return CmdCalculatorTestUtils::moveRangeToVector
				(
					partStrs
					| std::views::transform
					(
						[](const std::string& partStr)
						{
							return StubPartNodeType{ false, "", "", partStr };
						}
					)
				);
			}
		};

		const std::vector<std::string>& expectedLeftParts{ GetParam().leftParts };
		const std::string expectedSplitPart{ GetParam().splitPart };
		const std::vector<std::string>& expectedRightParts{ GetParam().rightParts };

		const std::vector<StubPartNodeType> leftPartsToPass
		{
			makeParts(GetParam().leftParts)
		};
		const StubPartNodeType splitPartToPass{ false, "", "", GetParam().splitPart };
		const std::vector<StubPartNodeType> rightPartsToPass
		{
			makeParts(GetParam().rightParts)
		};

		// Act
		const CmdCalculator::BasicDEPSingleSplitResult<std::string> instance
		{
			leftPartsToPass | std::views::all,
			splitPartToPass,
			rightPartsToPass | std::views::all
		};

		// Assert
		const auto partsAsStrs
		{
			[](CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto parts)
			{
				return
					parts
					| std::views::transform
					(
						[](const CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>& part)
						{ return part.getStringRepresentation(); }
					)
				;
			}
		};

		EXPECT_TRUE
		(
			std::ranges::equal
			(
				expectedLeftParts,
				partsAsStrs(instance.getLeftParts())
			)
		);
		EXPECT_EQ(expectedSplitPart, instance.getSplitPart().getStringRepresentation());
		EXPECT_TRUE
		(
			std::ranges::equal
			(
				expectedRightParts,
				partsAsStrs(instance.getRightParts())
			)
		);
	}

#pragma endregion
}