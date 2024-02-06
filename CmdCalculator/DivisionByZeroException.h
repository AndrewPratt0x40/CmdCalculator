#pragma once

#include <string>
#include <string_view>

#include "ExpressionEvaluationException.h"
#include "RealNumber.h"


namespace CmdCalculator
{
	/// \brief An exception that is thrown when division by zero is attempted in a CmdCalculator-specific context.
	class DivisionByZeroException : public ExpressionEvaluationException
	{
	private:
		const std::string m_dividend;


	public:

		virtual ~DivisionByZeroException() = default;


		/// \brief Creates a new instance of the \ref DivisionByZeroException class.
		/// \param dividend The dividend that attempted to divide by zero represented as a string.
		DivisionByZeroException(std::string&& dividend);
		
		
		/// \brief Creates a new instance of the \ref DivisionByZeroException class.
		/// \param dividend The dividend that attempted to divide by zero represented as a string.
		DivisionByZeroException(std::string_view dividend);


		const char* what() const noexcept override;


		/// \brief Accessor to the dividend that attempted to divide by zero.
		/// \returns The dividend as a string.
		std::string_view getDividend() const noexcept;
	};
}