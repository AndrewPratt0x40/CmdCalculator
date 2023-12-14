#include "pch.h"

#include <string>
#include <initializer_list>
#include <ranges>
#include <algorithm>

#include "../CmdCalculatorTestDoubles/StubExpression.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	template<std::regular T>
	class StubExpressionWithTParamTests :
		public testing::Test
	{};

	using StubExpressionWithTParamTests_Types = testing::Types
	<
		int,
		char,
		bool,
		std::string
	>;

	TYPED_TEST_CASE(StubExpressionWithTParamTests, StubExpressionWithTParamTests_Types);
	

	TYPED_TEST(StubExpressionWithTParamTests, StubExpression$satisfies$Expression$concept)
	{
		// Arrange
		const bool isConceptSatisfied
		{
			CmdCalculator::Expressions::Expression<CmdCalculatorTestDoubles::Expressions::StubExpression<typename TypeParam>>
		};
		
		// Assert
		EXPECT_TRUE(isConceptSatisfied);
	}

#pragma endregion
}