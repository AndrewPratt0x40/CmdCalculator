#include "pch.h"

#include <string>
#include <string_view>

#include "../CmdCalculatorTestDoubles/StubTrackingStringToMathAstConverter.h"
#include "../CmdCalculator/StringToMathAstConverter.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/MathAstNode.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	template<CmdCalculator::StringView StringViewT, CmdCalculator::String MathAstNodeStringT>
	struct StubTrackingStringToMathAstConverter_TParams
	{
		using StringViewType = StringViewT;
		using MathAstNodeStringType = MathAstNodeStringT;
	};

	template<class T>
	class StubTrackingStringToMathAstConverterWithTParamsTests :
		public testing::Test
	{};

	using StubTrackingStringToMathAstConverterWithTParamsTests_Types = testing::Types
	<
		StubTrackingStringToMathAstConverter_TParams<std::string_view, std::string>
	>;

	TYPED_TEST_CASE(StubTrackingStringToMathAstConverterWithTParamsTests, StubTrackingStringToMathAstConverterWithTParamsTests_Types);


	TYPED_TEST(StubTrackingStringToMathAstConverterWithTParamsTests, StubTrackingStringToMathAstConverter$satisfies$StringToMathAstConverter$concept)
	{
		static_assert
		(
			CmdCalculator::StringToMathAstConverter
			<
				CmdCalculatorTestDoubles::StubTrackingStringToMathAstConverter
				<
					typename TypeParam::StringViewType,
					typename TypeParam::MathAstNodeStringType
				>
			>
		);
	}

#pragma endregion
}