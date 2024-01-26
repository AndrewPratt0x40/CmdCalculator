#include "pch.h"

#include "../CmdCalculator/AntlrBasedStringToMathAstConverter.h"
#include "../CmdCalculator/StringToMathAstConverter.h"
#include "../CmdCalculator/EmptyInputExpressionException.h"
#include "../CmdCalculator/UnexpectedInputExpressionCharException.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionLexer.h"
#include "../CmdCalculatorAntlr/generated_code/CmdCalculatorExpressionParser.h"
#include "../CmdCalculatorTestDoubles/StubTrackingStringToAntlrContextConverter.h"
#include "../CmdCalculatorTestDoubles/StubThrowingStringToAntlrContextConverter.h"
#include "../CmdCalculatorTestDoubles/StubTrackingAntlrContextToMathAstConverter.h"
#include "../submodules/Antlr4CppRuntime/src/RecognitionException.h"

#include <string>
#include <optional>
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


	TEST(AntlrBasedStringToMathAstConverterTests, Calling$getStringAsMathAst$throws$UnexpectedInputExpressionCharException$when$StringToAntlrContextConverter$throws$RecognitionException)
	{
		// Arrange
		ASSERT_TRUE(std::copyable<antlr4::RecognitionException>);
		
		std::string inputExpression{"Input expression"};
		
		using StringToAntlrContextConverterType =
			CmdCalculatorTestDoubles::StubThrowingStringToAntlrContextConverter<std::string_view, antlr4::RecognitionException>
		;

		antlr4::ANTLRInputStream inputStream{ "BAD INPUT" };
		std::unique_ptr<CmdCalculator::Antlr::CmdCalculatorExpressionLexer> lexer{};
		std::unique_ptr<antlr4::CommonTokenStream> tokenStream{};
		std::unique_ptr<CmdCalculator::Antlr::CmdCalculatorExpressionParser> parser{};
		const auto parserErrorHandler{ std::make_shared<antlr4::BailErrorStrategy>() };

		
		std::optional<antlr4::RecognitionException> exceptionToThrow{};
		try
		{
			lexer = std::make_unique<CmdCalculator::Antlr::CmdCalculatorExpressionLexer>(&inputStream);
			lexer->removeErrorListeners();
			tokenStream = std::make_unique<antlr4::CommonTokenStream>(lexer.get());
			parser = std::make_unique<CmdCalculator::Antlr::CmdCalculatorExpressionParser>(tokenStream.get());
			parser->setErrorHandler(parserErrorHandler);
			parser->removeErrorListeners();
			parser->full_expression();
		}
		catch (antlr4::ParseCancellationException& exception)
		{
			try
			{
				std::rethrow_if_nested(exception);
			}
			catch (antlr4::RecognitionException& innerException)
			{
				exceptionToThrow = innerException;
			}
		}
		ASSERT_TRUE(exceptionToThrow.has_value());
		
		
		StringToAntlrContextConverterType stringToAntlrContextConverter
		{
#pragma warning(push)
#pragma warning(disable: 26859) // Empty optional "exceptionToThrow" is unwrapped, will throw exception.
			.exceptionToThrow{ exceptionToThrow.value() }
#pragma warning(pop)
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
			CmdCalculator::UnexpectedInputExpressionCharException
		);
	}

#pragma endregion
}