#include "pch.h"

#include <string>
#include <memory>
#include <span>

#include "../CmdCalculator/DynamicNumberLiteralNode.h"

namespace CmdCalculatorTestDoubleTests
{
	struct DynamicNumberLiteralNode_TestParams
	{
		int wholePart;
		float fractionalPart;
		CmdCalculator::MathAst::EDynamicNumberLiteralNodePartsConfig partsConfig;
		std::string leadingTrivia;
		std::string trailingTrivia;
		bool expectWholePartVisible;
		bool expectDecimalPointVisible;
		bool expectFractionalPartVisible;
		std::string stringRepresentation;
	};

	class DynamicNumberLiteralNodeWithCtorParamsTests :
		public testing::TestWithParam<DynamicNumberLiteralNode_TestParams>
	{};

	const DynamicNumberLiteralNode_TestParams DynamicNumberLiteralNode_TestParamsValues[]
	{
		DynamicNumberLiteralNode_TestParams
			{
				.wholePart{ 1 },
				.fractionalPart{ 0.2 },
				.partsConfig{ CmdCalculator::MathAst::EDynamicNumberLiteralNodePartsConfig::FullDecimal },
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.expectWholePartVisible{ true },
				.expectDecimalPointVisible{ true },
				.expectFractionalPartVisible{ true },
				.stringRepresentation{ "1.2" }
			},
			DynamicNumberLiteralNode_TestParams
			{
				.wholePart{ 1234 },
				.fractionalPart{ 0.5678 },
				.partsConfig{ CmdCalculator::MathAst::EDynamicNumberLiteralNodePartsConfig::FullDecimal },
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.expectWholePartVisible{ true },
				.expectDecimalPointVisible{ true },
				.expectFractionalPartVisible{ true },
				.stringRepresentation{ "1234.5678" }
			},
			DynamicNumberLiteralNode_TestParams
			{
				.wholePart{ 1 },
				.fractionalPart{ 0.2 },
				.partsConfig{ CmdCalculator::MathAst::EDynamicNumberLiteralNodePartsConfig::Integer },
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.expectWholePartVisible{ true },
				.expectDecimalPointVisible{ false },
				.expectFractionalPartVisible{ false },
				.stringRepresentation{ "1" }
			},
			DynamicNumberLiteralNode_TestParams
			{
				.wholePart{ 1 },
				.fractionalPart{ 0.2 },
				.partsConfig{ CmdCalculator::MathAst::EDynamicNumberLiteralNodePartsConfig::WholelessDecimal },
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.expectWholePartVisible{ false },
				.expectDecimalPointVisible{ true },
				.expectFractionalPartVisible{ true },
				.stringRepresentation{ ".2" }
			},
			DynamicNumberLiteralNode_TestParams
			{
				.wholePart{ 1 },
				.fractionalPart{ 0.2 },
				.partsConfig{ CmdCalculator::MathAst::EDynamicNumberLiteralNodePartsConfig::FractionlessDecimal },
				.leadingTrivia{ "" },
				.trailingTrivia{ "" },
				.expectWholePartVisible{ true },
				.expectDecimalPointVisible{ true },
				.expectFractionalPartVisible{ false },
				.stringRepresentation{ "1." }
			},
			DynamicNumberLiteralNode_TestParams
			{
				.wholePart{ 1 },
				.fractionalPart{ 0.2 },
				.partsConfig{ CmdCalculator::MathAst::EDynamicNumberLiteralNodePartsConfig::FullDecimal },
				.leadingTrivia{ " " },
				.trailingTrivia{ "  " },
				.expectWholePartVisible{ true },
				.expectDecimalPointVisible{ true },
				.expectFractionalPartVisible{ true },
				.stringRepresentation{ " 1.2  " }
			}
	};


#pragma region Instantiate DynamicNumberLiteralNodeWithCtorParamsTests
	INSTANTIATE_TEST_CASE_P
	(
		DynamicNumberLiteralNodeTests,
		DynamicNumberLiteralNodeWithCtorParamsTests,
		testing::ValuesIn(DynamicNumberLiteralNode_TestParamsValues)
	);
#pragma endregion


	TEST_P(DynamicNumberLiteralNodeWithCtorParamsTests, DynamicNumberLiteralNode$has$expected$state)
	{
		// Arrange
		const int wholePartToPass{ GetParam().wholePart };
		const float fractionalPartToPass{ GetParam().fractionalPart };
		const CmdCalculator::MathAst::EDynamicNumberLiteralNodePartsConfig partsConfigToPass{ GetParam().partsConfig };
		const std::string leadingTriviaToPass{ GetParam().leadingTrivia };
		const std::string trailingTriviaToPass{ GetParam().trailingTrivia };

		const int expectedWholePart{ GetParam().wholePart };
		const float expectedFractionalPart{ GetParam().fractionalPart };
		const bool expectedIsWholePartVisible{ GetParam().expectWholePartVisible };
		const bool expectedIsDecimalPointVisible{ GetParam().expectDecimalPointVisible };
		const bool expectedIsFractionalPartVisible{ GetParam().expectFractionalPartVisible };
		const std::string expectedLeadingTrivia{ GetParam().leadingTrivia };
		const std::string expectedTrailingTrivia{ GetParam().trailingTrivia };
		const std::string expectedStringRepresentation{ GetParam().stringRepresentation };
		
		// Act
		CmdCalculator::MathAst::DynamicNumberLiteralNode<std::string, int, float> instance
		{
			wholePartToPass,
			fractionalPartToPass,
			partsConfigToPass,
			leadingTriviaToPass,
			trailingTriviaToPass
		};

		// Assert
		EXPECT_EQ(expectedWholePart, instance.getWholePart());
		EXPECT_EQ(expectedFractionalPart, instance.getFractionalPart());
		EXPECT_EQ(expectedIsWholePartVisible, instance.isWholePartVisible());
		EXPECT_EQ(expectedIsDecimalPointVisible, instance.isDecimalPointVisible());
		EXPECT_EQ(expectedIsFractionalPartVisible, instance.isFractionalPartVisible());
		EXPECT_EQ(expectedLeadingTrivia, instance.getLeadingTrivia());
		EXPECT_EQ(expectedTrailingTrivia, instance.getTrailingTrivia());
		EXPECT_EQ(expectedStringRepresentation, instance.getStringRepresentation());
	}
}