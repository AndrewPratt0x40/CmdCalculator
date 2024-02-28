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
	template
	<
		class SourcePartsT,
		CmdCalculator::String MathAstStringT
	>
		requires CmdCalculator::MathAst::DynamicExpressionPartNodeRange<SourcePartsT, MathAstStringT>
	struct StubTrackingDynamicExpressionPartRecursiveSplitResult :
		public CmdCalculator::DynamicExpressionPartRecursiveSplitResult_IntendedSatisfaction
	{
		using SourcePartsType = SourcePartsT;
		using MathAstStringType = MathAstStringT;


		SourcePartsType sourceParts;
		std::unique_ptr<StubTrackingDynamicExpressionPartRecursiveSplitResult<SourcePartsT, MathAstStringT>> leftPart;
		std::reference_wrapper<const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>> splitPart;
		std::unique_ptr<StubTrackingDynamicExpressionPartRecursiveSplitResult<SourcePartsT, MathAstStringT>> rightPart;


		StubTrackingDynamicExpressionPartRecursiveSplitResult<SourcePartsT, MathAstStringT>* getLeftPart() const
		{
			return leftPart.get();
		}


		CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringT>& getSplitPart() const
		{
			return splitPart.get();
		}


		StubTrackingDynamicExpressionPartRecursiveSplitResult<SourcePartsT, MathAstStringT>* getRightPart() const
		{
			return rightPart.get();
		}


		std::string STUB_getStringRepresentation() const
		{
			return std::format
			(
				"{{[{}]->{}<{}>{}}}",
				CmdCalculatorTestUtils::joinStrings
				(
					sourceParts
					| std::views::transform
					(
						[](const CmdCalculator::MathAst::DynamicExpressionPartNode<MathAstStringType>& part)
						{ return CmdCalculator::convertString<char>(part.getStringRepresentation()); }
					)
				),
				leftPart ? (leftPart->STUB_getStringRepresentation()) : "null"s,
				splitPart.get().getStringRepresentation(),
				rightPart ? (rightPart->STUB_getStringRepresentation()) : "null"s
			);
		};


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const StubTrackingDynamicExpressionPartRecursiveSplitResult<SourcePartsT, std::string>& instance
		)
		{
			ostream << instance.STUB_getStringRepresentation();
			return ostream;
		}


		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const std::optional<StubTrackingDynamicExpressionPartRecursiveSplitResult<SourcePartsT, std::string>>& instance
		)
		{
			ostream << instance.has_value() ? instance.value().STUB_getStringRepresentation() : "{empty}";
			return ostream;
		}
	};
}