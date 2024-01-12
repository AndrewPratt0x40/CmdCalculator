#pragma once

#include <functional>
#include <memory>

#include "../CmdCalculator/StringToAntlrContextConverter.h"
#include "../CmdCalculator/FullExpressionAntlrContext.h"
#include "StubTrackingFullExpressionAntlrContext.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::StringView StringViewT>
	struct StubTrackingStringToAntlrContextConverter :
		public CmdCalculator::StringToAntlrContextConverter_IntendedSatisfaction
	{
	public:
		using StringViewType = StringViewT;
		using FullExpressionAntlrContexType = StubTrackingFullExpressionAntlrContext<StringViewType>;
		using ConvertedLeadingTriviaType = decltype(std::declval<FullExpressionAntlrContexType>().leadingTrivia);
		using ConvertedExpressionValueType = decltype(std::declval<FullExpressionAntlrContexType>().expressionValue);
		using ConvertedTrailingTriviaType = decltype(std::declval<FullExpressionAntlrContexType>().trailingTrivia);

		ConvertedLeadingTriviaType convertedLeadingTrivia;
		ConvertedExpressionValueType convertedExpressionValue;
		ConvertedTrailingTriviaType convertedTrailingTrivia;


		FullExpressionAntlrContexType getStringAsAntlrContext(StringViewT source) const
		{
			return FullExpressionAntlrContexType
			{
				.stringSource{ source },
				.leadingTrivia{ convertedLeadingTrivia },
				.expressionValue{ convertedExpressionValue },
				.trailingTrivia{ convertedTrailingTrivia }
			};
		}
	};
}