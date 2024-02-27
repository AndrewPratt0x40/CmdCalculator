#include "pch.h"

#include <string>
#include <string_view>

#include "../CmdCalculatorTestDoubles/StubDynamicOperandNode.h"
#include "../CmdCalculator/ExpressionPartNode.h"
#include "../CmdCalculator/dynamic_mathast.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubDynamicOperandNodeTests, DynamicOperandNode$satisfies$ExpressionPartNode$concept)
	{
		static_assert
		(
			CmdCalculator::MathAst::ExpressionPartNode
			<
				CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string>
			>
		);
	}

#pragma endregion
}