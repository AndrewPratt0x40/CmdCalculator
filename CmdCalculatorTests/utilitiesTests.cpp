#include "pch.h"

#include <concepts>
#include <optional>
#include <memory>
#include <utility>
#include <string>
#include <string_view>
#include <vector>
#include <span>

#include "common.h"
#include "..\CmdCalculator\NotImplementedException.h"
#include "..\CmdCalculator\utilities.h"

namespace CmdCalculatorTests
{
#pragma region Optional

	template<class OptionalT, bool shouldSatisfyT>
	struct Optional_TypeParams
	{
		using OptionalType = OptionalT;
		static constexpr bool shouldSatisfy{ shouldSatisfyT };
	};
	
	template<class T>
	class OptionalTests :
		public testing::Test
	{};

	using OptionalTests_Types = testing::Types
	<
		Optional_TypeParams<int, false>,
		Optional_TypeParams<int*, false>,
		Optional_TypeParams<std::string, false>,
		Optional_TypeParams<std::optional<int>, true>,
		Optional_TypeParams<std::optional<int*>, true>,
		Optional_TypeParams<std::optional<std::string>, true>,
		Optional_TypeParams<std::optional<std::optional<int>>, true>
	>;

	TYPED_TEST_CASE(OptionalTests, OptionalTests_Types);


	TYPED_TEST(OptionalTests, Only$expected$types$satisfy)
	{
		// Arrange
		const bool expectSatisfaction{ TypeParam::shouldSatisfy };
		const bool isSatisfactory{ CmdCalculator::Optional<TypeParam::OptionalType> };

		// Assert
		EXPECT_EQ(expectSatisfaction, isSatisfactory);
	}

#pragma endregion


#pragma region Dereferenceable

	template<class DereferenceableT, bool shouldSatisfyT>
	struct Dereferenceable_TypeParams
	{
		using DereferenceableType = DereferenceableT;
		static constexpr bool shouldSatisfy{ shouldSatisfyT };
	};

	template<class T>
	class DereferenceableTests :
		public testing::Test
	{};

	using DereferenceableTests_Types = testing::Types
	<
		Dereferenceable_TypeParams<int, false>,
		Dereferenceable_TypeParams<bool, false>,
		Dereferenceable_TypeParams<EmptyStruct, false>,
		Dereferenceable_TypeParams<int*, true>,
		Dereferenceable_TypeParams<bool*, true>,
		Dereferenceable_TypeParams<EmptyStruct*, true>,
		Dereferenceable_TypeParams<int**, true>,
		Dereferenceable_TypeParams<std::unique_ptr<int>, true>,
		Dereferenceable_TypeParams<std::optional<int>, true>,
		Dereferenceable_TypeParams<std::reference_wrapper<int>, true>,
		Dereferenceable_TypeParams<std::unique_ptr<int*>, true>
	>;

	TYPED_TEST_CASE(DereferenceableTests, DereferenceableTests_Types);


	TYPED_TEST(DereferenceableTests, Only$expected$types$satisfy)
	{
		// Arrange
		const bool expectSatisfaction{ TypeParam::shouldSatisfy };
		const bool isSatisfactory{ CmdCalculator::Dereferenceable<TypeParam::DereferenceableType> };

		// Assert
		EXPECT_EQ(expectSatisfaction, isSatisfactory);
	}

#pragma endregion


#pragma region DereferencedOptionalValueType

	template<class DereferenceableT, class ExpectedT>
	struct DereferencedType_TypeParams
	{
		using DereferenceableType = DereferenceableT;
		using ExpectedType = ExpectedT;
	};

	template<class T>
	class DereferencedTypeTests :
		public testing::Test
	{};

	using DereferencedTypeTests_Types = testing::Types
	<
		DereferencedType_TypeParams<int*, int>,
		DereferencedType_TypeParams<bool*, bool>,
		DereferencedType_TypeParams<EmptyStruct*, EmptyStruct>,
		DereferencedType_TypeParams<int**, int*>,
		DereferencedType_TypeParams<std::shared_ptr<int>, int>,
		DereferencedType_TypeParams<std::optional<int>, int>,
		DereferencedType_TypeParams<std::reference_wrapper<int>, int>,
		DereferencedType_TypeParams<std::shared_ptr<int*>, int*>,
		DereferencedType_TypeParams<std::shared_ptr<int>*, std::shared_ptr<int>>,
		DereferencedType_TypeParams<std::shared_ptr<int*>*, std::shared_ptr<int*>>
	>;

	TYPED_TEST_CASE(DereferencedTypeTests, DereferencedTypeTests_Types);


	TYPED_TEST(DereferencedTypeTests, DereferencedType$yields$dereferenced$type)
	{
		EXPECT_TRUE
		(
			false/*std::same_as
			<
				TypeParam::ExpectedType,
				CmdCalculator::DereferencedType<TypeParam::DereferenceableType>
			>*/
		);
	}

#pragma endregion


#pragma region RangeOfDereferenceableElements

	template<class RangeOfDereferenceableElementsT, bool shouldSatisfyT>
	struct RangeOfDereferenceableElements_TypeParams
	{
		using RangeOfDereferenceableElementsType = RangeOfDereferenceableElementsT;
		static constexpr bool shouldSatisfy{ shouldSatisfyT };
	};

	template<class T>
	class RangeOfDereferenceableElementsTests :
		public testing::Test
	{};

	using RangeOfDereferenceableElementsTests_Types = testing::Types
	<
		RangeOfDereferenceableElements_TypeParams<int, false>,
		RangeOfDereferenceableElements_TypeParams<bool, false>,
		RangeOfDereferenceableElements_TypeParams<EmptyStruct, false>,
		RangeOfDereferenceableElements_TypeParams<int*, false>,
		RangeOfDereferenceableElements_TypeParams<bool*, false>,
		RangeOfDereferenceableElements_TypeParams<EmptyStruct*, false>,
		RangeOfDereferenceableElements_TypeParams<int**, false>,
		RangeOfDereferenceableElements_TypeParams<std::unique_ptr<int>, false>,
		RangeOfDereferenceableElements_TypeParams<std::vector<int>, false>,
		RangeOfDereferenceableElements_TypeParams<std::span<int>, false>,
		RangeOfDereferenceableElements_TypeParams<std::vector<int*>, true>,
		RangeOfDereferenceableElements_TypeParams<std::span<int*>, true>,
		RangeOfDereferenceableElements_TypeParams<std::vector<std::unique_ptr<int>>, true>,
		RangeOfDereferenceableElements_TypeParams<std::vector<std::optional<int>>, true>,
		RangeOfDereferenceableElements_TypeParams<std::vector<std::reference_wrapper<int>>, true>
	>;

	TYPED_TEST_CASE(RangeOfDereferenceableElementsTests, RangeOfDereferenceableElementsTests_Types);


	TYPED_TEST(RangeOfDereferenceableElementsTests, Only$expected$types$satisfy)
	{
		// Arrange
		const bool expectSatisfaction{ TypeParam::shouldSatisfy };
		const bool isSatisfactory{ CmdCalculator::RangeOfDereferenceableElements<TypeParam::RangeOfDereferenceableElementsType> };

		// Assert
		EXPECT_EQ(expectSatisfaction, isSatisfactory);
	}

#pragma endregion


#pragma region DereferencedRangeElementType

	template<class RangeOfDereferenceableElementsT, class ExpectedT>
	struct DereferencedRangeElementType_TypeParams
	{
		using RangeOfDereferenceableElementsType = RangeOfDereferenceableElementsT;
		using ExpectedType = ExpectedT;
	};

	template<class T>
	class DereferencedRangeElementTypeTests :
		public testing::Test
	{};

	using DereferencedRangeElementTypeTests_Types = testing::Types
	<
		DereferencedRangeElementType_TypeParams<std::vector<int*>, int>,
		DereferencedRangeElementType_TypeParams<std::vector<bool*>, bool>,
		DereferencedRangeElementType_TypeParams<std::vector<EmptyStruct*>, bool>,
		DereferencedRangeElementType_TypeParams<std::span<int*>, int>,
		DereferencedRangeElementType_TypeParams<std::vector<std::unique_ptr<int>>, int>,
		DereferencedRangeElementType_TypeParams<std::vector<std::optional<int>>, int>,
		DereferencedRangeElementType_TypeParams<std::vector<std::reference_wrapper<int>>, int>,
		DereferencedRangeElementType_TypeParams<std::vector<std::unique_ptr<int*>>, int*>,
		DereferencedRangeElementType_TypeParams<std::vector<std::unique_ptr<int>>*, std::unique_ptr<int>>,
		DereferencedRangeElementType_TypeParams<std::vector<std::unique_ptr<int*>>*, std::unique_ptr<int*>>
	>;

	TYPED_TEST_CASE(DereferencedRangeElementTypeTests, DereferencedRangeElementTypeTests_Types);


	TYPED_TEST(DereferencedRangeElementTypeTests, DereferencedRangeElementType$yields$dereferenced$element$type)
	{
		EXPECT_TRUE
		(
			false/*std::same_as
			<
				TypeParam::ExpectedType,
				CmdCalculator::DereferencedRangeElementType<TypeParam::RangeOfDereferenceableElementsType>
			>*/
		);
	}

#pragma endregion


#pragma region pointerAsOptionalReference

#pragma region With nullptr

	template<class T>
	class pointerAsOptionalReferenceTests :
		public testing::Test
	{};

	using pointerAsOptionalReferenceTests_Types = testing::Types
	<
		int,
		EmptyStruct
	>;

	TYPED_TEST_CASE(pointerAsOptionalReferenceTests, pointerAsOptionalReferenceTests_Types);


	TYPED_TEST(pointerAsOptionalReferenceTests, Calling$pointerAsOptionalReference$with$nullptr$returns$empty$object)
	{
		// Arrange
		TypeParam* pointer{ nullptr };
		
		// Act
		std::optional<std::reference_wrapper<TypeParam>> returnValue{ CmdCalculator::pointerAsOptionalReference(pointer) };

		// Assert
		EXPECT_FALSE(returnValue.has_value());
	}


	TYPED_TEST(pointerAsOptionalReferenceTests, Calling$pointerAsOptionalConstReference$with$nullptr$returns$empty$object)
	{
		// Arrange
		TypeParam* pointer{ nullptr };

		// Act
		std::optional<std::reference_wrapper<const TypeParam>> returnValue{ CmdCalculator::pointerAsOptionalConstReference(pointer) };

		// Assert
		EXPECT_FALSE(returnValue.has_value());
	}


	TYPED_TEST(pointerAsOptionalReferenceTests, Calling$pointerAsOptionalReference$with$non$nullptr$returns$reference$to$pointed$to$value)
	{
		// Arrange
		ASSERT_TRUE(std::default_initializable<TypeParam>);

		TypeParam value{};
		TypeParam* pointer{ &value };
		
		// Act
		std::optional<std::reference_wrapper<TypeParam>> returnValue{ CmdCalculator::pointerAsOptionalReference(pointer) };

		// Assert
		EXPECT_TRUE(returnValue.has_value());
		EXPECT_EQ(pointer, &returnValue.value().get());
	}


	TYPED_TEST(pointerAsOptionalReferenceTests, Calling$pointerAsOptionalConstReference$with$non$nullptr$returns$reference$to$pointed$to$value)
	{
		// Arrange
		ASSERT_TRUE(std::default_initializable<TypeParam>);

		TypeParam value{};
		TypeParam* pointer{ &value };

		// Act
		std::optional<std::reference_wrapper<const TypeParam>> returnValue{ CmdCalculator::pointerAsOptionalConstReference(pointer) };

		// Assert
		EXPECT_TRUE(returnValue.has_value());
		EXPECT_EQ(pointer, &returnValue.value().get());
	}

#pragma endregion

#pragma endregion
}