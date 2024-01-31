#pragma once

#include <concepts>
#include <cmath>

#include "../CmdCalculator/RealNumber.h"
#include "../CmdCalculator/NotImplementedException.h"


namespace CmdCalculatorTestDoubles::Arithmetic
{
	struct DummyRealNumber :
		public CmdCalculator::Arithmetic::RealNumber_IntendedSatisfaction
	{
		double m_value;


		DummyRealNumber(const double value = 0.0) :
			m_value{ value }
		{}


		CmdCalculator::Arithmetic::ESign getSign() const
		{
			if (m_value == 0)
				return CmdCalculator::Arithmetic::ESign::Neutral;

			if (m_value > 0)
				return CmdCalculator::Arithmetic::ESign::Positive;

			return CmdCalculator::Arithmetic::ESign::Negative;
		}


		friend bool operator==(const FakeRealNumber& lhs, const FakeRealNumber& rhs)
		{
			return lhs.m_value == rhs.m_value;
		}


		friend bool operator!=(const FakeRealNumber& lhs, const FakeRealNumber& rhs)
		{
			return lhs != rhs;
		}


		friend bool operator<(const FakeRealNumber& lhs, const FakeRealNumber& rhs)
		{
			return lhs.m_value < rhs.m_value;
		}


		friend bool operator<=(const FakeRealNumber& lhs, const FakeRealNumber& rhs)
		{
			return lhs.m_value <= rhs.m_value;
		}


		friend bool operator>(const FakeRealNumber& lhs, const FakeRealNumber& rhs)
		{
			return lhs.m_value > rhs.m_value;
		}


		friend bool operator>=(const FakeRealNumber& lhs, const FakeRealNumber& rhs)
		{
			return lhs.m_value >= rhs.m_value;
		}


		FakeRealNumber& operator+=(const FakeRealNumber& rhs)
		{
			m_value += rhs.m_value;
			return *this;
		}


		friend FakeRealNumber operator+(FakeRealNumber lhs, const FakeRealNumber& rhs)
		{
			lhs += rhs;
			return lhs;
		}


		FakeRealNumber& operator-=(const FakeRealNumber& rhs)
		{
			m_value -= rhs.m_value;
			return *this;
		}


		friend FakeRealNumber operator-(FakeRealNumber lhs, const FakeRealNumber& rhs)
		{
			lhs -= rhs;
			return lhs;
		}


		FakeRealNumber& operator*=(const FakeRealNumber& rhs)
		{
			m_value *= rhs.m_value;
			return *this;
		}


		friend FakeRealNumber operator*(FakeRealNumber lhs, const FakeRealNumber& rhs)
		{
			lhs *= rhs;
			return lhs;
		}


		FakeRealNumber& operator/=(const FakeRealNumber& rhs)
		{
			m_value /= rhs.m_value;
			return *this;
		}


		friend FakeRealNumber operator/(FakeRealNumber lhs, const FakeRealNumber& rhs)
		{
			lhs /= rhs;
			return lhs;
		}


		FakeRealNumber& operator%=(const FakeRealNumber& rhs)
		{
			m_value = static_cast<int>(m_value) % static_cast<int>(rhs.m_value);
			return *this;
		}


		friend FakeRealNumber operator%(FakeRealNumber lhs, const FakeRealNumber& rhs)
		{
			lhs %= rhs;
			return lhs;
		}


		FakeRealNumber pow(const FakeRealNumber& exponent) const
		{
			return FakeRealNumber{ std::pow(m_value, exponent.m_value) };
		}


		FakeRealNumber nthRoot(const FakeRealNumber& exponent) const
		{
			return FakeRealNumber{ std::pow(m_value, exponent.m_value) };
		}


		FakeRealNumber getAbsoluteValue() const
		{
			throw CmdCalculator::NotImplementedException{};
		}
	};
}