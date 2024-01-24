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


	/// \brief Describes any type that is \ref std::optional.
	/// \tparam T The optional type.
	template<class T>
	concept Optional = std::same_as<T, std::optional<typename T::value_type>>;

	
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