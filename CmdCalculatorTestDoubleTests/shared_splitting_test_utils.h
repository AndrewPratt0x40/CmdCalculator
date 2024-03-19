#pragma once
#include "pch.h"

#include <string>
#include <algorithm>
#include <ranges>
#include <optional>
#include <vector>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/DynamicExpressionPartSingleSplitter.h"
#include "../CmdCalculatorTestDoubles/FakeHalfwayDynamicExpressionPartSingleSplitter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"


namespace CmdCalculatorTestDoubleTests
{
	static std::string stringifySplittingParts(std::ranges::forward_range auto parts)
		requires std::same_as<std::string, std::ranges::range_value_t<decltype(parts)>>
	{
		return CmdCalculatorTestUtils::joinStrings(parts);
	}


	static std::string stringifySplittingParts(const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto parts)
	{
		return stringifySplittingParts
		(
			parts
			| std::views::transform
			(
				[](const CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>& part)
				{ return part.getStringRepresentation(); }
			)
		);
	}


	CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
		makeExpressionPart(std::string stringRepresentation)
	;


	std::optional<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>>
		makeOptionalExpressionPart(std::string stringRepresentation)
	;


	std::vector<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>>
		makeExpressionParts(std::initializer_list<std::string> stringRepresentations)
	;
}