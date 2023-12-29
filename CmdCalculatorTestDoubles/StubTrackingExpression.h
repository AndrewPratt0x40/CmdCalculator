#pragma once

#include <concepts>
#include <memory>

#include "../CmdCalculator/Expression.h"
#include "../CmdCalculator/MathAstNode.h"
#include "../CmdCalculator/strings.h"

namespace CmdCalculatorTestDoubles::Expressions
{
	template<CmdCalculator::MathAst::MathAstNode SourceMathAstNodeT>
	struct StubTrackingExpression :
		public CmdCalculator::Expressions::Expression_IntendedSatisfaction
	{
		SourceMathAstNodeT mathAstSource;
		bool wasSimplified;

		bool isSimplifiableValue;


		bool isSimplifiable() const
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
		}
	};
}