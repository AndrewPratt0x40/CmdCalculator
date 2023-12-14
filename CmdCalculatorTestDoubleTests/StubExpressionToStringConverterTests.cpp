#include "pch.h"

#include <string>
#include <string_view>
#include <initializer_list>
#include <ranges>
#include <algorithm>

#include "../CmdCalculator/NotImplementedException.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculatorTestDoubles/StubExpressionToStringConverter.h"

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	template<CmdCalculator::Expressions::Expression ExpressionT, CmdCalculator::String StringT>
	struct StubExpressionToStringConverter_TParams
	{
		using ExpressionType = ExpressionT;
		using StringType = StringT;
	};
	
	template<StubExpressionToStringConverter_TParams T>
	class StubExpressionToStringConverterWithTParamsTests :
		public testing::Test
	{};

	using StubExpressionToStringConverterWithTParamsTests_Types = testing::Types
	<
		StubExpressionToStringConverter_TParams<TODO, TODO>
	>;

	TYPED_TEST_CASE(StubExpressionToStringConverterWithTParamsTests, StubExpressionToStringConverterWithTParamsTests_Types);


	TYPED_TEST(StubExpressionToStringConverterWithTParamsTests, StubExpressionToStringConverterWithTParamsTests$ExpressionToStringConverter$concept)
	{
		EXPECT_TRUE
		(
			CmdCalculator::ExpressionToStringConverter
			<
				CmdCalculatorTestDoubles::StubExpressionToStringConverter
				<
					typename TypeParam::ExpressionType,
					typename TypeParam::StringType
				>
			>
		);
	}

#pragma endregion
}