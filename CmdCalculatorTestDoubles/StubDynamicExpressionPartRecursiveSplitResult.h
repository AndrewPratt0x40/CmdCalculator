#pragma once

#include <functional>
#include <concepts>
#include <optional>
#include <memory>
#include <string>
#include <format>
#include <iostream>

#include "../CmdCalculator/DynamicExpressionPartRecursiveSplitResult.h"
#include "../CmdCalculator/DynamicExpressionPartNode.h"
#include "../CmdCalculator/strings.h"


using namespace std::string_literals;


namespace CmdCalculatorTestDoubles
{
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


		std::string STUB_getStringRepresentation() const
		{
			return std::format
			(
				"{{{}<{}>{}}}",
				leftPart ? stringifyStubDynamicExpressionPartRecursiveSplitResult(*leftPart) : "null"s,
				splitPart.get().getStringRepresentation(),
				rightPart ? stringifyStubDynamicExpressionPartRecursiveSplitResult(*rightPart) : "null"s
			);
		};


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const StubDynamicExpressionPartRecursiveSplitResult<std::string>& instance
		)
		{
			ostream << instance.STUB_getStringRepresentation();
			return ostream;
		}


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const std::optional<StubDynamicExpressionPartRecursiveSplitResult<std::string>>& instance
		)
		{
			ostream << instance.has_value() ? instance.value().STUB_getStringRepresentation() : "{empty}";
			return ostream;
		}
	};
}