#include "pch.h"

#include <concepts>
#include <optional>
#include <memory>
#include <utility>
#include <string>
#include <string_view>
#include <vector>
#include <span>

#include "common.h"
#include "..\CmdCalculator\NotImplementedException.h"
#include "..\CmdCalculator\utilities.h"

namespace CmdCalculatorTests
{
#pragma region Optional

	template<class OptionalT, bool shouldSatisfyT>
	struct Optional_TypeParams
	{
		using OptionalType = OptionalT;
		static constexpr bool shouldSatisfy{ shouldSatisfyT };
	};
	
	template<class T>
	class OptionalTests :
		public testing::Test
	{};

	using OptionalTests_Types = testing::Types
	<
		Optional_TypeParams<int, false>,
		Optional_TypeParams<int*, false>,
		Optional_TypeParams<std::string, false>,
		Optional_TypeParams<std::optional<int>, true>,
		Optional_TypeParams<std::optional<int*>, true>,
		Optional_TypeParams<std::optional<std::string>, true>,
		Optional_TypeParams<std::optional<std::optional<int>>, true>
	>;

	TYPED_TEST_CASE(OptionalTests, OptionalTests_Types);


	TYPED_TEST(OptionalTests, Only$expected$types$satisfy)
	{
		// Arrange
		const bool expectSatisfaction{ TypeParam::shouldSatisfy };
		const bool isSatisfactory{ CmdCalculator::Optional<TypeParam::OptionalType> };

		// Assert
		EXPECT_EQ(expectSatisfaction, isSatisfactory);
	}

#pragma endregion
}