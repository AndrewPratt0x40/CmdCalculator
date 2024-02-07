#pragma once

#include <concepts>
#include <string>

#include "RealNumber.h"

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


		FundamentallyBackedRealNumber<InnerType>& operator+=(const FundamentallyBackedRealNumber<InnerType>& rhs);
		FundamentallyBackedRealNumber<InnerType>& operator-=(const FundamentallyBackedRealNumber<InnerType>& rhs);
		FundamentallyBackedRealNumber<InnerType>& operator*=(const FundamentallyBackedRealNumber<InnerType>& rhs);
		FundamentallyBackedRealNumber<InnerType>& operator/=(const FundamentallyBackedRealNumber<InnerType>& rhs);
		FundamentallyBackedRealNumber<InnerType>& operator%=(const FundamentallyBackedRealNumber<InnerType>& rhs);
	};
}

#include "FundamentallyBackedRealNumber.hpp"