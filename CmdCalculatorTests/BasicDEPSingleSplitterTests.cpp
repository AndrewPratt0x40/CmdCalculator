#include "pch.h"

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/BasicDEPSingleSplitter.h"
#include "../CmdCalculator/DynamicExpressionPartSingleSplitter.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpressionPartNode.h"
#include "../CmdCalculatorTestDoubles/StubDynamicOperandNode.h"

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <functional>
#include <variant>


namespace CmdCalculatorTests
{
#pragma region Concept satisfaction
	
	TEST(BasicDEPSingleSplitterTests, BasicDEPSingleSplitter$satisfies$the$DynamicExpressionPartSingleSplitter$concept)
	{
		static_assert
		(
			CmdCalculator::DynamicExpressionPartSingleSplitter
			<
				CmdCalculator::BasicDEPSingleSplitter<std::string>
			>
		);
	}

#pragma endregion


#pragma region Shared test data

	struct BasicDEPSingleSplitter_ReturnValue_TestData
	{
		using PartType = std::variant<std::string, CmdCalculator::MathAst::EBinaryOperator>;

		std::vector<PartType> leftParts;
		PartType splitPart;
		std::vector<PartType> rightParts;
	};
	
	struct BasicDEPSingleSplitter_TestData
	{
		std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>> parts;
		std::optional<BasicDEPSingleSplitter_ReturnValue_TestData> expectedSplitResult;
	};


	static std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>> makeOperandPart(const std::string stringRepresentation)
	{
		return std::make_unique<CmdCalculatorTestDoubles::MathAst::StubDynamicOperandNode<std::string>>
		(
			CmdCalculator::MathAst::EDerivedDynamicOperandNodeKind::NumberLiteral,
			"",
			"",
			stringRepresentation
		);
	}


	static std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>> makeOperatorPart(const CmdCalculator::MathAst::EBinaryOperator binaryOperator)
	{
		return std::make_unique<CmdCalculator::MathAst::DynamicBinaryOperatorNode<std::string>>
		(binaryOperator, "", "");
	}


	static std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>> makeValidFiveParts
	(
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator1,
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator2
	)
	{
		return std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>>
		{
			std::move(makeOperandPart("Operand1")),
			std::move(makeOperatorPart(binaryOperator1)),
			std::move(makeOperandPart("Operand2")),
			std::move(makeOperatorPart(binaryOperator2)),
			std::move(makeOperandPart("Operand3"))
		};
	}


	static BasicDEPSingleSplitter_TestData makeValidFivePartBasicDEPSingleSplitter_TestData
	(
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator1,
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator2,
		const bool splitOnbinaryOperator1
	)
	{
		if (splitOnbinaryOperator1)
		{
			return BasicDEPSingleSplitter_TestData
			{
				.parts{ makeValidFiveParts(binaryOperator1, binaryOperator2) },
				.expectedSplitResult
				{
					std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
					(
						BasicDEPSingleSplitter_ReturnValue_TestData
						{
							.leftParts{ "Operand1" },
							.splitPart{ binaryOperator1 },
							.rightParts
							{
								"Operand2",
								binaryOperator2,
								"Operand3"
							}
						}
					)
				}
			};
		}

		return BasicDEPSingleSplitter_TestData
		{
			.parts{ makeValidFiveParts(binaryOperator1, binaryOperator2) },
			.expectedSplitResult
			{
				std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
				(
					BasicDEPSingleSplitter_ReturnValue_TestData
					{
						.leftParts
						{
							"Operand2",
							binaryOperator1,
							"Operand3"
						},
						.splitPart{ binaryOperator2 },
						.rightParts{ "Operand1" }
						
					}
				)
			}
		};
	}


	static std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>> makeValidSevenParts
	(
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator1,
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator2,
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator3
	)
	{
		return std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>>
		{
			std::move(makeOperandPart("Operand1")),
			std::move(makeOperatorPart(binaryOperator1)),
			std::move(makeOperandPart("Operand2")),
			std::move(makeOperatorPart(binaryOperator2)),
			std::move(makeOperandPart("Operand3")),
			std::move(makeOperatorPart(binaryOperator3)),
			std::move(makeOperandPart("Operand4"))
		};
	}


	static BasicDEPSingleSplitter_TestData makeValidSevenPartBasicDEPSingleSplitter_TestData
	(
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator1,
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator2,
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator3,
		const int splitOn
	)
	{
		if (splitOn == 1)
		{
			return BasicDEPSingleSplitter_TestData
			{
				.parts{ makeValidSevenParts(binaryOperator1, binaryOperator2, binaryOperator3) },
				.expectedSplitResult
				{
					std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
					(
						BasicDEPSingleSplitter_ReturnValue_TestData
						{
							.leftParts{ "Operand1" },
							.splitPart{ binaryOperator1 },
							.rightParts
							{
								"Operand2",
								binaryOperator2,
								"Operand3",
								binaryOperator3,
								"Operand4"
							}
						}
					)
				}
			};
		}

		if (splitOn == 2)
		{
			return BasicDEPSingleSplitter_TestData
			{
				.parts{ makeValidSevenParts(binaryOperator1, binaryOperator2, binaryOperator3) },
				.expectedSplitResult
				{
					std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
					(
						BasicDEPSingleSplitter_ReturnValue_TestData
						{
							.leftParts
							{
								"Operand1",
								binaryOperator1,
								"Operand2"
							},
							.splitPart{ binaryOperator2 },
							.rightParts
							{
								"Operand3",
								binaryOperator3,
								"Operand4"
							}
						}
					)
				}
			};
		}

		assert(splitOn == 3);
		return BasicDEPSingleSplitter_TestData
		{
			.parts{ makeValidSevenParts(binaryOperator1, binaryOperator2, binaryOperator3) },
			.expectedSplitResult
			{
				std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
				(
					BasicDEPSingleSplitter_ReturnValue_TestData
					{
						.leftParts
						{
							"Operand1",
							binaryOperator1,
							"Operand2",
							"Operand3",
							binaryOperator3,
						},
						.splitPart{ binaryOperator3 },
						.rightParts
						{
							"Operand4"
						}
					}
				)
			}
		};
	}


	const std::ranges::forward_range auto BasicDEPSingleSplitter_TestDataValues
	{
		[]()
		{
			std::vector<BasicDEPSingleSplitter_TestData> values
			{
#pragma region No parts
				{
					.parts{},
					.expectedSplitResult{}
				},
#pragma endregion
#pragma region One part
				{
					.parts
					{
						std::move(makeOperandPart("Operand"))
					},
					.expectedSplitResult
					{
						std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
						(
							BasicDEPSingleSplitter_ReturnValue_TestData
							{
								.leftParts{},
								.splitPart{ "Operand" },
								.rightParts{}
							}
						)
					}
				},
				{
					.parts
					{
						std::move(makeOperandPart("AnotherOperandWithADifferentValue"))
					},
					.expectedSplitResult
					{
						std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
						(
							BasicDEPSingleSplitter_ReturnValue_TestData
							{
								.leftParts{},
								.splitPart{ "AnotherOperandWithADifferentValue" },
								.rightParts{}
							}
						)
					}
				},
				{
					.parts
					{
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition))
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Multiplication))
					},
					.expectedSplitResult{}
				},
#pragma endregion
#pragma region Two parts
				{
					.parts
					{
						std::move(makeOperandPart("Operand1")),
						std::move(makeOperandPart("Operand2"))
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						std::move(makeOperandPart("Operand")),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition))
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition)),
						std::move(makeOperandPart("Operand"))
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition)),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition))
					},
					.expectedSplitResult{}
				},
#pragma endregion
#pragma region Three parts
				{
					.parts
					{
						std::move(makeOperandPart("Operand1")),
						std::move(makeOperandPart("Operand2")),
						std::move(makeOperandPart("Operand3"))
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						std::move(makeOperandPart("Operand1")),
						std::move(makeOperandPart("Operand2")),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition))
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						std::move(makeOperandPart("Operand1")),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition)),
						std::move(makeOperandPart("Operand2"))
					},
					.expectedSplitResult
					{
						std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
						(
							BasicDEPSingleSplitter_ReturnValue_TestData
							{
								.leftParts{ "Operand1" },
								.splitPart{ CmdCalculator::MathAst::EBinaryOperator::Addition },
								.rightParts{ "Operand2" }
							}
						)
					}
				},
				{
					.parts
					{
						std::move(makeOperandPart("Operand")),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition)),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition))
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition)),
						std::move(makeOperandPart("Operand1")),
						std::move(makeOperandPart("Operand2"))
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition)),
						std::move(makeOperandPart("Operand")),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition))
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition)),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition)),
						std::move(makeOperandPart("Operand"))
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition)),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition)),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition))
					},
					.expectedSplitResult{}
				},
#pragma endregion
#pragma region Valid three-part expression
				{
					.parts
					{
						std::move(makeOperandPart("Operand1")),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Addition)),
						std::move(makeOperandPart("Operand2"))
					},
					.expectedSplitResult
					{
						std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
						(
							BasicDEPSingleSplitter_ReturnValue_TestData
							{
								.leftParts{ "Operand1" },
								.splitPart{ CmdCalculator::MathAst::EBinaryOperator::Addition },
								.rightParts{ "Operand2" }
							}
						)
					}
				},
				{
					.parts
					{
						std::move(makeOperandPart("Operand1")),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Subtraction)),
						std::move(makeOperandPart("Operand2"))
					},
					.expectedSplitResult
					{
						std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
						(
							BasicDEPSingleSplitter_ReturnValue_TestData
							{
								.leftParts{ "Operand1" },
								.splitPart{ CmdCalculator::MathAst::EBinaryOperator::Subtraction },
								.rightParts{ "Operand2" }
							}
						)
					}
				},
				{
					.parts
					{
						std::move(makeOperandPart("Operand1")),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Multiplication)),
						std::move(makeOperandPart("Operand2"))
					},
					.expectedSplitResult
					{
						std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
						(
							BasicDEPSingleSplitter_ReturnValue_TestData
							{
								.leftParts{ "Operand1" },
								.splitPart{ CmdCalculator::MathAst::EBinaryOperator::Multiplication },
								.rightParts{ "Operand2" }
							}
						)
					}
				},
				{
					.parts
					{
						std::move(makeOperandPart("Operand1")),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Division)),
						std::move(makeOperandPart("Operand2"))
					},
					.expectedSplitResult
					{
						std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
						(
							BasicDEPSingleSplitter_ReturnValue_TestData
							{
								.leftParts{ "Operand1" },
								.splitPart{ CmdCalculator::MathAst::EBinaryOperator::Division },
								.rightParts{ "Operand2" }
							}
						)
					}
				},
				{
					.parts
					{
						std::move(makeOperandPart("Operand1")),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Exponentiation)),
						std::move(makeOperandPart("Operand2"))
					},
					.expectedSplitResult
					{
						std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
						(
							BasicDEPSingleSplitter_ReturnValue_TestData
							{
								.leftParts{ "Operand1" },
								.splitPart{ CmdCalculator::MathAst::EBinaryOperator::Exponentiation },
								.rightParts{ "Operand2" }
							}
						)
					}
				},
				{
					.parts
					{
						std::move(makeOperandPart("Operand1")),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::NthRoot)),
						std::move(makeOperandPart("Operand2"))
					},
					.expectedSplitResult
					{
						std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
						(
							BasicDEPSingleSplitter_ReturnValue_TestData
							{
								.leftParts{ "Operand1" },
								.splitPart{ CmdCalculator::MathAst::EBinaryOperator::NthRoot },
								.rightParts{ "Operand2" }
							}
						)
					}
				},
				{
					.parts
					{
						std::move(makeOperandPart("Operand1")),
						std::move(makeOperatorPart(CmdCalculator::MathAst::EBinaryOperator::Modulo)),
						std::move(makeOperandPart("Operand2"))
					},
					.expectedSplitResult
					{
						std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
						(
							BasicDEPSingleSplitter_ReturnValue_TestData
							{
								.leftParts{ "Operand1" },
								.splitPart{ CmdCalculator::MathAst::EBinaryOperator::Modulo },
								.rightParts{ "Operand2" }
							}
						)
					}
				}
#pragma endregion
			};

			for (const std::integral auto binaryOperator1Level : CmdCalculatorTestUtils::SharedTestData::binaryOperatorPrecedenceLevels) {
			for (const CmdCalculator::MathAst::EBinaryOperator binaryOperator1 : CmdCalculatorTestUtils::SharedTestData::getBinaryOperatorsAtPrecedenceLevel(binaryOperator1Level)) {
			for (const std::integral auto binaryOperator2Level : CmdCalculatorTestUtils::SharedTestData::binaryOperatorPrecedenceLevels) {
			for (const CmdCalculator::MathAst::EBinaryOperator binaryOperator2 : CmdCalculatorTestUtils::SharedTestData::getBinaryOperatorsAtPrecedenceLevel(binaryOperator1Level))
			{
				values.push_back
				(
					makeValidFivePartBasicDEPSingleSplitter_TestData
					(
						binaryOperator1,
						binaryOperator2,
						binaryOperator1Level < binaryOperator2Level
					)
				);
			}}}}

			for (const std::integral auto binaryOperator1Level : CmdCalculatorTestUtils::SharedTestData::binaryOperatorPrecedenceLevels) {
			for (const CmdCalculator::MathAst::EBinaryOperator binaryOperator1 : CmdCalculatorTestUtils::SharedTestData::getBinaryOperatorsAtPrecedenceLevel(binaryOperator1Level)) {
			for (const std::integral auto binaryOperator2Level : CmdCalculatorTestUtils::SharedTestData::binaryOperatorPrecedenceLevels) {
			for (const CmdCalculator::MathAst::EBinaryOperator binaryOperator2 : CmdCalculatorTestUtils::SharedTestData::getBinaryOperatorsAtPrecedenceLevel(binaryOperator1Level)) {
			for (const std::integral auto binaryOperator3Level : CmdCalculatorTestUtils::SharedTestData::binaryOperatorPrecedenceLevels) {
			for (const CmdCalculator::MathAst::EBinaryOperator binaryOperator3 : CmdCalculatorTestUtils::SharedTestData::getBinaryOperatorsAtPrecedenceLevel(binaryOperator1Level))
			{
				values.push_back
				(
					makeValidSevenPartBasicDEPSingleSplitter_TestData
					(
						binaryOperator1,
						binaryOperator2,
						binaryOperator3,
						binaryOperator1Level < binaryOperator2Level
							? binaryOperator1Level < binaryOperator3Level
								? 1
								: 3
							: binaryOperator1Level < binaryOperator3Level
								? 2
								: binaryOperator2Level < binaryOperator3Level
									? 2
									: 3
					)
				);
			}}}}}}

			return values;
		}()
	};

#pragma endregion


#pragma region canSplit



#pragma endregion
}