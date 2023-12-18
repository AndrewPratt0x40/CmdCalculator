#include "pch.h"

#include <string>
#include <string_view>

#include "..\CmdCalculator\Process.h"
#include "..\CmdCalculatorTestDoubles/StubRawCmdLineArgParser.h"
#include "..\CmdCalculatorTestDoubles/StubStringToMathAstConverter.h"
#include "..\CmdCalculatorTestDoubles/StubMathAstToExpressionConverter.h"
#include "..\CmdCalculatorTestDoubles/StubExpressionToStringConverter.h"

namespace CmdCalculatorTests
{
#pragma region Constructor

	template
	<
		CmdCalculator::RawCmdLineArgParser RawCmdLineArgParserT,
		RawCmdLineArgParserT rawCmdLineArgParser,
		CmdCalculator::StringToMathAstConverter StringToMathAstConverterT,
		StringToMathAstConverterT stringToMathAstConverter,
		CmdCalculator::MathAstToExpressionConverter MathAstToExpressionConverterT,
		MathAstToExpressionConverterT mathAstToExpressionConverter,
		CmdCalculator::ExpressionToStringConverter ExpressionToStringConverterT,
		ExpressionToStringConverterT expressionToStringConverter
	>
	struct Process_CtorParams
	{};

	template<class T>
	class ProcessConstructorTests :
		public testing::Test
	{};

	using ProcessConstructorTests_Types = testing::Types
	<
		Process_CtorParams
		<
			CmdCalculatorTestDoubles::StubRawCmdLineArgParser<std::string>,
			{},
		>
	>;

	INSTANTIATE_TYPED_TEST_CASE_P(ProcessConstructorTests, ProcessConstructorTests_Types);

#pragma endregion
}