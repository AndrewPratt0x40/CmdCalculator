#include "pch.h"

#include <string>
#include <string_view>

#include "../CmdCalculatorTestDoubles/StubMathAstNode.h"
#include "../CmdCalculatorTestDoubles/StubValidatingStringToMathAstConverter.h"
#include "../CmdCalculator/StringToMathAstConverter.h"
#include "../CmdCalculator/strings.h"
#include "../CmdCalculator/MathAstNode.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	template<::CmdCalculator::StringView StringViewT, ::CmdCalculator::MathAst::MathAstNode MathAstNodeT, class ExceptionT>
	struct StubValidatingStringToMathAstConverter_TParams
	{
		using StringViewType = StringViewT;
		using MathAstNodeType = MathAstNodeT;
		using ExceptionType = ExceptionT;
	};

	template<class T>
	class StubValidatingStringToMathAstConverterWithTParamsTests :
		public testing::Test
	{};

	using StubValidatingStringToMathAstConverterWithTParamsTests_Types = testing::Types
	<
		StubValidatingStringToMathAstConverter_TParams<std::string_view, CmdCalculatorTestDoubles::MathAst::StubMathAstNode<std::string>, int>
	>;

	TYPED_TEST_CASE(StubValidatingStringToMathAstConverterWithTParamsTests, StubValidatingStringToMathAstConverterWithTParamsTests_Types);


	TYPED_TEST(StubValidatingStringToMathAstConverterWithTParamsTests, StubValidatingStringToMathAstConverter$satisfies$StringToMathAstConverter$concept)
	{
		static_assert
		(
			::CmdCalculator::StringToMathAstConverter
			<
				CmdCalculatorTestDoubles::StubValidatingStringToMathAstConverter
				<
					typename TypeParam::StringViewType,
					typename TypeParam::MathAstNodeType,
					typename TypeParam::ExceptionType
				>
			>
		);
	}

#pragma endregion
}