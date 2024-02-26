#include "pch.h"

#include <string>
#include <string_view>

#include "../CmdCalculatorTestDoubles/StubMathAstNode.h"
#include "../CmdCalculatorTestDoubles/StubStringToMathAstConverter.h"
#include "../CmdCalculator/StringToMathAstConverter.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/MathAstNode.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	template<::CmdCalculator::StringView StringViewT, ::CmdCalculator::MathAst::MathAstNode MathAstNodeT>
	struct StubStringToMathAstConverter_TParams
	{
		using StringViewType = StringViewT;
		using MathAstNodeType = MathAstNodeT;
	};

	template<class T>
	class StubStringToMathAstConverterWithTParamsTests :
		public testing::Test
	{};

	using StubStringToMathAstConverterWithTParamsTests_Types = testing::Types
	<
		StubStringToMathAstConverter_TParams<std::string_view, CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>>
	>;

	TYPED_TEST_CASE(StubStringToMathAstConverterWithTParamsTests, StubStringToMathAstConverterWithTParamsTests_Types);


	TYPED_TEST(StubStringToMathAstConverterWithTParamsTests, StubStringToMathAstConverter$satisfies$StringToMathAstConverter$concept)
	{
		static_assert
		(
			::CmdCalculator::StringToMathAstConverter
			<
				CmdCalculatorTestDoubles::StubStringToMathAstConverter
				<
					typename TypeParam::StringViewType,
					typename TypeParam::MathAstNodeType
				>
			>
		);
	}

#pragma endregion
}