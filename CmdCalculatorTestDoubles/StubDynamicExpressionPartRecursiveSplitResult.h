#pragma once

#include <functional>
#include <concepts>
#include <memory>

#include "../CmdCalculator/DynamicExpressionPartRecursiveSplitResult.h"
#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/strings.h"


namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::String MathAstStringT>
	struct StubDynamicExpressionPartRecursiveSplitResult;

	template<CmdCalculator::String MathAstStringT>
	struct StubDynamicExpressionPartRecursiveSplitResult :
		public CmdCalculator::DynamicExpressionPartRecursiveSplitResult_IntendedSatisfaction
	{
		using MathAstStringType = MathAstStringT;


		std::unique_ptr<StubDynamicExpressionPartRecursiveSplitResult<MathAstStringT>> leftPart;
		std::reference_wrapper<CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>> splitPart;
		std::unique_ptr<StubDynamicExpressionPartRecursiveSplitResult<MathAstStringT>> rightPart;


		StubDynamicExpressionPartRecursiveSplitResult<MathAstStringT>* getLeftPart() const
		{
			return leftPart.get();
		}


		CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>& getSplitPart() const
		{
			return splitPart.get();
		}


		StubDynamicExpressionPartRecursiveSplitResult<MathAstStringT>* getRightPart() const
		{
			return rightPart.get();
		}
	};
}