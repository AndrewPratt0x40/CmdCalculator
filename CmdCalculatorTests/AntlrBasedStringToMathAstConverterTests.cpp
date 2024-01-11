#include "pch.h"

#include "../CmdCalculator/AntlrBasedStringToMathAstConverter.h"
#include "../CmdCalculator/StringToMathAstConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingStringToAntlrContextConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingAntlrContextToMathAstConverter.h"


namespace CmdCalculatorTests
{
#pragma region Concept satisfaction
	
	TEST(AntlrBasedStringToMathAstConverterTests, AntlrBasedStringToMathAstConverter$satisfies$StringToMathAstConverter$concept)
	{
		FAIL();
		static_assert
		(
			true/*CmdCalculator::StringToMathAstConverter
			<
				CmdCalculator::AntlrBasedStringToMathAstConverter
				<
					std::string_view,
					CmdCalculatorTestDoubles::StubTrackingStringToAntlrContextConverter<std::string_view>,
					CmdCalculatorTestDoubles::StubTrackingAntlrContextToMathAstConverter<std::string, int>
				>
			>*/
		);
	}

#pragma endregion


#pragma region getStringAsMathAst

	TEST(AntlrBasedStringToMathAstConverterTests, Calling$getStringAsMathAst$returns$the$result$of$using$converters)
	{
		FAIL();
		// Arrange
		/*std::string inputExpression{"Input expression"};
		
		using StringToAntlrContextConverterType = CmdCalculatorTestDoubles::StubTrackingStringToAntlrContextConverter<std::string_view>;

		StringToAntlrContextConverterType stringToAntlrContextConverter
		{
			.convertedString{ nullptr, static_cast<size_t>(-1) }
		};

		using AntlrContextToMathAstConverterType = CmdCalculatorTestDoubles::StubTrackingAntlrContextToMathAstConverter<std::string, int>;

		CmdCalculatorTestDoubles::MathAst::StubDynamicExpressionPartNode<std::string> expressionParts[]
		{
			{ "", "", "First part" },
			{ "", "", "Second part" },
			{ "", "", "Third part" }
		};

		AntlrContextToMathAstConverterType antlrContextToMathAstConverter
		{
			.convertedContextLeadingTrivia{ "" },
			.convertedContextTrailingTrivia{ "" },
			.convertedContextParts{ expressionParts }
		};

		CmdCalculator::AntlrBasedStringToMathAstConverter<std::string_view, StringToAntlrContextConverterType, AntlrContextToMathAstConverterType> instance
		{
			std::move(stringToAntlrContextConverter),
			std::move(antlrContextToMathAstConverter)
		};

		// Act
		std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionNode<std::string>> returnValue{ instance.getStringAsMathAst(inputExpression) };
		auto expression{ dynamic_cast<CmdCalculatorTestDoubles::MathAst::StubTrackingDynamicExpressionNode<std::string>>(returnValue) };*/

	}

#pragma endregion
}