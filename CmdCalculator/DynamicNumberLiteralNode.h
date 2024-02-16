#pragma once

#include "DynamicOperandNode.h"
#include "strings.h"
#include "NotImplementedException.h"

#include <concepts>
#include <string>
#include <ranges>
#include <utility>

namespace CmdCalculator::MathAst
{
	/// \brief Bitflags for the different parts of a \ref DynamicNumberLiteralNode instance.
	enum EDynamicNumberLiteralNodePartsFlags : uint8_t
	{
		WholePart =			1 << 0,
		DecimalPoint =		1 << 1,
		FractionalPart =	1 << 2
	};


	/// \brief Enumerates the different possible configurations of the different parts of a \ref DynamicNumberLiteralNode instance.
	enum class EDynamicNumberLiteralNodePartsConfig : std::underlying_type_t<EDynamicNumberLiteralNodePartsFlags>
	{
		/// A number with a visible whole part, a visible decimal point, and a visible fractional part.
		FullDecimal =
			EDynamicNumberLiteralNodePartsFlags::WholePart
			| EDynamicNumberLiteralNodePartsFlags::DecimalPoint
			| EDynamicNumberLiteralNodePartsFlags::FractionalPart
		,
		/// A number with a visible whole part, no decimal point, and no fractional part.
		Integer =
			EDynamicNumberLiteralNodePartsFlags::WholePart
		,
		/// A number with no whole part, a visible decimal point, and a visible fractional part.
		WholelessDecimal =
			EDynamicNumberLiteralNodePartsFlags::DecimalPoint
			| EDynamicNumberLiteralNodePartsFlags::FractionalPart
		,
		/// A number with a visible whole part, a visible decimal point, and no fractional part.
		FractionlessDecimal =
			EDynamicNumberLiteralNodePartsFlags::WholePart
			| EDynamicNumberLiteralNodePartsFlags::DecimalPoint
	};
	
	
	/// \brief A node that holds an expression inside of it.
	/// \tparam StringT The string type to use.
	/// \tparam IntT The type to use to store integers.
	template<String StringT, std::integral IntT>
	class DynamicNumberLiteralNode :
		public DynamicOperandNode<StringT>
	{
	public:

		using StringType = DynamicOperandNode<StringT>::StringType;

		using IntType = IntT;


	private:

		using CharType = typename StringType::value_type;

		
		const IntType m_wholePart;
		const IntType m_fractionalPart;
		const EDynamicNumberLiteralNodePartsFlags m_partsFlags;
		const StringType m_leadingTrivia;
		const StringType m_trailingTrivia;


		inline CharType getDecimalPointChar() const
		{
			return convertChar<CharType>('.');
		}


		auto getIntAsString(const IntType intValue) const
		{
			return convertString<CharType>(std::to_string(intValue));
		}


	public:

		virtual ~DynamicNumberLiteralNode() = default;


		DynamicNumberLiteralNode
		(
			const IntType wholePart,
			const IntType fractionalPart,
			const EDynamicNumberLiteralNodePartsConfig partsConfig,
			const StringType leadingTrivia,
			const StringType trailingTrivia
		) :
			m_wholePart{ wholePart },
			m_fractionalPart{ fractionalPart },
			m_partsFlags{ static_cast<EDynamicNumberLiteralNodePartsFlags>(partsConfig) },
			m_leadingTrivia{ leadingTrivia },
			m_trailingTrivia{ trailingTrivia }
		{
			assert(m_wholePart >= 0);
			assert(m_fractionalPart >= 0);
		}


		inline EDerivedDynamicOperandNodeKind getDerivedOperandKind() const override
		{
			return EDerivedDynamicOperandNodeKind::NumberLiteral;
		}
		
		
		/// \brief Accessor to the whole part of the number.
		/// \returns The whole part of the number as an integer. This is the portion of the number to the left of the decimal point.
		/// \example The whole part of the number <tt>7</tt> is <tt>7</tt>.
		/// \example The whole part of the number <tt>7.</tt> is <tt>7</tt>.
		/// \example The whole part of the number <tt>.7</tt> is <tt>0</tt>.
		/// \example The whole part of the number <tt>123.456</tt> is <tt>123</tt>.
		IntT getWholePart() const
		{
			return m_wholePart;
		}


		/// \brief Accessor to the fractional part of the number.
		/// \returns The fractional part of the number as an integer. This is the portion of the number to the right of the decimal point.
		/// \example The fractional part of the number <tt>7</tt> is <tt>0</tt>.
		/// \example The fractional part of the number <tt>7.</tt> is <tt>0</tt>.
		/// \example The fractional part of the number <tt>.7</tt> is <tt>7</tt>.
		/// \example The fractional part of the number <tt>123.456</tt> is <tt>123</tt>.
		IntT getFractionalPart() const
		{
			return m_fractionalPart;
		}


		/// \brief Tests if the number includes a whole part.
		/// \returns True if the number includes a whole part, false otherwise.
		bool isWholePartVisible() const
		{
			return m_partsFlags & EDynamicNumberLiteralNodePartsFlags::WholePart;
		}


		/// \brief Tests if the number includes a decimal point.
		/// \returns True if the number includes a decimal point, false otherwise.
		bool isDecimalPointVisible() const
		{
			return m_partsFlags & EDynamicNumberLiteralNodePartsFlags::DecimalPoint;
		}


		/// \brief Tests if the number includes a fractional part.
		/// \returns True if the number includes a fractional part, false otherwise.
		bool isFractionalPartVisible() const
		{
			return m_partsFlags & EDynamicNumberLiteralNodePartsFlags::FractionalPart;
		}


		StringType getLeadingTrivia() const override
		{
			return m_leadingTrivia;
		}


		StringType getTrailingTrivia() const override
		{
			return m_trailingTrivia;
		}


		StringType getStringRepresentation() const override
		{
			using StdStringType = std::basic_string<CharType>;
			
			StdStringType str{ getLeadingTrivia() };

			if (isWholePartVisible())
				str += static_cast<StdStringType>(getIntAsString(getWholePart()));
			if (isDecimalPointVisible())
				str += getDecimalPointChar();
			if (isFractionalPartVisible())
				str += static_cast<StdStringType>(getIntAsString(getFractionalPart()));

			return static_cast<StringType>
			(
				str
				+ static_cast<StdStringType>(getTrailingTrivia())
			);
		}
	};
}