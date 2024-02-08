#pragma once

#include <concepts>
#include <string>

#include "RealNumber.h"


#pragma region Non-member forward declarations
namespace CmdCalculator::Arithmetic
{
	template<std::floating_point InnerT>
	class FundamentallyBackedRealNumber;


#pragma region Comparison operators

	template<std::floating_point InnerT>
	bool operator==
	(
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
	);

	template<std::floating_point InnerT>
	bool operator!=
	(
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
	);

	template<std::floating_point InnerT>
	bool operator<
	(
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
	);

	template<std::floating_point InnerT>
	bool operator<=
	(
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
	);

	template<std::floating_point InnerT>
	bool operator>
	(
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
	);

	template<std::floating_point InnerT>
	bool operator>=
	(
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
	);

#pragma endregion


#pragma region Unary arithmetic operators

	template<std::floating_point InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> operator-
	(
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
	);

#pragma endregion


#pragma region Binary arithmetic operations

	template<std::floating_point InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> operator+
	(
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
	);

	template<std::floating_point InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> operator-
	(
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
	);

	template<std::floating_point InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> operator*
	(
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
	);

	template<std::floating_point InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> operator/
	(
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
	);

	template<std::floating_point InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> operator%
	(
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
		const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
	);

#pragma endregion
}

#pragma endregion


namespace CmdCalculator::Arithmetic
{
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


		FundamentallyBackedRealNumber(const FundamentallyBackedRealNumber<InnerT>&);


		/// \brief Accessor to a \ref FundamentallyBackedRealNumber instance equal to zero.
		/// \returns A representation of zero.
		static FundamentallyBackedRealNumber<InnerT> getZero();


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
		FundamentallyBackedRealNumber<InnerT> getAbsoluteValue() const;


		/// \brief Accessor to the whole part of the number.
		/// \returns The whole part of the number.
		/// \example The whole part of <tt>1234.5678</tt> would be <tt>1234</tt>.
		FundamentallyBackedRealNumber<InnerT> getWholePart() const;


		/// \brief Calculates the number to the power of another number.
		/// \param exponent The exponent to raise to.
		/// \returns The number to the power of \p exponent.
		FundamentallyBackedRealNumber<InnerT> pow(const FundamentallyBackedRealNumber<InnerT>& exponent) const;


		/// \brief Calculates the nth-root of another.
		/// \param degree The degree of the root to get.
		/// \returns The nth-root of the number with a degree of \p degree.
		FundamentallyBackedRealNumber<InnerT> nthRoot(const FundamentallyBackedRealNumber<InnerT>& degree) const;


#pragma region Comparison operators

		friend bool operator==<InnerT>(const FundamentallyBackedRealNumber<InnerT>& lhs, const FundamentallyBackedRealNumber<InnerT>& rhs);
		friend bool operator!=(const FundamentallyBackedRealNumber<InnerT>& lhs, const FundamentallyBackedRealNumber<InnerT>& rhs);
		friend bool operator<(const FundamentallyBackedRealNumber<InnerT>& lhs, const FundamentallyBackedRealNumber<InnerT>& rhs);
		friend bool operator<=(const FundamentallyBackedRealNumber<InnerT>& lhs, const FundamentallyBackedRealNumber<InnerT>& rhs);
		friend bool operator>(const FundamentallyBackedRealNumber<InnerT>& lhs, const FundamentallyBackedRealNumber<InnerT>& rhs);
		friend bool operator>=(const FundamentallyBackedRealNumber<InnerT>& lhs, const FundamentallyBackedRealNumber<InnerT>& rhs);

#pragma endregion


#pragma region Unary arithmetic operators

		friend FundamentallyBackedRealNumber<InnerT>& operator-(const FundamentallyBackedRealNumber<InnerT>& rhs);

		FundamentallyBackedRealNumber<InnerT>& operator++();
		FundamentallyBackedRealNumber<InnerT> operator++(int);

		FundamentallyBackedRealNumber<InnerT>& operator--();
		FundamentallyBackedRealNumber<InnerT> operator--(int);

#pragma endregion


#pragma region Binary arithmetic operators
		
		FundamentallyBackedRealNumber<InnerT>& operator+=(const FundamentallyBackedRealNumber<InnerT>& rhs);

		friend FundamentallyBackedRealNumber<InnerT> operator+
		(
			const FundamentallyBackedRealNumber<InnerT>& lhs,
			const FundamentallyBackedRealNumber<InnerT>& rhs
		);

		FundamentallyBackedRealNumber<InnerT>& operator-=(const FundamentallyBackedRealNumber<InnerT>& rhs);

		friend FundamentallyBackedRealNumber<InnerT> operator-
		(
			const FundamentallyBackedRealNumber<InnerT>& lhs,
			const FundamentallyBackedRealNumber<InnerT>& rhs
		);

		FundamentallyBackedRealNumber<InnerT>& operator*=(const FundamentallyBackedRealNumber<InnerT>& rhs);

		friend FundamentallyBackedRealNumber<InnerT> operator*
		(
			const FundamentallyBackedRealNumber<InnerT>& lhs,
			const FundamentallyBackedRealNumber<InnerT>& rhs
		);

		FundamentallyBackedRealNumber<InnerT>& operator/=(const FundamentallyBackedRealNumber<InnerT>& rhs);

		friend FundamentallyBackedRealNumber<InnerT> operator/
		(
			const FundamentallyBackedRealNumber<InnerT>& lhs,
			const FundamentallyBackedRealNumber<InnerT>& rhs
		);

		FundamentallyBackedRealNumber<InnerT>& operator%=(const FundamentallyBackedRealNumber<InnerT>& rhs);

		friend FundamentallyBackedRealNumber<InnerT> operator%
		(
			const FundamentallyBackedRealNumber<InnerT>& lhs,
			const FundamentallyBackedRealNumber<InnerT>& rhs
		);

#pragma endregion
	};
}

#include "FundamentallyBackedRealNumber.hpp"