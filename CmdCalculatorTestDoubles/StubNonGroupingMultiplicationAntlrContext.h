#pragma once

#include <optional>

#include "../CmdCalculator/NonGroupingMultiplicationAntlrContext.h"
#include "StubNumberLiteralAntlrContext.h"
#include "StubSignOperationAntlrContext.h"
#include "StubSqrtOperationAntlrContext.h"
#include "StubGroupingAntlrContext.h"
#include "StubAbsoluteValueOperationAntlrContext.h"

namespace CmdCalculatorTestDoubles
{
	struct StubNonGroupingMultiplicationAntlrContext :
		public CmdCalculator::NonGroupingMultiplicationAntlrContext_IntendedSatisfaction
	{
		using NumberLiteralAntlrContextType = StubNumberLiteralAntlrContext;
		using SignOperationAntlrContextType = StubSignOperationAntlrContext;
		using SqrtOperationAntlrContextType = StubSqrtOperationAntlrContext;
		using GroupingAntlrContextType = StubGroupingAntlrContext;
		using AbsoluteValueOperationAntlrContextType = StubAbsoluteValueOperationAntlrContext;

		CmdCalculator::ENonGroupingMultiplicationAntlrContextKind nonGroupingMultiplicationKind;
		std::optional<NumberLiteralAntlrContextType> numberLiteral;
		std::optional<SignOperationAntlrContextType> signOperation;
		std::optional<SqrtOperationAntlrContextType> sqrtOperation;
		std::optional<GroupingAntlrContextType> grouping;
		std::optional<AbsoluteValueOperationAntlrContextType> absoluteValueOperation;


		CmdCalculator::ENonGroupingMultiplicationAntlrContextKind getNonGroupingMultiplicationKind() const
		{
			return nonGroupingMultiplicationKind;
		}


		std::optional<NumberLiteralAntlrContextType> getNumberLiteral() const
		{
			return numberLiteral;
		}



		std::optional<SignOperationAntlrContextType> getSignOperation() const
		{
			return signOperation;
		}



		std::optional<SqrtOperationAntlrContextType> getSqrtOperation() const
		{
			return sqrtOperation;
		}



		std::optional<GroupingAntlrContextType> getGrouping() const
		{
			return grouping;
		}



		std::optional<AbsoluteValueOperationAntlrContextType> getAbsoluteValueOperation() const
		{
			return absoluteValueOperation;
		}
	};
}