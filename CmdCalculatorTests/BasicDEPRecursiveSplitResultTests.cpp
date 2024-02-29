#include "pch.h"

#include "../CmdCalculator/BasicDEPRecursiveSplitResult.h"
#include "../CmdCalculator/DynamicExpressionPartRecursiveSplitResult.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <functional>


namespace CmdCalculatorTests
{
#pragma region Concept satisfaction
	
	TEST(BasicDEPRecursiveSplitResultTests, BasicDEPRecursiveSplitResult$satisfies$the$DynamicExpressionPartRecursiveSplitResult$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicExpressionPartRecursiveSplitResult
			<
				CmdCalculator::BasicDEPRecursiveSplitResult<std::string>
			>
		);
	}

#pragma endregion


#pragma region Expected state
	
	struct BasicDEPRecursiveSplitResult_TestData
	{
		bool useNullLeftPart;
		bool useNullRightPart;
	};

	class BasicDEPRecursiveSplitResultWithParamsTests :
		public testing::TestWithParam<BasicDEPRecursiveSplitResult_TestData>
	{};

	const BasicDEPRecursiveSplitResult_TestData BasicDEPRecursiveSplitResult_TestDataValues[]
	{
		{ false, false },
		{ false, true },
		{ true, false },
		{ true, true }
	};

	INSTANTIATE_TEST_CASE_P
	(
		BasicDEPRecursiveSplitResultTests,
		BasicDEPRecursiveSplitResultWithParamsTests,
		testing::ValuesIn(BasicDEPRecursiveSplitResult_TestDataValues)
	);


	TEST_P(BasicDEPRecursiveSplitResultWithParamsTests, BasicDEPRecursiveSplitResult$has$expected$state)
	{
		// Arrange
		using ExpressionPartType = CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>;

		const auto makeSplitPartOfSidePart
		{
			[](const bool isEmpty, const std::string& partAsStr)
			{
				return isEmpty
					? std::optional<ExpressionPartType>{}
					: std::make_optional<ExpressionPartType>
					(
						false, "", "", partAsStr
					)
				;
			}
		};

		const auto makeSidePart
		{
			[](const std::optional<ExpressionPartType>& sidePart)
			{
				return sidePart.has_value()
					? std::make_unique<CmdCalculator::BasicDEPRecursiveSplitResult<std::string>>
					(
						std::unique_ptr<CmdCalculator::BasicDEPRecursiveSplitResult<std::string>>{},
						sidePart.value(),
						std::unique_ptr<CmdCalculator::BasicDEPRecursiveSplitResult<std::string>>{}
					)
					: std::unique_ptr<CmdCalculator::BasicDEPRecursiveSplitResult<std::string>>{}
				;
			}
		};

		const std::string splitPartOfLeftPartStr{ "Left's split part" };
		const std::string splitPartStr{ "Split part" };
		const std::string splitPartOfRightPartStr{ "Right's split part" };

		const bool shouldInstanceHaveNullLeftPart{ GetParam().useNullLeftPart };
		const bool shouldInstanceHaveNullRightPart{ GetParam().useNullRightPart };

		std::optional<ExpressionPartType> splitPartOfLeftPart{ makeSplitPartOfSidePart(shouldInstanceHaveNullLeftPart, splitPartOfLeftPartStr) };
		ExpressionPartType splitPart{ false, "", "", splitPartStr };
		std::optional<ExpressionPartType> splitPartOfRightPart{ makeSplitPartOfSidePart(shouldInstanceHaveNullRightPart, splitPartOfRightPartStr) };

		ASSERT_EQ(shouldInstanceHaveNullLeftPart, !splitPartOfLeftPart.has_value());
		ASSERT_EQ(shouldInstanceHaveNullRightPart, !splitPartOfRightPart.has_value());

		std::unique_ptr<CmdCalculator::BasicDEPRecursiveSplitResult<std::string>> leftPartToPass{ makeSidePart(splitPartOfLeftPart) };
		std::unique_ptr<CmdCalculator::BasicDEPRecursiveSplitResult<std::string>> rightPartToPass{ makeSidePart(splitPartOfRightPart) };

		ASSERT_EQ(shouldInstanceHaveNullLeftPart, leftPartToPass.get() == nullptr);
		ASSERT_EQ(shouldInstanceHaveNullRightPart, rightPartToPass.get() == nullptr);

		// Act
		const CmdCalculator::BasicDEPRecursiveSplitResult<std::string> instance
		{
			std::move(leftPartToPass),
			splitPart,
			std::move(rightPartToPass)
		};

		// Assert
		if (shouldInstanceHaveNullLeftPart)
			EXPECT_FALSE(instance.getLeftPart());
		else
		{
			ASSERT_TRUE(instance.getLeftPart());
			EXPECT_EQ(splitPartOfLeftPartStr, instance.getLeftPart()->getSplitPart().getStringRepresentation());
		}

		EXPECT_EQ(&splitPart, &instance.getSplitPart());

		if (shouldInstanceHaveNullRightPart)
			EXPECT_FALSE(instance.getRightPart());
		else
		{
			ASSERT_TRUE(instance.getRightPart());
			EXPECT_EQ(splitPartOfRightPartStr, instance.getRightPart()->getSplitPart().getStringRepresentation());
		}
	}

#pragma endregion
}