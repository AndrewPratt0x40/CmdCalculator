#pragma once

#include <string>
#include <string_view>

#include "ExpressionEvaluationException.h"
#include "RealNumber.h"


namespace CmdCalculator
{
	/// \brief An exception that is thrown when the evaluation of an nth-root operation with a negative radicand is attempted in a CmdCalculator-specific context.
	class NegativeRadicandException : public ExpressionEvaluationException
	{
	private:
		const std::string m_radicand;


	public:

		virtual ~NegativeRadicandException() = default;


		/// \brief Creates a new instance of the \ref NegativeRadicandException class.
		/// \param radicand The negative radicand represented as a string.
		NegativeRadicandException(std::string&& radicand);
		
		
		/// \brief Creates a new instance of the \ref NegativeRadicandException class.
		/// \param radicand The negative radicand represented as a string.
		NegativeRadicandException(std::string_view radicand);


		const char* what() const noexcept override;


		/// \brief Accessor to the negative radicand.
		/// \returns The radicand as a string.
		std::string_view getDividend() const noexcept;
	};
}