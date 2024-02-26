#pragma once

#include <span>
#include <memory>

#include "../CmdCalculator/dynamic_mathast.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::MathAst
{
	template<::CmdCalculator::String StringT>
	class StubDynamicOperandNode :
		public ::CmdCalculator::MathAst::DynamicOperandNode<StringT>,
		public ::CmdCalculator::MathAst::ExpressionPartNode_IntendedSatisfaction,
		public ::CmdCalculator::MathAst::MathAstNode_IntendedSatisfaction
	{
	public:
		using StringType = StringT;


		::CmdCalculator::MathAst::EDerivedDynamicOperandNodeKind derivedOperandKind;
		StringType leadingTrivia;
		StringType trailingTrivia;
		StringType stringRepresentation;

		
		StubDynamicOperandNode
		(
			const ::CmdCalculator::MathAst::EDerivedDynamicOperandNodeKind derivedOperandKind,
			const StringType leadingTrivia,
			const StringType trailingTrivia,
			const StringType stringRepresentation
		) :
			derivedOperandKind{ derivedOperandKind },
			leadingTrivia{ leadingTrivia },
			trailingTrivia{ trailingTrivia },
			stringRepresentation{ stringRepresentation }
		{}


		::CmdCalculator::MathAst::EDerivedDynamicOperandNodeKind getDerivedOperandKind() const override
		{
			return derivedOperandKind;
		}


		StringType getLeadingTrivia() const override
		{
			return leadingTrivia;
		}


		StringType getTrailingTrivia() const override
		{
			return trailingTrivia;
		}


		StringT getStringRepresentation() const override
		{
			return stringRepresentation;
		}
	};
}