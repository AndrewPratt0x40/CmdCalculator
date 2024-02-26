#pragma once

#include "../CmdCalculator/AntlrToken.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles
{
	template<::CmdCalculator::String StringT>
	struct StubAntlrToken :
		public ::CmdCalculator::AntlrToken_IntendedSatisfaction
	{
		using StringType = StringT;

		StringType text;
		size_t startIndex;
		size_t stopIndex;


		StringType getText() const
		{
			return text;
		}


		size_t getStartIndex() const
		{
			return startIndex;
		}


		size_t getStopIndex() const
		{
			return stopIndex;
		}
	};
}