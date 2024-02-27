#include "pch.h"

#include <string>

#include "../CmdCalculator/DynamicMathAstToDynamicExpressionConverter.h"
#include "../CmdCalculator/MathAstToExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicOperandToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingRecursiveSplitResultToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/FakeHalfwayDynamicExpressionPartRecursiveSplitter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"


namespace CmdCalculatorTests
{
#pragma region Concept satisfaction
	
	TEST(DynamicMathAstToDynamicExpressionConverterTests, DynamicMathAstToDynamicExpressionConverter$satisfies$MathAstToExpressionConverter$concept)
	{
		static_assert
		(
			CmdCalculator::MathAstToExpressionConverter
			<
				CmdCalculator::DynamicMathAstToDynamicExpressionConverter
				<
					CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartRecursiveSplitter
					<
						std::string
					>,
					CmdCalculatorTestDoubles::StubTrackingRecursiveSplitResultToDynamicExpressionConverter
					<
						CmdCalculatorTestDoubles::StubTrackingDynamicExpressionPartRecursiveSplitResult
						<
							std::ranges::subrange
							<
								std::ranges::iterator_t
								<
									CmdCalculator::MathAst::DynamicExpressionNodePartsView<std::string>
								>
							>,
							std::string
						>,
						CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
					>
				>
			>
		);
	}

#pragma endregion


#pragma region getMathAstAsExpression

	// getMathAstAsExpression$returns$the$result$of%recursively$

#pragma endregion
}