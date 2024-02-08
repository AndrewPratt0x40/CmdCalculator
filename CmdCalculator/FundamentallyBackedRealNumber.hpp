#pragma once

#include "FundamentallyBackedRealNumber.h"
#include "NotImplementedException.h"


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::FundamentallyBackedRealNumber(const InnerType innerValue)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::FundamentallyBackedRealNumber(const FundamentallyBackedRealNumber<InnerT>&)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getZero()
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::InnerType
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getInnerValue() const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline std::string
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getStringRepresentation() const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::ESign
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getSign() const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getAbsoluteValue() const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getWholePart() const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::pow
(
	const FundamentallyBackedRealNumber<InnerT>& exponent
) const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::nthRoot
(
	const FundamentallyBackedRealNumber<InnerT>& degree
) const
{
	throw NotImplementedException{};
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
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
bool
	CmdCalculator::Arithmetic::operator!=
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
bool
	CmdCalculator::Arithmetic::operator<
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
bool
	CmdCalculator::Arithmetic::operator<=
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
bool
	CmdCalculator::Arithmetic::operator>
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
bool
	CmdCalculator::Arithmetic::operator>=
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
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
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator++()
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator++(int)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator--()
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator--(int)
{
	throw NotImplementedException{};
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
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::operator+
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator-=
(
	const FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::operator-
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator*=
(
	const FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::operator*
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator/=
(
	const FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::operator/
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>&
	CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator%=
(
	const FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>
	CmdCalculator::Arithmetic::operator%
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}

#pragma endregion