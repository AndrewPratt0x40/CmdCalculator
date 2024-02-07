#pragma once

#include "FundamentallyBackedRealNumber.h"
#include "NotImplementedException.h"


#pragma push_macro("THIS_INNER_TYPE")
#define THIS_INNER_TYPE CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::InnerType
#pragma push_macro("THIS_INNER_TYPENAME")
#define THIS_INNER_TYPENAME typename THIS_INNER_TYPE
#pragma push_macro("THIS_TYPE")
#define THIS_TYPE CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<THIS_INNER_TYPENAME>


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::FundamentallyBackedRealNumber(const InnerType innerValue)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::FundamentallyBackedRealNumber(const THIS_TYPE&)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline THIS_TYPE CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getZero()
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline THIS_INNER_TYPE CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getInnerValue() const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline std::string CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getStringRepresentation() const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline CmdCalculator::Arithmetic::ESign CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getSign() const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline THIS_TYPE CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getAbsoluteValue() const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline THIS_TYPE CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::getWholePart() const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline THIS_TYPE CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::pow(const THIS_TYPE& exponent) const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
inline THIS_TYPE CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::nthRoot(const THIS_TYPE& degree) const
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> operator-(const THIS_TYPE& number)
{
	throw CmdCalculator::NotImplementedException{};
}


#pragma region Comparison operators

template<std::floating_point InnerT>
bool operator==
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
bool operator!=
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
bool operator<
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
bool operator<=
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
bool operator>
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
bool operator>=
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
bool operator-
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}

#pragma endregion


#pragma region Binary arithmetic operators

template<std::floating_point InnerT>
inline THIS_TYPE& CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator+=(const THIS_TYPE& rhs)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> operator+
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
inline THIS_TYPE& CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator-=(const THIS_TYPE& rhs)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> operator-
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
inline THIS_TYPE& CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator*=(const THIS_TYPE& rhs)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> operator*
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
inline THIS_TYPE& CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator/=(const THIS_TYPE& rhs)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> operator/
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}


template<std::floating_point InnerT>
inline THIS_TYPE& CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>::operator%=(const THIS_TYPE& rhs)
{
	throw NotImplementedException{};
}


template<std::floating_point InnerT>
CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT> operator%
(
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& lhs,
	const CmdCalculator::Arithmetic::FundamentallyBackedRealNumber<InnerT>& rhs
)
{
	throw CmdCalculator::NotImplementedException{};
}

#pragma endregion


#pragma pop_macro("THIS_TYPE")
#pragma pop_macro("THIS_INNER_TYPE")
#pragma pop_macro("THIS_INNER_TYPENAME")