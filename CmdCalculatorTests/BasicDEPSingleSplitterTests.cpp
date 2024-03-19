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
		std::function
		<
			std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>>()
		> parts;
		std::optional<BasicDEPSingleSplitter_ReturnValue_TestData> expectedSplitResult;


		static std::string stringifyExpectedPart(const BasicDEPSingleSplitter_ReturnValue_TestData::PartType& part)
		{
			const std::string* partAsStr{ std::get_if<std::string>(&part) };
			if (partAsStr)
				return *partAsStr;
			return CmdCalculatorTestUtils::getBinaryOperatorName(std::get<CmdCalculator::MathAst::EBinaryOperator>(part));
		}
		
		
		static std::string stringifyExpectedPartsRange(const std::vector<BasicDEPSingleSplitter_ReturnValue_TestData::PartType>& parts)
		{
			return CmdCalculatorTestUtils::joinStrings
			(
				parts
				| std::views::transform
				(
					[](const BasicDEPSingleSplitter_ReturnValue_TestData::PartType& part)
					{ return stringifyExpectedPart(part); }
				)
			);
		}

		
		friend std::ostream& operator<<
		(
			std::ostream& ostream,
			const BasicDEPSingleSplitter_TestData& testData
		)
		{
			const auto parts{ testData.parts() };

			ostream
				<< "BasicDEPSingleSplitter.tryToSplit("
				<< CmdCalculatorTestUtils::joinStrings
				(
					parts
					| std::views::transform
					(
						[](const std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>& part)
						{ return part->getStringRepresentation(); }
					)
				)
				<< ") = {"
			;

			if (testData.expectedSplitResult.has_value())
			{
				ostream
					<< stringifyExpectedPartsRange(testData.expectedSplitResult.value().leftParts)
					<< '<'
					<< stringifyExpectedPart(testData.expectedSplitResult.value().splitPart)
					<< '>'
					<< stringifyExpectedPartsRange(testData.expectedSplitResult.value().rightParts)
				;
			}

			ostream << '}';
			return ostream;
		}
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


	static std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>> makePart(const BasicDEPSingleSplitter_ReturnValue_TestData::PartType& part)
	{
		const std::string* partAsStr{ std::get_if<std::string>(&part) };
		if (partAsStr)
			return makeOperandPart(*partAsStr);
		return makeOperatorPart(std::get<CmdCalculator::MathAst::EBinaryOperator>(part));
	}


	static std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>> makeParts
	(
		const std::initializer_list<BasicDEPSingleSplitter_ReturnValue_TestData::PartType> parts
	)
	{
		return CmdCalculatorTestUtils::moveRangeToVector
		(
			parts
			| std::views::transform
			(
				[](const BasicDEPSingleSplitter_ReturnValue_TestData::PartType& part)
				{ return makePart(part); }
			)
		);
	}


	static std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>> makeValidThreeParts
	(
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator
	)
	{
		return makeParts
		({
			"Operand1",
			binaryOperator,
			"Operand2"
		});
	}


	static BasicDEPSingleSplitter_TestData makeValidThreePartBasicDEPSingleSplitter_TestData
	(
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator
	)
	{
		return BasicDEPSingleSplitter_TestData
		{
			.parts{ [binaryOperator]() { return makeValidThreeParts(binaryOperator); } },
			.expectedSplitResult
			{
				std::make_optional<BasicDEPSingleSplitter_ReturnValue_TestData>
				(
					BasicDEPSingleSplitter_ReturnValue_TestData
					{
						.leftParts{ "Operand1" },
						.splitPart{ binaryOperator },
						.rightParts{ "Operand2" }
						
					}
				)
			}
		};
	}


	static std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>> makeValidFiveParts
	(
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator1,
		const CmdCalculator::MathAst::EBinaryOperator binaryOperator2
	)
	{
		return makeParts
		({
			"Operand1",
			binaryOperator1,
			"Operand2",
			binaryOperator2,
			"Operand3"
		});
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
				.parts{ [binaryOperator1, binaryOperator2]() { return makeValidFiveParts(binaryOperator1, binaryOperator2); } },
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
			.parts{ [binaryOperator1, binaryOperator2]() { return makeValidFiveParts(binaryOperator1, binaryOperator2); } },
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
						.rightParts{ "Operand3" }
						
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
		return makeParts
		({
			"Operand1",
			binaryOperator1,
			"Operand2",
			binaryOperator2,
			"Operand3",
			binaryOperator3,
			"Operand4"
			});
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
				.parts
				{
					[binaryOperator1, binaryOperator2, binaryOperator3]()
					{ return makeValidSevenParts(binaryOperator1, binaryOperator2, binaryOperator3); }
				},
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
				.parts
				{
					[binaryOperator1, binaryOperator2, binaryOperator3]()
					{ return makeValidSevenParts(binaryOperator1, binaryOperator2, binaryOperator3); }
				},
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
			.parts
			{
				[binaryOperator1, binaryOperator2, binaryOperator3]()
				{ return makeValidSevenParts(binaryOperator1, binaryOperator2, binaryOperator3); }
			},
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
							binaryOperator2,
							"Operand3"
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
					.parts
					{
						[]()
						{
							return makeParts({});
						}
					},
					.expectedSplitResult{}
				},
#pragma endregion
#pragma region One part
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								"Operand"
							});
						}
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
						[]()
						{
							return makeParts
							({
								"AnotherOperandWithADifferentValue"
							});
						}
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
						[]()
						{
							return makeParts
							({
								CmdCalculator::MathAst::EBinaryOperator::Addition
							});
						}
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								CmdCalculator::MathAst::EBinaryOperator::Multiplication
							});
						}
					},
					.expectedSplitResult{}
				},
#pragma endregion
#pragma region Two parts
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								"Operand1",
								"Operand2"
							});
						}
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								"Operand",
								CmdCalculator::MathAst::EBinaryOperator::Addition
							});
						}
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								CmdCalculator::MathAst::EBinaryOperator::Addition,
								"Operand"
							});
						}
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								CmdCalculator::MathAst::EBinaryOperator::Addition,
								CmdCalculator::MathAst::EBinaryOperator::Addition
							});
						}
					},
					.expectedSplitResult{}
				},
#pragma endregion
#pragma region Three parts
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								"Operand1",
								"Operand2",
								"Operand3"
							});
						}
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								"Operand1",
								"Operand2",
								CmdCalculator::MathAst::EBinaryOperator::Addition
							});
						}
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								"Operand1",
								CmdCalculator::MathAst::EBinaryOperator::Addition,
								"Operand2"
							});
						}
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
						[]()
						{
							return makeParts
							({
								"Operand",
								CmdCalculator::MathAst::EBinaryOperator::Addition,
								CmdCalculator::MathAst::EBinaryOperator::Addition
							});
						}
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								CmdCalculator::MathAst::EBinaryOperator::Addition,
								"Operand1",
								"Operand2"
							});
						}
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								CmdCalculator::MathAst::EBinaryOperator::Addition,
								"Operand",
								CmdCalculator::MathAst::EBinaryOperator::Addition
							});
						}
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								CmdCalculator::MathAst::EBinaryOperator::Addition,
								CmdCalculator::MathAst::EBinaryOperator::Addition,
								"Operand"
							});
						}
					},
					.expectedSplitResult{}
				},
				{
					.parts
					{
						[]()
						{
							return makeParts
							({
								CmdCalculator::MathAst::EBinaryOperator::Addition,
								CmdCalculator::MathAst::EBinaryOperator::Addition,
								CmdCalculator::MathAst::EBinaryOperator::Addition
							});
						}
					},
					.expectedSplitResult{}
				}
#pragma endregion
			};

			for (const CmdCalculator::MathAst::EBinaryOperator binaryOperator : CmdCalculatorTestUtils::SharedTestData::binaryOperators)
			{
				values.push_back
				(
					makeValidThreePartBasicDEPSingleSplitter_TestData(binaryOperator)
				);
			}

			for (const CmdCalculatorTestUtils::SharedTestData::BinaryOperatorData binaryOperator1 : CmdCalculatorTestUtils::SharedTestData::binaryOperatorDataValues) {
			for (const CmdCalculatorTestUtils::SharedTestData::BinaryOperatorData binaryOperator2 : CmdCalculatorTestUtils::SharedTestData::binaryOperatorDataValues)
			{
				values.push_back
				(
					makeValidFivePartBasicDEPSingleSplitter_TestData
					(
						binaryOperator1.binaryOperator,
						binaryOperator2.binaryOperator,
						binaryOperator1.precedenceLevel < binaryOperator2.precedenceLevel
					)
				);
			}}

			for (const CmdCalculatorTestUtils::SharedTestData::BinaryOperatorData binaryOperator1 : CmdCalculatorTestUtils::SharedTestData::binaryOperatorDataValues) {
			for (const CmdCalculatorTestUtils::SharedTestData::BinaryOperatorData binaryOperator2 : CmdCalculatorTestUtils::SharedTestData::binaryOperatorDataValues) {
			for (const CmdCalculatorTestUtils::SharedTestData::BinaryOperatorData binaryOperator3 : CmdCalculatorTestUtils::SharedTestData::binaryOperatorDataValues)
			{
				values.push_back
				(
					makeValidSevenPartBasicDEPSingleSplitter_TestData
					(
						binaryOperator1.binaryOperator,
						binaryOperator2.binaryOperator,
						binaryOperator3.binaryOperator,
						binaryOperator1.precedenceLevel < binaryOperator2.precedenceLevel
							? binaryOperator1.precedenceLevel < binaryOperator3.precedenceLevel
								? 1
								: 3
							: binaryOperator1.precedenceLevel < binaryOperator3.precedenceLevel
								? 2
								: binaryOperator2.precedenceLevel < binaryOperator3.precedenceLevel
									? 2
									: 3
					)
				);
			}}}

			return values;
		}()
	};

#pragma endregion


#pragma region canSplit

	class BasicDEPSingleSplitter$canSplit$Tests :
		public testing::TestWithParam<BasicDEPSingleSplitter_TestData>
	{};

	INSTANTIATE_TEST_CASE_P
	(
		BasicDEPSingleSplitterTests,
		BasicDEPSingleSplitter$canSplit$Tests,
		testing::ValuesIn(BasicDEPSingleSplitter_TestDataValues)
	);

	TEST_P(BasicDEPSingleSplitter$canSplit$Tests, canSplit$returns$true$IFF$given$parts$are$valid)
	{
		// Arrange
		const std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>> parts
		{
			std::move(GetParam().parts())
		};
		const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto partRefsView
		{
			parts
			| std::views::transform
			(
				[](const std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>& part)
				{ return std::ref(*part); }
			)
		};
		const CmdCalculator::BasicDEPSingleSplitter<std::string> instance{};
		const bool expected{ GetParam().expectedSplitResult.has_value() };

		// Act
		const bool actual{ instance.canSplit(partRefsView | std::views::all) };

		// Assert
		EXPECT_EQ(expected, actual);
	}

#pragma endregion


#pragma region tryToSplit

	class BasicDEPSingleSplitter$tryToSplit$Tests :
		public testing::TestWithParam<BasicDEPSingleSplitter_TestData>
	{};

	INSTANTIATE_TEST_CASE_P
	(
		BasicDEPSingleSplitterTests,
		BasicDEPSingleSplitter$tryToSplit$Tests,
		testing::ValuesIn(BasicDEPSingleSplitter_TestDataValues)
	);

	TEST_P(BasicDEPSingleSplitter$tryToSplit$Tests, tryToSplit$returns$expected$value)
	{
		// Arrange
		const auto doesActualPartEqualExpected
		{
			[]
			(
				const BasicDEPSingleSplitter_ReturnValue_TestData::PartType& expected,
				const CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>& actual
			) -> bool
			{
				const std::string* expectedAsStr{ std::get_if<std::string>(&expected) };
				if (expectedAsStr)
					return actual.getStringRepresentation() == *expectedAsStr;

				if (!actual.isBinaryOperator())
					return false;

				return
					reinterpret_cast<const CmdCalculator::MathAst::DynamicBinaryOperatorNode<std::string>&>
						(actual).getOperatorKind()
					== std::get<CmdCalculator::MathAst::EBinaryOperator>(expected)
				;
			}
		};

		const std::vector<std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>> parts
		{
			std::move(GetParam().parts())
		};

		const CmdCalculator::MathAst::DynamicExpressionPartNodeRange<std::string> auto partRefsView
		{
			parts
			| std::views::transform
			(
				[](const std::unique_ptr<CmdCalculator::MathAst::DynamicExpressionPartNode<std::string>>& part)
				{ return std::ref(*part); }
			)
		};
		const CmdCalculator::BasicDEPSingleSplitter<std::string> instance{};
		const CmdCalculator::Optional auto expectedResultData{ GetParam().expectedSplitResult };

		// Act
		const CmdCalculator::Optional auto actual{ instance.tryToSplit(partRefsView | std::views::all) };

		// Assert
		EXPECT_EQ(expectedResultData.has_value(), actual.has_value());
		if (expectedResultData.has_value())
		{
			EXPECT_EQ
			(
				expectedResultData.value().leftParts.size(),
				std::ranges::size(actual.value().getLeftParts())
			);
			EXPECT_TRUE
			(
				std::ranges::equal
				(
					expectedResultData.value().leftParts,
					actual.value().getLeftParts(),
					doesActualPartEqualExpected
				)
			);

			EXPECT_TRUE
			(
				doesActualPartEqualExpected
				(
					expectedResultData.value().splitPart,
					actual.value().getSplitPart()
				)
			);

			EXPECT_EQ
			(
				expectedResultData.value().rightParts.size(),
				std::ranges::size(actual.value().getRightParts())
			);
			EXPECT_TRUE
			(
				std::ranges::equal
				(
					expectedResultData.value().rightParts,
					actual.value().getRightParts(),
					doesActualPartEqualExpected
				)
			);
		}
	}

#pragma endregion
}