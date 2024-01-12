#pragma once

#include "strings.h"
#include "utilities.h"


namespace CmdCalculator
{
	/// \brief A mode to write text to a console.
	enum class EWriteMode
	{
		/// \brief General information.
		Info,
		/// \brief An error message.
		Error,
		/// \brief Debug information.
		Debug
	};


	/// \brief The base type for types that are intended to satisfy the \ref Console concept.
	struct Console_IntendedSatisfaction
	{};
	
	
	/// \brief A text console.
	/// \tparam T The console type.
	template<class T>
	concept Console =
		IntendsToSatisfy<T, Console_IntendedSatisfaction>
		&& String<typename T::StringType>
		&& StringView<typename T::StringViewType>
		&& requires(T && instance)
		{
			{ instance.getInput() } -> std::same_as<typename T::StringType>;
		}
		&& requires(T&& instance, typename T::StringViewType text, EWriteMode writeMode)
		{
			instance.write(text, writeMode);
			instance.writeLine(text, writeMode);
		}
	;
}