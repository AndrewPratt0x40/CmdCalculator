#include "pch.h"

#include <string>
#include <concepts>
#include <ranges>
#include <vector>
#include <list>

#include "../CmdCalculatorTestDoubles/StubThrowingRawCmdLineArgParser.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/RawCmdLineArgParser.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	template<std::ranges::input_range ArgsT, class ExceptionT, ::CmdCalculator::String ExpressionStringT>
	struct StubThrowingRawCmdLineArgParser_TParams
	{
		using ArgsType = ArgsT;
		using ExceptionType = ExceptionT;
		using ExpressionStringType = ExpressionStringT;
	};

	template<class T>
	class StubThrowingRawCmdLineArgParserWithTParamsTests :
		public testing::Test
	{};

	using StubThrowingRawCmdLineArgParserWithTParamsTests_Types = testing::Types
	<
		StubThrowingRawCmdLineArgParser_TParams<std::vector<std::string>, int, std::string>,
		StubThrowingRawCmdLineArgParser_TParams<std::vector<std::string>, std::exception, std::string>,
		StubThrowingRawCmdLineArgParser_TParams<std::list<std::string>, int, std::string>,
		StubThrowingRawCmdLineArgParser_TParams<std::ranges::owning_view<std::vector<std::string>>, int, std::string>,
		StubThrowingRawCmdLineArgParser_TParams<std::ranges::ref_view<std::vector<std::string>>, int, std::string>
	>;

	TYPED_TEST_CASE(StubThrowingRawCmdLineArgParserWithTParamsTests, StubThrowingRawCmdLineArgParserWithTParamsTests_Types);

	TYPED_TEST(StubThrowingRawCmdLineArgParserWithTParamsTests, StubThrowingRawCmdLineArgParser$satisfies$RawCmdLineArgParser$concept)
	{
		static_assert
		(
			::CmdCalculator::RawCmdLineArgParser
			<
				CmdCalculatorTestDoubles::StubThrowingRawCmdLineArgParser
				<
					typename TypeParam::ExceptionType,
					typename TypeParam::ExpressionStringType
				>,
				typename TypeParam::ArgsType
			>
		);
	}

#pragma endregion
}