#pragma once

#include <span>
#include <memory>

#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<::CmdCalculator::String StringT>
	class StubDynamicExpressionPartNode :
		public ::CmdCalculator::MathAst::DynamicExpressionPartNode<StringT>,
		public ::CmdCalculator::MathAst::MathAstNode_IntendedSatisfaction
	{
	public:
		using StringType = StringT;

		bool isBinaryOperatorValue;
		StringT leadingTrivia;
		StringT trailingTrivia;
		StringT stringRepresentation;


		StubDynamicExpressionPartNode
		(
			const bool isBinaryOperatorValue,
			const StringT leadingTrivia,
			const StringT trailingTrivia,
			const StringT stringRepresentation
		) :
			isBinaryOperatorValue{ isBinaryOperatorValue },
			leadingTrivia{ leadingTrivia },
			trailingTrivia{ trailingTrivia },
			stringRepresentation{ stringRepresentation }
		{}


		StringT getLeadingTrivia() const override
		{
			return leadingTrivia;
		}


		StringT getTrailingTrivia() const override
		{
			return trailingTrivia;
		}


		StringT getStringRepresentation() const override
		{
			return stringRepresentation;
		}


		bool isBinaryOperator() const override
		{
			return isBinaryOperatorValue;
		}
	};
}