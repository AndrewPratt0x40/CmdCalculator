#pragma once

#include <concepts>
#include <string>

#include "RealNumber.h"

namespace CmdCalculator::Arithmetic
{
#pragma region Non-member forward declarations

	template<std::floating_point InnerT>
	class FundamentallyBackedRealNumber;

#pragma push_macro("THIS_INNER_TYPE")
#define THIS_INNER_TYPE CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::InnerType
#pragma push_macro("THIS_INNER_TYPENAME")
#define THIS_INNER_TYPENAME typename THIS_INNER_TYPE
#pragma push_macro("THIS_TYPE")
#define THIS_TYPE CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<THIS_INNER_TYPENAME>

#pragma region Comparison operators

	template<std::floating_point InnerT>
	bool operator==(const THIS_TYPE& lhs, const THIS_TYPE& rhs);

	template<std::floating_point InnerT>
	bool operator!=(const THIS_TYPE& lhs, const THIS_TYPE& rhs);

	template<std::floating_point InnerT>
	bool operator<(const THIS_TYPE& lhs, const THIS_TYPE& rhs);

	template<std::floating_point InnerT>
	bool operator<=(const THIS_TYPE& lhs, const THIS_TYPE& rhs);

	template<std::floating_point InnerT>
	bool operator>(const THIS_TYPE& lhs, const THIS_TYPE& rhs);

	template<std::floating_point InnerT>
	bool operator>=(const THIS_TYPE& lhs, const THIS_TYPE& rhs);

#pragma endregion


#pragma region Unary arithmetic operators

	template<std::floating_point InnerT>
	FundamentallyBackedRealNumber<THIS_INNER_TYPENAME>& operator-(const THIS_TYPE& rhs);

#pragma endregion


#pragma region Binary arithmetic operations

	template<std::floating_point InnerT>
	FundamentallyBackedRealNumber<THIS_INNER_TYPENAME> operator+(const THIS_TYPE& lhs, const THIS_TYPE& rhs);

	template<std::floating_point InnerT>
	FundamentallyBackedRealNumber<THIS_INNER_TYPENAME> operator-(const THIS_TYPE& lhs, const THIS_TYPE& rhs);
	
	template<std::floating_point InnerT>
	FundamentallyBackedRealNumber<THIS_INNER_TYPENAME> operator*(const THIS_TYPE& lhs, const THIS_TYPE& rhs);

	template<std::floating_point InnerT>
	FundamentallyBackedRealNumber<THIS_INNER_TYPENAME> operator/(const THIS_TYPE& lhs, const THIS_TYPE& rhs);

	template<std::floating_point InnerT>
	FundamentallyBackedRealNumber<THIS_INNER_TYPENAME> operator%(const THIS_TYPE& lhs, const THIS_TYPE& rhs);

#pragma endregion

#pragma pop_macro("THIS_TYPE")
#pragma pop_macro("THIS_INNER_TYPE")
#pragma pop_macro("THIS_INNER_TYPENAME")

#pragma endregion


	/// \brief A satisfaction of the \ref RealNumber concept that is implemented with a fundamental type.
	template<std::floating_point InnerT>
	class FundamentallyBackedRealNumber :
		public RealNumber_IntendedSatisfaction
	{
	public:
		
		using InnerType = InnerT;

	private:
		InnerType m_innerValue;


	public:

		/// \brief Creates a new instance of the \ref FundamentallyBackedRealNumber class.
		/// \param innerValue The numeric value the object represents.
		FundamentallyBackedRealNumber(const InnerType innerValue = default);


		FundamentallyBackedRealNumber(const FundamentallyBackedRealNumber<InnerType>&);


		/// \brief Accessor to a \ref FundamentallyBackedRealNumber instance equal to zero.
		/// \returns A representation of zero.
		static FundamentallyBackedRealNumber<InnerType> getZero();


		/// \brief Accessor to the fundamental value the object represents.
		/// \returns The fundamental value the object represents.
		InnerType getInnerValue() const;


		/// \brief Accessor to the string representation of the number.
		/// \returns The number formatted as a string.
		std::string getStringRepresentation() const;


		/// \brief Accessor to the sign of the number.
		/// \returns A value that represents the sign of the number value.
		ESign getSign() const;


		/// \brief Accessor to the absolute value of the number.
		/// \returns The absolute value of the number.
		FundamentallyBackedRealNumber<InnerType> getAbsoluteValue() const;


		/// \brief Accessor to the whole part of the number.
		/// \returns The whole part of the number.
		/// \example The whole part of <tt>1234.5678</tt> would be <tt>1234</tt>.
		FundamentallyBackedRealNumber<InnerType> getWholePart() const;


		/// \brief Calculates the number to the power of another number.
		/// \param exponent The exponent to raise to.
		/// \returns The number to the power of \p exponent.
		FundamentallyBackedRealNumber<InnerType> pow(const FundamentallyBackedRealNumber<InnerType>& exponent) const;


		/// \brief Calculates the nth-root of another.
		/// \param degree The degree of the root to get.
		/// \returns The nth-root of the number with a degree of \p degree.
		FundamentallyBackedRealNumber<InnerType> nthRoot(const FundamentallyBackedRealNumber<InnerType>& degree) const;


#pragma region Comparison operators

		friend bool operator==(const FundamentallyBackedRealNumber<InnerType>& lhs, const FundamentallyBackedRealNumber<InnerType>& rhs);
		friend bool operator!=(const FundamentallyBackedRealNumber<InnerType>& lhs, const FundamentallyBackedRealNumber<InnerType>& rhs);
		friend bool operator<(const FundamentallyBackedRealNumber<InnerType>& lhs, const FundamentallyBackedRealNumber<InnerType>& rhs);
		friend bool operator<=(const FundamentallyBackedRealNumber<InnerType>& lhs, const FundamentallyBackedRealNumber<InnerType>& rhs);
		friend bool operator>(const FundamentallyBackedRealNumber<InnerType>& lhs, const FundamentallyBackedRealNumber<InnerType>& rhs);
		friend bool operator>=(const FundamentallyBackedRealNumber<InnerType>& lhs, const FundamentallyBackedRealNumber<InnerType>& rhs);

#pragma endregion


#pragma region Unary arithmetic operators

		friend FundamentallyBackedRealNumber<InnerType>& operator-();

		FundamentallyBackedRealNumber<InnerType>& operator++();
		FundamentallyBackedRealNumber<InnerType> operator++(int);

		FundamentallyBackedRealNumber<InnerType>& operator--();
		FundamentallyBackedRealNumber<InnerType> operator--(int);

#pragma endregion


#pragma region Binary arithmetic operators
		
		FundamentallyBackedRealNumber<InnerType>& operator+=(const FundamentallyBackedRealNumber<InnerType>& rhs);

		friend FundamentallyBackedRealNumber<InnerType> operator+
		(
			const FundamentallyBackedRealNumber<InnerType>& lhs,
			const FundamentallyBackedRealNumber<InnerType>& rhs
		);

		FundamentallyBackedRealNumber<InnerType>& operator-=(const FundamentallyBackedRealNumber<InnerType>& rhs);

		friend FundamentallyBackedRealNumber<InnerType> operator-
		(
			const FundamentallyBackedRealNumber<InnerType>& lhs,
			const FundamentallyBackedRealNumber<InnerType>& rhs
		);

		FundamentallyBackedRealNumber<InnerType>& operator*=(const FundamentallyBackedRealNumber<InnerType>& rhs);

		friend FundamentallyBackedRealNumber<InnerType> operator*
		(
			const FundamentallyBackedRealNumber<InnerType>& lhs,
			const FundamentallyBackedRealNumber<InnerType>& rhs
		);

		FundamentallyBackedRealNumber<InnerType>& operator/=(const FundamentallyBackedRealNumber<InnerType>& rhs);

		friend FundamentallyBackedRealNumber<InnerType> operator/
		(
			const FundamentallyBackedRealNumber<InnerType>& lhs,
			const FundamentallyBackedRealNumber<InnerType>& rhs
		);

		FundamentallyBackedRealNumber<InnerType>& operator%=(const FundamentallyBackedRealNumber<InnerType>& rhs);

		friend FundamentallyBackedRealNumber<InnerType> operator%
		(
			const FundamentallyBackedRealNumber<InnerType>& lhs,
			const FundamentallyBackedRealNumber<InnerType>& rhs
		);

#pragma endregion
	};
}

#include "FundamentallyBackedRealNumber.hpp"