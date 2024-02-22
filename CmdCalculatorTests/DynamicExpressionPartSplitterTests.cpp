#include "pch.h"

#include "../CmdCalculator/DynamicExpressionPartSingleSplitter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartSingleSplitResult.h"

#include <string>
#include <vector>
#include <optional>


namespace CmdCalculatorTests
{
#pragma region recursivelySplitExpressionParts
	
	struct recursivelySplitExpressionParts_TestData
	{
		std::vector<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>> parts;
		std::optional<CmdCalculatorTestDoubles::StubDynamicExpressionPartSingleSplitResult<std::string>> expected;
	};
	
	TEST(recursivelySplitExpressionPartsTests, recursivelySplitExpressionParts$returns$recursive$calls$to$trySplit)
	{
		FAIL();
	}

#pragma endregion
}