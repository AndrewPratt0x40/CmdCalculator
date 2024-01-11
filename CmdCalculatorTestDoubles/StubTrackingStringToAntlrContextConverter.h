#pragma once

#include <functional>
#include <memory>

#include "../CmdCalculator/StringToAntlrContextConverter.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::StringView StringViewT>
	struct StubTrackingStringToAntlrContextConverter :
		public CmdCalculator::StringToAntlrContextConverter_IntendedSatisfaction
	{
	public:
		using StringViewType = StringViewT;
		//using AntlrFullExpressionContextOwnerType = CmdCalculatorTestDoubles::StubTrackingAntlrFullExpressionContextOwner<StringViewType>;

		//CmdCalculator::Antlr::CmdCalculatorExpressionParser::Full_expressionContext convertedString;


		/*AntlrFullExpressionContextOwnerType getStringAsAntlrContext(StringViewT source) const
		{
			static_assert(std::copyable<decltype(convertedString)>);
			return AntlrFullExpressionContextOwnerType
			{
				.stringSource{ source },
				.value{ convertedString }
			};
		}*/
	};
}