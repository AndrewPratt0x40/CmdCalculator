#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubMathAstNode.h"
#include "../CmdCalculatorTestDoubles/StubExpression.h"
#include "../CmdCalculatorTestDoubles/StubMathAstToExpressionConverter.h"
#include "../CmdCalculator/MathAstToExpressionConverter.h"
#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/Expression.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	template<CmdCalculator::MathAst::MathAstNode RootMathAstNodeT, CmdCalculator::Expressions::Expression ExpressionT>
	struct StubMathAstToExpressionConverter_TParams
	{
		using RootMathAstNodeType = RootMathAstNodeT;
		using ExpressionType = ExpressionT;
	};

	template<class T>
	class StubMathAstToExpressionConverterWithTParamsTests :
		public testing::Test
	{};

	using StubMathAstToExpressionConverterWithTParamsTests_Types = testing::Types
	<
		StubMathAstToExpressionConverter_TParams<CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>, CmdCalculatorTestDoubles::Expressions::StubExpression>
	>;

	TYPED_TEST_CASE(StubMathAstToExpressionConverterWithTParamsTests, StubMathAstToExpressionConverterWithTParamsTests_Types);


	TYPED_TEST(StubMathAstToExpressionConverterWithTParamsTests, StubMathAstToExpressionConverter$satisfies$MathAstToExpressionConverter$concept)
	{
		static_assert
		(
			CmdCalculator::MathAstToExpressionConverter
			<
				CmdCalculatorTestDoubles::StubMathAstToExpressionConverter
				<
					typename TypeParam::RootMathAstNodeType,
					typename TypeParam::ExpressionType
				>,
				typename TypeParam::RootMathAstNodeType
			>
		);
	}

#pragma endregion
}