#pragma once

#include <functional>
#include <concepts>
#include <optional>
#include <memory>
#include <string>
#include <format>
#include <iostream>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/DynamicExpressionPartRecursiveSplitResult.h"
#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/DynamicExpressionPartRecursiveSplitter.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/std_polyfills.h"


using namespace std::string_literals;


namespace CmdCalculatorTestDoubles
{
	template<CmdCalculator::String MathAstStringT>
	struct StubDynamicExpressionPartRecursiveSplitResult :
		public CmdCalculator::DynamicExpressionPartRecursiveSplitResult_IntendedSatisfaction
	{
		using MathAstStringType = MathAstStringT;


		std::unique_ptr<StubDynamicExpressionPartRecursiveSplitResult<MathAstStringT>> leftPart;
		std::reference_wrapper<const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>> splitPart;
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