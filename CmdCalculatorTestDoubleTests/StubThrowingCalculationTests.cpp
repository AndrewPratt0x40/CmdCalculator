#include "pch.h"

#include <string>
#include <string_view>
#include <utility>

#include "../CmdCalculatorTestDoubles/StubCalculation.h"
#include "../CmdCalculatorTestDoubles/StubThrowingCalculation.h"
#include "../CmdCalculatorTestDoubles/StubMathAstNode.h"
#include "../CmdCalculatorTestDoubles/StubExpression.h"
#include "../CmdCalculatorTestDoubles/StubStringToMathAstConverter.h"
#include "../CmdCalculatorTestDoubles/StubMathAstToExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubExpressionToStringConverter.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/Calculation.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	template<class T>
	class StubThrowingCalculationWithTParamsTests :
		public testing::Test
	{};

	using StubThrowingCalculationWithTParamsTests_Types = testing::Types
	<
		std::pair
		<
			CmdCalculatorTestDoubles::StubCalculation_TParams
			<
				std::string,
				std::string,
				CmdCalculatorTestDoubles::StubStringToMathAstConverter
				<
					std::string_view,
					CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>
				>,
				CmdCalculatorTestDoubles::StubMathAstToExpressionConverter
				<
					CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>,
					CmdCalculatorTestDoubles::Expressions::StubExpression
				>,
				CmdCalculatorTestDoubles::StubExpressionToStringConverter
				<
					CmdCalculatorTestDoubles::Expressions::StubExpression,
					std::string
				>
			>,
			int
		>
	>;

	TYPED_TEST_CASE(StubThrowingCalculationWithTParamsTests, StubThrowingCalculationWithTParamsTests_Types);

	TYPED_TEST(StubThrowingCalculationWithTParamsTests, StubThrowingCalculation$satisfies$Calculation$concept)
	{
		static_assert
		(
			CmdCalculator::Calculation
			<
				CmdCalculatorTestDoubles::StubThrowingCalculation
				<
					TypeParam::first_type,
					TypeParam::second_type
				>
			>
		);
	}

#pragma endregion
}