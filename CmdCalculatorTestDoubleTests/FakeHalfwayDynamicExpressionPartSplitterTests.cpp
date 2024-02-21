#include "pch.h"

#include <string>
#include <ranges>
#include <vector>

#include "../CmdCalculator/DynamicExpressionPartSplitter.h"
#include "../CmdCalculatorTestDoubles/FakeHalfwayDynamicExpressionPartSplitter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Concept satisfaction

	TEST(FakeHalfwayDynamicExpressionPartSplitterTests, FakeHalfwayDynamicExpressionPartSplitter$satisfies$DynamicExpressionPartSplitter$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicExpressionPartSplitter
			<
				CmdCalculatorTestDoubles::FakeHalfwayDynamicExpressionPartSplitter
				<
					std::string
				>,
				std::ranges::ref_view
				<
					std::vector
					<
						std::reference_wrapper
						<
							CmdCalculator::MathAst::DynamicExpressionPartNode
							<
								std::string
							>
						>
					>
				>
			>
		);
	}

#pragma endregion


#pragma region canSplit

	

#pragma endregion
}