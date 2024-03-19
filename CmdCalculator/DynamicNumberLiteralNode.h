#pragma once

#include "DynamicOperandNode.h"
#include "strings.h"
#include "NotImplementedException.h"

#include <concepts>
#include <string>
#include <ranges>
#include <utility>
#include <regex>

namespace CmdCalculator::MathAst
{
	/// \brief A node that holds an expression inside of it.
	/// \tparam StringT The string type to use.
	template<String StringT>
	class DynamicNumberLiteralNode :
		public DynamicOperandNode<StringT>
	{
	public:

		using StringType = DynamicOperandNode<StringT>::StringType;


	private:

		using CharType = typename StringType::value_type;

		
		const std::optional<StringType> m_wholePart;
		const std::optional<StringType> m_fractionalPart;
		const bool m_isDecimalPointVisible;
		const StringType m_leadingTrivia;
		const StringType m_trailingTrivia;


		inline CharType getDecimalPointChar() const
		{
			return convertChar<CharType>('.');
		}


	public:

		virtual ~DynamicNumberLiteralNode() = default;


		DynamicNumberLiteralNode
		(
			const std::optional<StringType> wholePart,
			const std::optional<StringType> fractionalPart,
			const bool isDecimalPointVisible,
			const StringType leadingTrivia,
			const StringType trailingTrivia
		) :
			m_wholePart{ wholePart },
			m_fractionalPart{ fractionalPart },
			m_isDecimalPointVisible{ isDecimalPointVisible },
			m_leadingTrivia{ leadingTrivia },
			m_trailingTrivia{ trailingTrivia }
		{
			const bool FOO{ m_isDecimalPointVisible || !m_fractionalPart.has_value() };
			assert(m_wholePart.has_value() || m_fractionalPart.has_value());
			assert(m_isDecimalPointVisible || !m_fractionalPart.has_value());
		}


		inline EDerivedDynamicOperandNodeKind getDerivedOperandKind() const override
		{
			return EDerivedDynamicOperandNodeKind::NumberLiteral;
		}
		
		
		/// \brief Accessor to the whole part of the number.
		/// \returns The whole part of the number, if there is any. This is the portion of the number to the left of the decimal point.
		/// \example The whole part of the number <tt>7</tt> is <tt>7</tt>.
		/// \example The whole part of the number <tt>7.</tt> is <tt>7</tt>.
		/// \example The whole part of the number <tt>.7</tt> is <tt>0</tt>.
		/// \example The whole part of the number <tt>123.456</tt> is <tt>123</tt>.
		std::optional<StringType> getWholePart() const
		{
			return m_wholePart;
		}


		/// \brief Accessor to the fractional part of the number.
		/// \returns The fractional part of the number, if there is any. This is the portion of the number to the right of the decimal point.
		/// \example The fractional part of the number <tt>7</tt> is <tt>0</tt>.
		/// \example The fractional part of the number <tt>7.</tt> is <tt>0</tt>.
		/// \example The fractional part of the number <tt>.7</tt> is <tt>7</tt>.
		/// \example The fractional part of the number <tt>123.456</tt> is <tt>123</tt>.
		std::optional<StringType> getFractionalPart() const
		{
			return m_fractionalPart;
		}


		/// \brief Tests if the number includes a whole part.
		/// \returns True if the number includes a whole part, false otherwise.
		bool isWholePartVisible() const
		{
			return m_wholePart.has_value();
		}


		/// \brief Tests if the number includes a decimal point.
		/// \returns True if the number includes a decimal point, false otherwise.
		bool isDecimalPointVisible() const
		{
			return m_isDecimalPointVisible;
		}


		/// \brief Tests if the number includes a fractional part.
		/// \returns True if the number includes a fractional part, false otherwise.
		bool isFractionalPartVisible() const
		{
			return m_fractionalPart.has_value();
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
				str += getWholePart().value();

			if (isDecimalPointVisible())
				str += getDecimalPointChar();

			if (isFractionalPartVisible())
				str += getFractionalPart().value();

			return static_cast<StringType>
			(
				str + static_cast<StdStringType>(getTrailingTrivia())
			);
		}
	};
}