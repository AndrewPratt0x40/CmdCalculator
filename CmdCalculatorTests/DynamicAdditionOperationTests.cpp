#include "pch.h"

#include <string>

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

	const DynamicAdditionOperation_TestData DynamicAdditionOperation_TestDataValues[]
	{
		DynamicAdditionOperation_TestData{  0.0,  0.0,  0.0 },
		DynamicAdditionOperation_TestData{  0.0,  0.5,  0.5 },
		DynamicAdditionOperation_TestData{  0.0,  1.0,  1.0 },
		DynamicAdditionOperation_TestData{  0.0,  1.5,  1.5 },
		DynamicAdditionOperation_TestData{  0.0,  2.0,  2.0 },

		DynamicAdditionOperation_TestData{  0.5,  0.0,  0.5 },
		DynamicAdditionOperation_TestData{  0.5,  0.5,  1.0 },
		DynamicAdditionOperation_TestData{  0.5,  1.0,  1.5 },
		DynamicAdditionOperation_TestData{  0.5,  1.5,  2.0 },
		DynamicAdditionOperation_TestData{  0.5,  2.0,  2.5 },

		DynamicAdditionOperation_TestData{  1.0,  0.0,  1.0 },
		DynamicAdditionOperation_TestData{  1.0,  0.5,  1.5 },
		DynamicAdditionOperation_TestData{  1.0,  1.0,  2.0 },
		DynamicAdditionOperation_TestData{  1.0,  1.5,  2.5 },
		DynamicAdditionOperation_TestData{  1.0,  2.0,  3.0 },

		DynamicAdditionOperation_TestData{  1.5,  0.0,  1.5 },
		DynamicAdditionOperation_TestData{  1.5,  0.5,  2.0 },
		DynamicAdditionOperation_TestData{  1.5,  1.0,  2.5 },
		DynamicAdditionOperation_TestData{  1.5,  1.5,  3.0 },
		DynamicAdditionOperation_TestData{  1.5,  2.0,  3.5 },

		DynamicAdditionOperation_TestData{  2.0,  0.0,  2.0 },
		DynamicAdditionOperation_TestData{  2.0,  0.5,  2.5 },
		DynamicAdditionOperation_TestData{  2.0,  1.0,  3.0 },
		DynamicAdditionOperation_TestData{  2.0,  1.5,  3.5 },
		DynamicAdditionOperation_TestData{  2.0,  2.0,  4.0 },

		DynamicAdditionOperation_TestData{  12.34,  56.78,  69.12 },
		DynamicAdditionOperation_TestData{  56.78,  12.34,  69.12 },

		DynamicAdditionOperation_TestData{  12.34, -56.78, -44.44 },
		DynamicAdditionOperation_TestData{ -56.78,  12.34, -44.44 },

		DynamicAdditionOperation_TestData{ -12.34,  56.78,  44.44},
		DynamicAdditionOperation_TestData{  56.78, -12.34,  44.44},

		DynamicAdditionOperation_TestData{ -12.34, -56.78, -69.12},
		DynamicAdditionOperation_TestData{ -56.78, -12.34, -69.12}
	};

	INSTANTIATE_TEST_CASE_P
	(
		DynamicAdditionOperationTests,
		DynamicAdditionOperationWithTestDataTests,
		testing::ValuesIn(DynamicAdditionOperation_TestDataValues)
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