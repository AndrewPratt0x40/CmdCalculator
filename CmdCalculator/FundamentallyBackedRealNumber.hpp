#pragma once

#include <string>

#include "FundamentallyBackedRealNumber.h"
#include "NotImplementedException.h"


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::FundamentallyBackedRealNumber(const InnerType innerValue) :
	m_innerValue{ innerValue }
{}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::FundamentallyBackedRealNumber(const FundamentallyBackedRealNumber<InnerT>& other) :
	m_innerValue{ other.m_innerValue }
{}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getZero()
{
	return FundamentallyBackedRealNumber<InnerT>{ 0.0 };
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::InnerType
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getInnerValue() const
{
	return m_innerValue;
}


template<std::floating_point InnerT>
inline std::string
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getStringRepresentation() const
{
	return std::to_string(getInnerValue());
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::ESign
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getSign() const
{
	if (getInnerValue() < 0.0)
		return ESign::Negative;
	if (getInnerValue() > 0.0)
		return ESign::Positive;
	return ESign::Neutral;
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getAbsoluteValue() const
{
	return FundamentallyBackedRealNumber<InnerT>{ std::abs(getInnerValue()) };
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getWholePart() const
{
	return FundamentallyBackedRealNumber<InnerT>{ std::trunc(getInnerValue()) };
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::pow
(
	const FundamentallyBackedRealNumber<InnerT>& exponent
) const
{
	assert(exponent.getSign() != ESign::Negative);
	assert(exponent.getWholePart() == exponent);

	return FundamentallyBackedRealNumber<InnerT>{ std::pow(getInnerValue(), exponent.getInnerValue()) };
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::nthRoot
(
	const FundamentallyBackedRealNumber<InnerT>& degree
) const
{
	assert(getSign() != ESign::Negative);
	assert(degree.getSign() == ESign::Positive);
	assert(degree.getWholePart() == degree);

	return FundamentallyBackedRealNumber<InnerT>
	{
		std::pow
		(
			getInnerValue(),
			1.0 / degree.getInnerValue()
		)
	};
}


#pragma region Comparison operators

template<std::floating_point InnerT>
bool
	CmdCalculator::Arithmetic::operator==
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	return lhs.getInnerValue() == rhs.getInnerValue();
}


template<std::floating_point InnerT>
std::strong_ordering
	CmdCalculator::Arithmetic::operator<=>
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	if (lhs.getInnerValue() < rhs.getInnerValue())
		return std::strong_ordering::less;

	if (lhs.getInnerValue() > rhs.getInnerValue())
		return std::strong_ordering::greater;

	return std::strong_ordering::equal;
}

#pragma endregion


#pragma region Unary arithmetic operators

template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::operator-
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	return FundamentallyBackedRealNumber<InnerT>{ -rhs.getInnerValue() };
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator++()
{
	++m_innerValue;
	return *this;
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator++(int)
{
	auto oldValue{ *this };
	m_innerValue++;
	return oldValue;
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator--()
{
	--m_innerValue;
	return *this;
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator--(int)
{
	auto oldValue{ *this };
	m_innerValue--;
	return oldValue;
}

#pragma endregion


#pragma region Binary arithmetic operators

template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator+=
(
	const FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	m_innerValue += rhs.getInnerValue();
	return *this;
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::operator+
(
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	lhs += rhs;
	return lhs;
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator-=
(
	const FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	m_innerValue -= rhs.getInnerValue();
	return *this;
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::operator-
(
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	lhs -= rhs;
	return lhs;
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator*=
(
	const FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	m_innerValue *= rhs.getInnerValue();
	return *this;
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::operator*
(
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	lhs *= rhs;
	return lhs;
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator/=
(
	const FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	m_innerValue /= rhs.getInnerValue();
	return *this;
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::operator/
(
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	lhs /= rhs;
	return lhs;
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator%=
(
	const FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	const auto absRhs{ rhs.getAbsoluteValue().getInnerValue() };
	m_innerValue = m_innerValue - absRhs * std::floor(m_innerValue / absRhs);

	return *this;
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::operator%
(
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	lhs %= rhs;
	return lhs;
}

#pragma endregion