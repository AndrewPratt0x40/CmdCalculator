#pragma once

#include <functional>
#include <memory>

#include "../CmdCalculator/StringToAntlrContextConverter.h"
#include "../CmdCalculator/FullExpressionAntlrContext.h"
#include "StubTrackingFullExpressionAntlrContext.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::StringView StringViewT, class ExceptionT>
	struct StubThrowingStringToAntlrContextConverter :
		public CmdCalculator::StringToAntlrContextConverter_IntendedSatisfaction
	{
	public:
		using StringViewType = StringViewT;
		using ExceptionType = ExceptionT;
		using FullExpressionAntlrContexType = StubTrackingFullExpressionAntlrContext<StringViewType>;

		ExceptionType exceptionToThrow;


		FullExpressionAntlrContexType getStringAsAntlrContext(StringViewT source) const
		{
			throw exceptionToThrow;
		}
	};
}