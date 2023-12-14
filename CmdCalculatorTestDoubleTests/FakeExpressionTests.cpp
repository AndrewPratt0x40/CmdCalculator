#include "pch.h"

#include <string>
#include <initializer_list>
#include <ranges>
#include <algorithm>

#include "../CmdCalculator/NotImplementedException.h"
#include "../CmdCalculatorTestDoubles/FakeExpression.h"

namespace CmdCalculatorTestDoubleTests
{
#pragma region Fixture with type parameters

	template<std::regular IdentifierT, IdentifierT identifierValue_t, IdentifierT otherIdentifierValue_t>
	struct FakeExpressionTestData
	{
		using IdentifierType = IdentifierT;
		using FakeExpressionType = CmdCalculatorTestDoubles::Expressions::FakeExpression<IdentifierT>;

		static constexpr IdentifierT defaultIdentifierValue{};
		static constexpr IdentifierT identifierValue{ identifierValue_t };
		static constexpr IdentifierT otherIdentifierValue{ otherIdentifierValue_t };

		static_assert(defaultIdentifierValue != identifierValue);
		static_assert(defaultIdentifierValue != otherIdentifierValue);
		static_assert(identifierValue != otherIdentifierValue);
	};
	
	template<class T>
	class FakeExpressionWithTParamTests :
		public testing::Test
	{};

	using FakeExpressionWithTParamTests_Types = testing::Types
	<
		FakeExpressionTestData<int, 1, 2>,
		FakeExpressionTestData<char, 'x', 'y'>,
		FakeExpressionTestData<bool, false, true>
	>;

	TYPED_TEST_CASE(FakeExpressionWithTParamTests, FakeExpressionWithTParamTests_Types);

#pragma endregion


#pragma region Concept satisfaction

	TYPED_TEST(FakeExpressionWithTParamTests, FakeExpression$satisfies$Expression$concept)
	{
		EXPECT_TRUE(CmdCalculator::Expressions::Expression<typename TypeParam::FakeExpressionType>);
	}

#pragma endregion


#pragma region Constructors

#pragma region Default Constructor

	TEST(FakeExpressionTests, Default$constructor$sets$full$simplification$to$empty)
	{
		// Arrange
		CmdCalculatorTestDoubles::Expressions::FakeExpression instance{};

		// Assert
		EXPECT_FALSE(instance.FAKE_getFullSimplification().has_value());
	}

	TYPED_TEST(FakeExpressionWithTParamTests, Default$constructor$sets$identifier$to$default$value)
	{
		// Arrange
		typename TypeParam::FakeExpressionType instance{};

		// Assert
		EXPECT_EQ(TypeParam::defaultIdentifierValue, instance.FAKE_getIdentifer());
	}

#pragma endregion


#pragma region Constructor with one argument

	class FakeExpressionConstructorWithOneArgTests :
		public testing::TestWithParam<std::optional<CmdCalculatorTestDoubles::Expressions::FakeExpression<>>>
	{};
	
	TEST_P(FakeExpressionConstructorWithOneArgTests, Constructor$with$one$argument$sets$full$simplification)
	{
		// Arrange
		const auto& fullSimplification{ GetParam() };
		std::is_trivially_copy_constructible_v<decltype(fullSimplification.value())>;
		CmdCalculatorTestDoubles::Expressions::FakeExpression instance{ fullSimplification };

		// Assert
		EXPECT_EQ(instance.FAKE_getFullSimplification(), fullSimplification);
	}

	INSTANTIATE_TEST_CASE_P
	(
		FakeExpressionTests,
		FakeExpressionConstructorWithOneArgTests,
		testing::Values
		(
			std::optional<CmdCalculatorTestDoubles::Expressions::FakeExpression<int>>{},
			std::make_optional<CmdCalculatorTestDoubles::Expressions::FakeExpression<int>>()
		)
	);

	TYPED_TEST(FakeExpressionWithTParamTests, Constructor$with$one$argument$sets$identifier$to$default$value)
	{
		// Arrange
		typename TypeParam::FakeExpressionType instance{};

		// Assert
		EXPECT_EQ(TypeParam::defaultIdentifierValue, instance.FAKE_getIdentifer());
	}

#pragma endregion


#pragma region Constructor with two arguments

	class FakeExpressionConstructorWithTwoArgsTests :
		public testing::TestWithParam<std::pair<std::optional<CmdCalculatorTestDoubles::Expressions::FakeExpression<int>>, int>>
	{};

	INSTANTIATE_TEST_CASE_P
	(
		FakeExpressionTests,
		FakeExpressionConstructorWithTwoArgsTests,
		testing::Values
		(
			std::make_pair<std::optional<CmdCalculatorTestDoubles::Expressions::FakeExpression<int>>, int>
			(
				{},
				0
			),
			std::make_pair<std::optional<CmdCalculatorTestDoubles::Expressions::FakeExpression<int>>, int>
			(
				{},
				1
			),
			std::make_pair<std::optional<CmdCalculatorTestDoubles::Expressions::FakeExpression<int>>, int>
			(
				std::make_optional<CmdCalculatorTestDoubles::Expressions::FakeExpression<int>>(),
				0
			),
			std::make_pair<std::optional<CmdCalculatorTestDoubles::Expressions::FakeExpression<int>>, int>
			(
				std::make_optional<CmdCalculatorTestDoubles::Expressions::FakeExpression<int>>(),
				1
			)
		)
	);

	TEST_P(FakeExpressionConstructorWithTwoArgsTests, Constructor$with$two$arguments$sets$full$simplification)
	{
		// Arrange
		const auto& fullSimplification{ GetParam().first };
		const auto& identifier{ GetParam().second };
		CmdCalculatorTestDoubles::Expressions::FakeExpression instance{ fullSimplification, identifier };

		// Assert
		EXPECT_EQ(instance.FAKE_getFullSimplification(), fullSimplification);
	}

	TEST_P(FakeExpressionConstructorWithTwoArgsTests, Constructor$with$two$arguments$sets$identifier)
	{
		// Arrange
		const auto& fullSimplification{ GetParam().first };
		const auto& identifier{ GetParam().second };
		CmdCalculatorTestDoubles::Expressions::FakeExpression instance{ fullSimplification, identifier };

		// Assert
		EXPECT_EQ(instance.FAKE_getIdentifier(), identifier);
	}

#pragma endregion

#pragma endregion
}