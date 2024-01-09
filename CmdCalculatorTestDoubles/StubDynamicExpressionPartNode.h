#pragma once

#include <concepts>
#include <span>

#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<CmdCalculator::String StringT>
	class StubDynamicExpressionPartNode :
		public CmdCalculator::MathAst::DynamicExpressionPartNode<StringT>
	{
	public:

		using StringType = CmdCalculator::MathAst::DynamicExpressionPartNode<StringT>::StringType;
		

		StringType leadingTrivia;
		StringType trailingTrivia;
		StringType stringRepresentation;


		StringType getLeadingTrivia() const override
		{
			return leadingTrivia;
		}


		StringType getTrailingTrivia() const override
		{
			return trailingTrivia;
		}


		StringType getStringRepresentation() const override
		{
			return stringRepresentation;
		}


		StubDynamicExpressionPartNode
		(
			const StringT leadingTrivia,
			const StringT trailingTrivia,
			const StringT stringRepresentation
		) :
			leadingTrivia{ leadingTrivia },
			trailingTrivia{ trailingTrivia },
			stringRepresentation{ stringRepresentation }
		{}
	};
}