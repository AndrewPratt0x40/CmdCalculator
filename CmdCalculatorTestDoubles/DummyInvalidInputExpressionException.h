#pragma once

#include "../CmdCalculator/InvalidInputExpressionException.h"

namespace CmdCalculatorTestDoubles
{
	struct DummyInvalidInputExpressionException :
		public CmdCalculator::InvalidInputExpressionException
	{
	};
}