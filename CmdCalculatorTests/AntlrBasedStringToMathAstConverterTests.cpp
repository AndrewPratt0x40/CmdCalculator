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
		static_assert
		(
			CmdCalculator::StringToMathAstConverter
			<
				CmdCalculator::AntlrBasedStringToMathAstConverter
				<
					std::string_view,
					CmdCalculatorTestDoubles::StubTrackingStringToAntlrContextConverter<std::string_view>,
					CmdCalculatorTestDoubles::StubTrackingAntlrContextToMathAstConverter<std::string, int, std::string_view>
				>
			>
		);
	}

#pragma endregion


#pragma region getStringAsMathAst

	TEST(AntlrBasedStringToMathAstConverterTests, Calling$getStringAsMathAst$returns$the$result$of$using$converters)
	{
		// Arrange
		std::string inputExpression{"Input expression"};
		
		using StringToAntlrContextConverterType = CmdCalculatorTestDoubles::StubTrackingStringToAntlrContextConverter<std::string_view>;

		StringToAntlrContextConverterType stringToAntlrContextConverter
		{
			.convertedLeadingTrivia{},
			.convertedExpressionValue{ CmdCalculatorTestDoubles::StubExpressionAntlrContext{} },
			.convertedTrailingTrivia{}
		};

		using AntlrContextToMathAstConverterType = CmdCalculatorTestDoubles::StubTrackingAntlrContextToMathAstConverter<std::string, int, std::string_view>;

		AntlrContextToMathAstConverterType antlrContextToMathAstConverter
		{
			.convertedContextLeadingTrivia{ "" },
			.convertedContextTrailingTrivia{ "" },
			.convertedContextParts{}
		};

		CmdCalculator::AntlrBasedStringToMathAstConverter<std::string_view, StringToAntlrContextConverterType, AntlrContextToMathAstConverterType> instance
		{
			std::move(stringToAntlrContextConverter),
			std::move(antlrContextToMathAstConverter)
		};

		// Act
		auto returnValue{ instance.getStringAsMathAst(inputExpression) };
		auto expression{ dynamic_cast<CmdCalculatorTestDoubles::MathAst::StubTrackingDynamicExpressionNode<std::string, std::string_view>*>(returnValue.get()) };
		FAIL();
	}

#pragma endregion
}