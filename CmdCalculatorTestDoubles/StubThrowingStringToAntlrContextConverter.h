#pragma once

#include <exception>#include "../CmdCalculator/StringToAntlrContextConverter.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::StringView StringViewT, class ExceptionT>
	class StubThrowingStringToAntlrContextConverter :
		public CmdCalculator::StringToAntlrContextConverter_IntendedSatisfaction
	{
	public:
		using StringViewType = StringViewT;
		using ExceptionType = ExceptionT;
		//using AntlrFullExpressionContextOwnerType = CmdCalculatorTestDoubles::StubTrackingAntlrFullExpressionContextOwner<StringViewType>;

		ExceptionType exceptionToThrow;


		/*AntlrFullExpressionContextOwnerType getStringAsAntlrContext(StringViewT source) const
		{
			throw exceptionToThrow;
		}*/
	};
}