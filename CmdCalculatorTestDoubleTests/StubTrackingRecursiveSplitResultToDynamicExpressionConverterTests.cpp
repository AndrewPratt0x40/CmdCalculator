#include "pch.h"

#include <string>
#include <ranges>

#include "../CmdCalculator/RecursiveSplitResultToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingRecursiveSplitResultToDynamicExpressionConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingDynamicExpressionPartRecursiveSplitResult.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingRecursiveSplitResultToDynamicExpressionConverterTestsTests, StubTrackingRecursiveSplitResultToDynamicExpressionConverterTests$satisfies$RecursiveSplitResultToDynamicExpressionConverter$concept)
	{
		static_assert
		(
			CmdCalculator::RecursiveSplitResultToDynamicExpressionConverter
			<
				CmdCalculatorTestDoubles::StubTrackingRecursiveSplitResultToDynamicExpressionConverter
				<
					CmdCalculatorTestDoubles::StubTrackingDynamicExpressionPartRecursiveSplitResult
					<
						std::ranges::empty_view
						<
							std::reference_wrapper<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>
						>,
						std::string
					>,
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion
}