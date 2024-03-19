#include "pch.h"

#include <string>
#include <memory>
#include <span>

#include "../CmdCalculator/DynamicNumberLiteralNode.h"

namespace CmdCalculatorTestDoubleTests
{
	struct DynamicNumberLiteralNode_TestParams
	{
		std::optional<std::string> wholePart;
		std::optional<std::string> fractionalPart;
		bool isDecimalPointVisible;
		std::string leadingTrivia;
		std::string trailingTrivia;
		bool expectWholePartVisible;
		bool expectDecimalPointVisible;
		bool expectFractionalPartVisible;
		std::string stringRepresentation;


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const DynamicNumberLiteralNode_TestParams& testData
		)
		{
			ostream
				<< "DynamicNumberLiteralNode{wholePart{"
				<< testData.wholePart.value_or("")
				<< "}, fractionalPart{"
				<< testData.fractionalPart.value_or("")
				<< "}, isDecimalPointVisible{"
				<< testData.isDecimalPointVisible
				<< "}, leadingTrivia{"
				<< testData.leadingTrivia
				<< "}, trailingTrivia{"
				<< testData.trailingTrivia
				<< "}} -> {isWholePartVisible{"
				<< testData.expectWholePartVisible
				<< "}, isDecimalPointVisible{"
				<< testData.expectDecimalPointVisible
				<< "}, isFractionalPartVisible"
				<< testData.expectFractionalPartVisible
				<< "}, {stringRepresentation{"
				<< testData.stringRepresentation
				<< "}}"
			;

			return ostream;
		}
	};

	class DynamicNumberLiteralNodeWithCtorParamsTests :
		public testing::TestWithParam<DynamicNumberLiteralNode_TestParams>
	{};

	const DynamicNumberLiteralNode_TestParams DynamicNumberLiteralNode_TestParamsValues[]
	{
		{
			.wholePart{ std::make_optional<std::string>("0") },
			.fractionalPart{  std::make_optional<std::string>("0") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "0.0" }
		},
		{
			.wholePart{ std::make_optional<std::string>("0") },
			.fractionalPart{  std::make_optional<std::string>("1") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "0.1" }
		},
		{
			.wholePart{ std::make_optional<std::string>("0") },
			.fractionalPart{  std::make_optional<std::string>("123") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "0.123" }
		},
		{
			.wholePart{ std::make_optional<std::string>("0") },
			.fractionalPart{  std::make_optional<std::string>("00123000") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "0.00123000" }
		},
		{
			.wholePart{ std::make_optional<std::string>("1") },
			.fractionalPart{  std::make_optional<std::string>("0") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "1.0" }
		},
		{
			.wholePart{ std::make_optional<std::string>("1") },
			.fractionalPart{  std::make_optional<std::string>("1") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "1.1" }
		},
		{
			.wholePart{ std::make_optional<std::string>("1") },
			.fractionalPart{  std::make_optional<std::string>("123") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "1.123" }
		},
		{
			.wholePart{ std::make_optional<std::string>("1") },
			.fractionalPart{  std::make_optional<std::string>("00123000") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "1.00123000" }
		},
		{
			.wholePart{ std::make_optional<std::string>("123") },
			.fractionalPart{  std::make_optional<std::string>("0") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "123.0" }
		},
		{
			.wholePart{ std::make_optional<std::string>("123") },
			.fractionalPart{  std::make_optional<std::string>("1") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "123.1" }
		},
		{
			.wholePart{ std::make_optional<std::string>("123") },
			.fractionalPart{  std::make_optional<std::string>("123") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "123.123" }
		},
		{
			.wholePart{ std::make_optional<std::string>("123") },
			.fractionalPart{  std::make_optional<std::string>("00123000") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "123.00123000" }
		},
		{
			.wholePart{ std::make_optional<std::string>("00123000") },
			.fractionalPart{  std::make_optional<std::string>("0") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "00123000.0" }
		},
		{
			.wholePart{ std::make_optional<std::string>("00123000") },
			.fractionalPart{  std::make_optional<std::string>("1") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "00123000.1" }
		},
		{
			.wholePart{ std::make_optional<std::string>("00123000") },
			.fractionalPart{  std::make_optional<std::string>("123") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "00123000.123" }
		},
		{
			.wholePart{ std::make_optional<std::string>("00123000") },
			.fractionalPart{  std::make_optional<std::string>("00123000") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ "00123000.00123000" }
		},
		{
			.wholePart{},
			.fractionalPart{  std::make_optional<std::string>("123") },
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ false },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ true },
			.stringRepresentation{ ".123" }
		},
		{
			.wholePart{ std::make_optional<std::string>("123") },
			.fractionalPart{},
			.isDecimalPointVisible{ true },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ true },
			.expectFractionalPartVisible{ false },
			.stringRepresentation{ "123." }
		},
		{
			.wholePart{ std::make_optional<std::string>("123") },
			.fractionalPart{},
			.isDecimalPointVisible{ false },
			.leadingTrivia{ "" },
			.trailingTrivia{ "" },
			.expectWholePartVisible{ true },
			.expectDecimalPointVisible{ false },
			.expectFractionalPartVisible{ false },
			.stringRepresentation{ "123" }
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
		const std::optional<std::string> wholePartToPass{ GetParam().wholePart };
		const std::optional<std::string> fractionalPartToPass{ GetParam().fractionalPart };
		const bool isDecimalPointVisibleToPass{ GetParam().isDecimalPointVisible };
		const std::string leadingTriviaToPass{ GetParam().leadingTrivia };
		const std::string trailingTriviaToPass{ GetParam().trailingTrivia };

		const std::optional<std::string> expectedWholePart{ GetParam().wholePart };
		const std::optional<std::string> expectedFractionalPart{ GetParam().fractionalPart };
		const bool expectedIsWholePartVisible{ GetParam().expectWholePartVisible };
		const bool expectedIsDecimalPointVisible{ GetParam().expectDecimalPointVisible };
		const bool expectedIsFractionalPartVisible{ GetParam().expectFractionalPartVisible };
		const std::string expectedLeadingTrivia{ GetParam().leadingTrivia };
		const std::string expectedTrailingTrivia{ GetParam().trailingTrivia };
		const std::string expectedStringRepresentation{ GetParam().stringRepresentation };
		
		// Act
		CmdCalculator::MathAst::DynamicNumberLiteralNode<std::string> instance
		{
			wholePartToPass,
			fractionalPartToPass,
			isDecimalPointVisibleToPass,
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