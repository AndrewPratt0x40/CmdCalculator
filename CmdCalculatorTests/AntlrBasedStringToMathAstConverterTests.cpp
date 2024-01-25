#include "pch.h"

#include "../CmdCalculator/AntlrBasedStringToMathAstConverter.h"
#include "../CmdCalculator/StringToMathAstConverter.h"
#include "../CmdCalculator/EmptyInputExpressionException.h"
#include "../CmdCalculator/InvalidInputExpressionException.h"
#include "../CmdCalculatorTestDoubles/StubTrackingStringToAntlrContextConverter.h"
#include "../CmdCalculatorTestDoubles/StubThrowingStringToAntlrContextConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingAntlrContextToMathAstConverter.h"
#include "../submodules/Antlr4CppRuntime/src/InputMismatchException.h"
#include "../submodules/Antlr4CppRuntime/src/ParserInterpreter.h"
#include "../submodules/Antlr4CppRuntime/src/CommonTokenStream.h"
#include "../submodules/Antlr4CppRuntime/src/ListTokenSource.h"
#include "../submodules/Antlr4CppRuntime/src/Token.h"

#include <string>
#include <vector>
#include <memory>


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

	TEST(AntlrBasedStringToMathAstConverterTests, Calling$getStringAsMathAst$with$valid$source$returns$the$result$of$using$converters)
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
			.convertedContextTrailingTrivia{ "" }
		};

		CmdCalculator::AntlrBasedStringToMathAstConverter<std::string_view, StringToAntlrContextConverterType, AntlrContextToMathAstConverterType> instance
		{
			std::move(stringToAntlrContextConverter),
			std::move(antlrContextToMathAstConverter)
		};

		// Act
		auto returnValue{ instance.getStringAsMathAst(inputExpression) };
		
		// Assert
		auto expression
		{
			dynamic_cast<CmdCalculatorTestDoubles::MathAst::StubTrackingDynamicExpressionNode<std::string, std::string_view>*>
				(returnValue.get())
		};
		EXPECT_EQ(expression->stringSource, inputExpression);
	}


	TEST(AntlrBasedStringToMathAstConverterTests, Calling$getStringAsMathAst$with$empty$source$throws$EmptyInputExpressionException)
	{
		// Arrange
		std::string inputExpression{""};
		
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
			.convertedContextTrailingTrivia{ "" }
		};

		CmdCalculator::AntlrBasedStringToMathAstConverter<std::string_view, StringToAntlrContextConverterType, AntlrContextToMathAstConverterType> instance
		{
			std::move(stringToAntlrContextConverter),
			std::move(antlrContextToMathAstConverter)
		};

		// Assert
		EXPECT_THROW
		(
			instance.getStringAsMathAst(inputExpression),
			CmdCalculator::EmptyInputExpressionException
		);
	}


	TEST(AntlrBasedStringToMathAstConverterTests, Calling$getStringAsMathAst$throws$InvalidInputExpressionException$when$StringToAntlrContextConverter$throws$InputMismatchException)
	{
		// Arrange
		std::string inputExpression{""};
		
		using StringToAntlrContextConverterType =
			CmdCalculatorTestDoubles::StubThrowingStringToAntlrContextConverter<std::string_view, antlr4::InputMismatchException>
		;

#pragma region Create pseudo-stub InputMismatchException


		const std::string exceptionParserGrammarFileName{};
		const antlr4::dfa::Vocabulary exceptionParserVocabulary{};
		const std::vector<std::string> exceptionParserRuleNames{};
		const antlr4::atn::ATN exceptionParserAtn{};
		antlr4::ListTokenSource exceptionParserInputTokenSource
		{
			std::vector<std::unique_ptr<antlr4::Token>>{}
		};
		antlr4::CommonTokenStream exceptionParserInput{ &exceptionParserInputTokenSource };

		antlr4::ParserInterpreter exceptionParser
		{
			exceptionParserGrammarFileName,
			exceptionParserVocabulary,
			exceptionParserRuleNames,
			exceptionParserAtn,
			&exceptionParserInput
		};
#pragma endregion


		StringToAntlrContextConverterType stringToAntlrContextConverter
		{
			.exceptionToThrow{ &exceptionParser }
		};

		using AntlrContextToMathAstConverterType = CmdCalculatorTestDoubles::StubTrackingAntlrContextToMathAstConverter<std::string, int, std::string_view>;

		AntlrContextToMathAstConverterType antlrContextToMathAstConverter
		{
			.convertedContextLeadingTrivia{ "" },
			.convertedContextTrailingTrivia{ "" }
		};

		CmdCalculator::AntlrBasedStringToMathAstConverter<std::string_view, StringToAntlrContextConverterType, AntlrContextToMathAstConverterType> instance
		{
			std::move(stringToAntlrContextConverter),
			std::move(antlrContextToMathAstConverter)
		};

		// Assert
		EXPECT_THROW
		(
			instance.getStringAsMathAst(inputExpression),
			CmdCalculator::InvalidInputExpressionException
		);
	}

#pragma endregion
}