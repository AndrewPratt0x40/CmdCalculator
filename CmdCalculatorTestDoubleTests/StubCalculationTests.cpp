#include "pch.h"

#include <string>
#include <string_view>

#include "../CmdCalculatorTestDoubles/StubCalculation.h"
#include "../CmdCalculatorTestDoubles/StubMathAstNode.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"
#include "../CmdCalculatorTestDoubles/StubExpression.h"
#include "../CmdCalculatorTestDoubles/StubStringToMathAstConverter.h"
#include "../CmdCalculatorTestDoubles/StubMathAstToExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubExpressionToStringConverter.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/Calculation.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	struct OutputExpressionProviderForStubCalculation
	{
		using OutputExpressionType = std::string;

		static std::string getOutputExpression()
		{
			return {};
		}
	};

	
	template<class T>
	class StubCalculationWithTParamsTests :
		public testing::Test
	{};

	using StubCalculationWithTParamsTests_Types = testing::Types
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
				CmdCalculatorTestDoubles::Expressions::StubExpression<CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber>
			>,
			CmdCalculatorTestDoubles::StubExpressionToStringConverter
			<
				CmdCalculatorTestDoubles::Expressions::StubExpression<CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber>,
				std::string
			>
		>
	>;

	TYPED_TEST_CASE(StubCalculationWithTParamsTests, StubCalculationWithTParamsTests_Types);

	TYPED_TEST(StubCalculationWithTParamsTests, StubCalculation$satisfies$Calculation$concept)
	{
		static_assert
		(
			::CmdCalculator::Calculation<CmdCalculatorTestDoubles::StubCalculation<TypeParam, OutputExpressionProviderForStubCalculation>>
		);
	}

#pragma endregion
}