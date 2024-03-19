#pragma once

#include <concepts>
#include <type_traits>
#include <optional>
#include <memory>
#include <vector>

#include "NotImplementedException.h"

namespace CmdCalculator
{
	/// \brief Describes a type that is intended to satisfy a given concept.
	/// \tparam SatisfierT The type that is intended to satisfy the concept.
	/// \tparam ConceptMarkerT A marker class that represents the concept to be satisfied.
	template<class SatisfierT, class ConceptMarkerT>
	concept IntendsToSatisfy = std::convertible_to<SatisfierT*, ConceptMarkerT*>;


	template<class T>
	concept CopyButNotMoveConstructible =
		std::copy_constructible<T>
		&& !std::move_constructible<T>
	;


	// TODO: moveToUniquePtr would probably be better as a customization point object.
	/// \brief Moves a value into a unique pointer.
	/// \tparam T The type of the value to move.
	/// \param value The value to move.
	/// \returns A unique pointer instance that owns \p value.
	template<std::move_constructible T>
	std::unique_ptr<std::remove_reference_t<T>> moveToUniquePtr(T&& value)
	{
		return std::make_unique<std::remove_reference_t<T>>(std::move(value));
	}


	/// \brief Moves a value into a unique pointer.
	/// \tparam T The type of the value to move.
	/// \param value The value to move.
	/// \returns A unique pointer instance that owns \p value.
	template<CopyButNotMoveConstructible T>
	std::unique_ptr<std::remove_reference_t<T>> moveToUniquePtr(T&& value)
	{
		return std::make_unique<T>(value);
	}


	/// \brief Describes any type that may be moved into a unique pointer.
	/// \tparam The type of value to move into a unique pointer.
	template<class T>
	concept MovableToUniquePtr =
		requires(T&& instance)
		{
			{ ::CmdCalculator::moveToUniquePtr(instance) } ->
				std::same_as<std::unique_ptr<std::remove_reference_t<T>>>
			;
		}
	;


	/// \brief Describes any type that is \ref std::optional.
	/// \tparam T The optional type.
	template<class T>
	concept Optional = std::same_as<std::remove_cv_t<T>, std::optional<typename T::value_type>>;

	
	template<Optional OptionalT>
	using OptionalValueType = OptionalT::value_type;


	/// \brief Describes any type that is \ref std::unqiue_ptr.
	/// \tparam T The unique pointer type.
	template<class T>
	concept UniquePtr = std::same_as<T, std::unique_ptr<typename T::element_type>>;


	/// \brief Describes any type that is \ref std::shared_ptr.
	/// \tparam T The shared pointer type.
	template<class T>
	concept SharedPtr = std::same_as<T, std::shared_ptr<typename T::element_type>>;


	/// \brief Describes any type that is \ref std::weak_ptr.
	/// \tparam T The weak pointer type.
	template<class T>
	concept WeakPtr = std::same_as<T, std::weak_ptr<typename T::element_type>>;


	/// \brief Describes any type that is a smart pointer from the standard library.
	/// \tparam T The smart pointer type.
	template<class T>
	concept SmartPtr = UniquePtr<T> || SharedPtr<T> || WeakPtr<T>;


	template<SmartPtr SmartPtrT>
	using SmartPointedToType = SmartPtrT::element_type;
}