#pragma once

#include <concepts>
#include <memory>

#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/RealNumber.h"
#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::Expressions
{
	template
	<
		::CmdCalculator::Arithmetic::RealNumber NumberT,
		::CmdCalculator::MathAst::MathAstNode SourceMathAstNodeT
	>
	struct StubTrackingExpression :
		public ::CmdCalculator::Expressions::Expression_IntendedSatisfaction
	{
		using NumberType = NumberT;

		SourceMathAstNodeT mathAstSource;
		//bool wasSimplified;

		NumberType evaluation;
		//bool isSimplifiableValue;


		NumberType getEvaluation() const
		{
			return evaluation;
		}


		/*bool isSimplifiable() const
		{
			return isSimplifiableValue;
		}


		StubTrackingExpression<SourceMathAstNodeT> getFullSimplification() const
		{
			return isSimplifiableValue
				? StubTrackingExpression<SourceMathAstNodeT>
				{
					.mathAstSource{ mathAstSource },
					.wasSimplified{ true },
					.isSimplifiableValue{ false }
				}
				: *this;
		}*/
	};
}