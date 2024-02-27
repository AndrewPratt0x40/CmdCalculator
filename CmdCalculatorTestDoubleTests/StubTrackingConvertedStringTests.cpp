#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/StubTrackingConvertedString.h""
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"
#include "../CmdCalculatorTestDoubles/StubExpression.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(StubTrackingConvertedStringTests, StubTrackingConvertedString$satisfies$String$concept)
	{
		static_assert
		(
			CmdCalculator::String
			<
				CmdCalculatorTestDoubles::StubTrackingConvertedString
				<
					std::string,
					CmdCalculatorTestDoubles::Expressions::StubExpression
					<
						CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
					>
				>
			>
		);
	}

#pragma endregion
}