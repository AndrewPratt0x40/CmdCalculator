#include "pch.h"
#include "shared_splitting_test_utils.h"


CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
	CmdCalculatorTestDoubleTests::makeExpressionPart(std::string stringRepresentation)
{
	return CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>
	{
		false,
		"",
		"",
		stringRepresentation
	};
}


std::optional<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>>
	CmdCalculatorTestDoubleTests::makeOptionalExpressionPart(std::string stringRepresentation)
{
	return std::make_optional<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>>
		(makeExpressionPart(stringRepresentation))
	;
}


std::vector<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>>
CmdCalculatorTestDoubleTests::makeExpressionParts(std::initializer_list<std::string> stringRepresentations)
{
	std::ranges::input_range auto partsView
	{
		stringRepresentations
		| std::views::transform
		(
			[](const std::string& stringRepresentation)
			{ return makeExpressionPart(stringRepresentation); }
		)
	};

	return std::vector<CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string>>
	{
		std::ranges::begin(partsView),
		std::ranges::end(partsView)
	};
}