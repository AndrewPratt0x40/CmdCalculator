#include "pch.h"

#include <string>

#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(FakeRealNumberTests, FakeRealNumber$satisfies$RealNumber$concept)
	{
		static_assert
		(
			CmdCalculator::Arithmetic::RealNumber<CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber>
		);
	}

#pragma endregion
}