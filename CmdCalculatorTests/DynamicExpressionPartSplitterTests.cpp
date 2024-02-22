#include "pch.h"

#include "../CmdCalculator/DynamicExpressionPartSplitter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartSplitResult.h"

#include <string>
#include <vector>
#include <optional>


namespace CmdCalculatorTests
{
#pragma region recursivelySplitExpressionParts
	
	struct recursivelySplitExpressionParts_TestData
	{
		std::vector<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>> parts;
		std::optional<CmdCalculatorTestDoubles::StubDynamicExpressionPartSplitResult<std::string>> expected;
	};
	
	TEST(recursivelySplitExpressionPartsTests, recursivelySplitExpressionParts$returns$recursive$calls$to$trySplit)
	{
		FAIL();
	}

#pragma endregion
}