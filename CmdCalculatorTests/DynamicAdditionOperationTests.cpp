#include "pch.h"

#include <string>

#include "../CmdCalculatorTestUtils/common.h"
#include "../CmdCalculator/DynamicAdditionOperation.h"
#include "../CmdCalculator/Expression.h"
#include "../CmdCalculatorTestDoubles/StubDynamicExpression.h"
#include "../CmdCalculatorTestDoubles/FakeRealNumber.h"

namespace CmdCalculatorTests
{
#pragma region Concept satisfaction

	TEST(DynamicAdditionOperationTests, DynamicAdditionOperation$satisfies$Expression$concept)
	{
		static_assert
		(
			CmdCalculator::Expressions::Expression
			<
				CmdCalculator::Expressions::DynamicAdditionOperation
				<
					CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber
				>
			>
		);
	}

#pragma endregion


#pragma region Test data setup

	struct DynamicAdditionOperation_TestData
	{
		using NumberType = CmdCalculatorTestDoubles::Arithmetic::FakeRealNumber;
		using OperandType = CmdCalculatorTestDoubles::Expressions::StubDynamicExpression<NumberType>;

		OperandType augend;
		OperandType addend;
		double expectedAugendEvaluation;
		double expectedAddendEvaluation;
		double expectedEvaluation;

		DynamicAdditionOperation_TestData(const double augend, const double addend, const double evaluation) :
			augend{ DynamicAdditionOperation_TestData::NumberType{ augend } },
			addend{ DynamicAdditionOperation_TestData::NumberType{ addend } },
			expectedAugendEvaluation{ augend },
			expectedAddendEvaluation{ addend },
			expectedEvaluation{ evaluation }
		{}


		friend std::ostream& operator<<(std::ostream & ostream, const DynamicAdditionOperation_TestData & testData)
		{
			ostream
				<< '['
				<< testData.augend.evaluation.FAKE_getValue()
				<< " + "
				<< testData.addend.evaluation.FAKE_getValue()
				<< " == {"
				<< testData.expectedAugendEvaluation
				<< '+'
				<< testData.expectedAddendEvaluation
				<< '='
				<< testData.expectedEvaluation
				<< "}]"
			;

			return ostream;
		}
	};

	class DynamicAdditionOperationWithTestDataTests :
		public testing::TestWithParam<DynamicAdditionOperation_TestData>
	{};

	const auto DynamicAdditionOperation_TestDataValues
	{
		CmdCalculatorTestUtils::SharedTestData::additionOperationsDataValues
		| std::views::transform
		(
			[](const auto& data)
			{
				return DynamicAdditionOperation_TestData
				{
					data.leftOperand,
					data.rightOperand,
					data.result
				};
			}
		)
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicAdditionOperationTests,
		DynamicAdditionOperationWithTestDataTests,
		CmdCalculatorTestUtils::ValuesInRange(DynamicAdditionOperation_TestDataValues)
	);

#pragma endregion


#pragma region Expected state

	TEST_P(DynamicAdditionOperationWithTestDataTests, DynamicAdditionOperation$has$expected$state)
	{
		// Arrange
		using NumberType = DynamicAdditionOperation_TestData::NumberType;
		using OperandType = DynamicAdditionOperation_TestData::OperandType;

		auto augendToPass{ std::make_unique<OperandType>(GetParam().augend) };
		auto addendToPass{ std::make_unique<OperandType>(GetParam().addend) };

		const double expectedAugendEvaluation{ GetParam().expectedAugendEvaluation };
		const double expectedAddendEvaluation{ GetParam().expectedAddendEvaluation };
		const double expectedEvaluation{ GetParam().expectedEvaluation };
		
		// Act
		CmdCalculator::Expressions::DynamicAdditionOperation<NumberType> instance
		{
			std::move(augendToPass),
			std::move(addendToPass)
		};

		// Assert
		EXPECT_DOUBLE_EQ(expectedAugendEvaluation, instance.getAugend().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedAddendEvaluation, instance.getAddend().getEvaluation().FAKE_getValue());
		EXPECT_DOUBLE_EQ(expectedEvaluation, instance.getEvaluation().FAKE_getValue());
	}

#pragma endregion
}