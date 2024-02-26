#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"
#include "../CmdCalculatorTestDoubles/StubExpression.h"
#include "../CmdCalculatorTestDoubles/StubExpressionToStringConverter.h"
#include "../CmdCalculator/ExpressionToStringConverter.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	template<::CmdCalculator::Expressions::Expression ExpressionT, ::CmdCalculator::String StringT>
	struct StubExpressionToStringConverter_TParams
	{
		using ExpressionType = ExpressionT;
		using StringType = StringT;
	};
	
	template<class T>
	class StubExpressionToStringConverterWithTParamsTests :
		public testing::Test
	{};

	using StubExpressionToStringConverterWithTParamsTests_Types = testing::Types
	<
		StubExpressionToStringConverter_TParams
		<
			CmdCalculatorTestDoubles::Expressions::StubExpression
			<
				CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
			>,
			std::string
		>
	>;

	TYPED_TEST_CASE(StubExpressionToStringConverterWithTParamsTests, StubExpressionToStringConverterWithTParamsTests_Types);


	TYPED_TEST(StubExpressionToStringConverterWithTParamsTests, StubExpressionToStringConverter$satisfies$ExpressionToStringConverter$concept)
	{
		static_assert
		(
			::CmdCalculator::ExpressionToStringConverter
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