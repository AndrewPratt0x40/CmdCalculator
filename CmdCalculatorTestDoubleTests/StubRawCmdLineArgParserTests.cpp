#include "pch.h"

#include <string>
#include <concepts>
#include <ranges>
#include <vector>
#include <list>

#include "../CmdCalculatorTestDoubles/StubRawCmdLineArgParser.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/RawCmdLineArgParser.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	template<std::ranges::input_range ArgsT, ::CmdCalculator::String ExpressionStringT>
	struct StubRawCmdLineArgParser_TParams
	{
		using ArgsType = ArgsT;
		using ExpressionStringType = ExpressionStringT;
	};
	
	template<class T>
	class StubRawCmdLineArgParserWithTParamsTests :
		public testing::Test
	{};

	using StubRawCmdLineArgParserWithTParamsTests_Types = testing::Types
	<
		StubRawCmdLineArgParser_TParams<std::vector<std::string>, std::string>,
		StubRawCmdLineArgParser_TParams<std::list<std::string>, std::string>,
		StubRawCmdLineArgParser_TParams<std::ranges::owning_view<std::vector<std::string>>, std::string>,
		StubRawCmdLineArgParser_TParams<std::ranges::ref_view<std::vector<std::string>>, std::string>
	>;

	TYPED_TEST_CASE(StubRawCmdLineArgParserWithTParamsTests, StubRawCmdLineArgParserWithTParamsTests_Types);
	
	TYPED_TEST(StubRawCmdLineArgParserWithTParamsTests, StubRawCmdLineArgParser$satisfies$RawCmdLineArgParser$concept)
	{
		static_assert
		(
			::CmdCalculator::RawCmdLineArgParser
			<
				CmdCalculatorTestDoubles::StubRawCmdLineArgParser<typename TypeParam::ExpressionStringType>,
				typename TypeParam::ArgsType
			>
		);
	}

#pragma endregion
}