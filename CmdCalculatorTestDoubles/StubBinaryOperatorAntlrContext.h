#pragma once

#include <optional>

#include "../CmdCalculator/BinaryOperatorAntlrContext.h"
#include "StubAntlrToken.h"

namespace CmdCalculatorTestDoubles
{
	struct StubBinaryOperatorAntlrContext :
		public ::CmdCalculator::BinaryOperatorAntlrContext_IntendedSatisfaction
	{
		using AntlrTokenType = StubAntlrToken<std::string>;

		::CmdCalculator::MathAst::EBinaryOperator binaryOperatorAntlrContextKind;
		AntlrTokenType token;


		::CmdCalculator::MathAst::EBinaryOperator getBinaryOperatorAntlrContextKind() const
		{
			return binaryOperatorAntlrContextKind;
		}


		AntlrTokenType getToken() const
		{
			return token;
		}
	};
}