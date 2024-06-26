#pragma once

#include <concepts>
#include <cmath>
#include <string>
#include <optional>

#include "../CmdCalculator/RealNumber.h"
#include "../CmdCalculator/std_polyfills.h"
#include "../CmdCalculator/NotImplementedException.h"


namespace CmdCalculatorTestDoubles::Arithmetic
{
	// TODO: Unit test this class better
	class FakeRealNumber :
		public CmdCalculator::Arithmetic::RealNumber_IntendedSatisfaction
	{
	private:
		double m_value;
		std::optional<std::string> m_stringRepresentation;


	public:

		FakeRealNumber(const double value = 0.0) :
			m_value{ value }
		{}


		FakeRealNumber(const std::string stringRepresentation, const double value) :
			m_value{ value },
			m_stringRepresentation{ stringRepresentation }
		{}


		FakeRealNumber(const std::string stringRepresentation) :
			m_value{},
			m_stringRepresentation{ stringRepresentation }
		{
			try
			{
				m_value = std::stod(stringRepresentation);
			}
			catch (const std::invalid_argument&)
			{
				m_value = 0.0;
			}
		}


		double FAKE_getValue() const
		{
			return m_value;
		}


		void FAKE_setValue(const double value)
		{
			m_value = value;
		}


		static FakeRealNumber getZero()
		{
			return FakeRealNumber{ 0.0 };
		}


		std::string getStringRepresentation() const
		{
			return m_stringRepresentation.value_or(std::to_string(m_value));
		}


		friend std::ostream& operator<<(std::ostream& ostream, const FakeRealNumber& value)
		{
			ostream << value.FAKE_getValue();
			return ostream;
		}


		CmdCalculator::Arithmetic::ESign getSign() const
		{
			if (m_value == 0)
				return CmdCalculator::Arithmetic::ESign::Neutral;

			if (m_value > 0)
				return CmdCalculator::Arithmetic::ESign::Positive;

			return CmdCalculator::Arithmetic::ESign::Negative;
		}


#pragma region Operations

		friend bool operator==(const FakeRealNumber& lhs, const FakeRealNumber& rhs)
		{
			return lhs.m_value == rhs.m_value;
		}


		friend bool operator!=(const FakeRealNumber& lhs, const FakeRealNumber& rhs)
		{
			return lhs.m_value != rhs.m_value;
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


		FakeRealNumber operator-() const
		{
			return FakeRealNumber{ -m_value };
		}


		FakeRealNumber& operator++()
		{
			++m_value;
			return *this;
		}


		FakeRealNumber operator++(int)
		{
			double oldValue{ m_value };
			++m_value;
			return FakeRealNumber{ oldValue };
		}


		FakeRealNumber& operator--()
		{
			--m_value;
			return *this;
		}


		FakeRealNumber operator--(int)
		{
			double oldValue{ m_value };
			--m_value;
			return FakeRealNumber{ oldValue };
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
			const auto absRhs{ rhs.getAbsoluteValue().m_value };
			m_value = m_value - absRhs * std::floor(m_value / absRhs);

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
			return FakeRealNumber{ std::pow(m_value, 1.0 / exponent.m_value) };
		}


		FakeRealNumber getAbsoluteValue() const
		{
			return FakeRealNumber{ std::abs(m_value) };
		}


		FakeRealNumber getWholePart() const
		{
			return FakeRealNumber{ std::trunc(m_value) };
		}

#pragma endregion
	};
}