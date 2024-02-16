#include "pch.h"

#include "../CmdCalculator/DynamicMathAstToDynamicExpressionConverter.h"
#include "../CmdCalculator/MathAstToExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubFullExpressionAntlrContext.h"

#include <algorithm>
#include <string>
#include <string_view>
#include <ranges>
#include <concepts>
#include <assert.h>
#include <vector>
#include <optional>


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
					TODO
				>
			>
		);
	}

#pragma endregion
}