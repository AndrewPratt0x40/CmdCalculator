#pragma once

#include "StringToAntlrContextConverter.h"
#include "OwningTrueFullExpressionAntlrContext.h"
#include "strings.h"
#include "NotImplementedException.h"

#include <memory>


namespace CmdCalculator
{
	/// \brief A satisfaction of the \ref StringToAntlrContextConverter concept that invokes the ANTLR runtime.
	/// \tparam StringViewT The string view type to use.
	template<StringView StringViewT>
	class AntlrInvokingStringToAntlrContextConverter :
		public StringToAntlrContextConverter_IntendedSatisfaction
	{
	public:
		using StringViewType = StringViewT;


		/// Converts a string to an ANTLR context object invoking by the ANTLR runtime.
		/// \param source The string to parse.
		/// \returns An owning pointer to an ANTLR context object.
		std::unique_ptr<OwningTrueFullExpressionAntlrContext> getStringAsAntlrContext(StringViewType source)
		{
			return std::make_unique<OwningTrueFullExpressionAntlrContext>
			(
				std::move
				(
					OwningTrueFullExpressionAntlrContext::parse
					(
						std::basic_string<typename StringViewType::value_type>
						{
							std::basic_string_view<typename StringViewType::value_type>{ source }
						}
					)
				)
			);
		}
	};
}