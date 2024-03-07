#pragma once

#include <concepts>
#include <ranges>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include <limits>
#include <assert.h>

#include "AntlrContextToMathAstConverter.h"
#include "FullExpressionAntlrContext.h"
#include "AntlrContextTypeDeductions.h"
#include "dynamic_mathast.h"
#include "strings.h"
#include "std_polyfills.h"
#include "NotImplementedException.h"

namespace CmdCalculator
{
	/// \brief A type that converts ANTLR parsing output into polymorphic mathematical abstract syntax trees.
	/// \tparam FullExpressionAntlrContextT The ANTLR context object for a full expression to convert into a math AST.
	/// \tparam CharT The character type to use for strings in the math AST.
	/// \tparam WholePartT The type to use for the whole parts of numbers in the math AST.
	/// \tparam FractionalPartT The type to use for the fractional parts of numbers in the math AST.
	template
	<
		FullExpressionAntlrContext FullExpressionAntlrContextT,
		class CharT,
		std::integral WholePartT,
		std::floating_point FractionalPartT
	>
	class AntlrContextToDynamicMathAstConverter :
		public AntlrContextToMathAstConverter_IntendedSatisfaction
	{
	public:

		using FullExpressionAntlrContextType = FullExpressionAntlrContextT;
		using CharType = CharT;
		using StringType = std::basic_string<CharType>;
		using WholePartType = WholePartT;
		using FractionalPartType = FractionalPartT;


	public:

		std::unique_ptr<MathAst::DynamicBinaryOperatorNode<StringType>> getConvertedBinaryOperatorContext
		(
			const AntlrContextTypeDeductions::BinaryOperatorLeadingTriviaType<FullExpressionAntlrContextType>* const leadingTrivia,
			const AntlrContextTypeDeductions::BinaryOperatorType<FullExpressionAntlrContextType>& context,
			const AntlrContextTypeDeductions::BinaryOperatorTrailingTriviaType<FullExpressionAntlrContextType>* const trailingTrivia
		) const;


	private:

		static constexpr StringType getEmptyString()
		{
			return StringType{};
		}


		static StringType getOptionalTokenText(const Optional auto token)
			requires AntlrToken<OptionalValueType<decltype(token)>>
		{
			return token.has_value()
				? token.value().getText()
				: getEmptyString()
			;
		}


		static WholePartType getWholePartNumericTokenValue(const AntlrToken auto& token)
		{
			const std::string str{ token.getText() };

			if constexpr (std::unsigned_integral<WholePartType>)
			{
				if constexpr (sizeof(WholePartType) <= sizeof(unsigned long))
					return static_cast<WholePartType>(std::stoul(str));
				
				return static_cast<WholePartType>(std::stoull(str));
			}

			if constexpr (sizeof(WholePartType) <= sizeof(int))
				return static_cast<WholePartType>(std::stoi(str));

			if constexpr (sizeof(WholePartType) <= sizeof(long))
				return static_cast<WholePartType>(std::stol(str));

			return static_cast<WholePartType>(std::stoll(str));
		}


		static WholePartType getOptionalWholePartNumericTokenValue(const Optional auto token)
			requires AntlrToken<OptionalValueType<decltype(token)>>
		{
			return token.has_value()
				? getWholePartNumericTokenValue(token.value())
				: static_cast<WholePartType>(0)
			;
		}


		static FractionalPartType getFractionalPartNumericTokenValue(const AntlrToken auto& token)
		{
			const std::string str{ token.getText() };

			if constexpr (sizeof(FractionalPartType) <= sizeof(float))
				return static_cast<FractionalPartType>(std::stof(str));

			if constexpr (sizeof(FractionalPartType) <= sizeof(double))
				return static_cast<FractionalPartType>(std::stod(str));

			return static_cast<FractionalPartType>(std::stold(str));
		}


		static FractionalPartType getOptionalFractionalPartNumericTokenValue(const Optional auto token)
			requires AntlrToken<OptionalValueType<decltype(token)>>
		{
			return token.has_value()
				? getFractionalPartNumericTokenValue(token.value())
				: static_cast<FractionalPartType>(0.0)
			;
		}


		static MathAst::EDynamicNumberLiteralNodePartsConfig getPartsConfigOfWholefulNumber
			(const AntlrContextTypeDeductions::WholefulNumberLiteralType<FullExpressionAntlrContextType>& context)
		{
			if (context.getDecimalPoint().has_value())
			{
				if (context.getFractionalPart().has_value())
					return MathAst::EDynamicNumberLiteralNodePartsConfig::FullDecimal;

				return MathAst::EDynamicNumberLiteralNodePartsConfig::FractionlessDecimal;
			}

			assert(!context.getFractionalPart().has_value());

			return MathAst::EDynamicNumberLiteralNodePartsConfig::Integer;
		}


		std::ranges::owning_view<std::vector<std::unique_ptr<MathAst::DynamicExpressionPartNode<StringType>>>> getConvertedExpressionParts
			(const AntlrContextTypeDeductions::ExpressionType<FullExpressionAntlrContextType>& context) const
		{
			std::vector<std::unique_ptr<MathAst::DynamicExpressionPartNode<StringType>>> parts{};
			parts.emplace_back(std::move(getConvertedOperandContext(context.getHeadOperand())));
			for (const OperationPartPairAntlrContext auto& partPair : context.getOperationPartPairs())
			{
				parts.emplace_back(std::move(getConvertedBinaryOperatorContextFromPartPair(partPair)));
				parts.emplace_back(std::move(getConvertedOperandContext(partPair.getOperandValue())));
			}

			return std::ranges::owning_view(std::move(parts));
		}


		std::unique_ptr<MathAst::DynamicOperandNode<StringType>> getConvertedNonGroupingMultiplicationContext
			(const AntlrContextTypeDeductions::NonGroupingMultiplicationType<FullExpressionAntlrContextType>& context) const
		{
			switch (context.getNonGroupingMultiplicationKind())
			{
			case ENonGroupingMultiplicationAntlrContextKind::NumberLiteral:
				assert(context.getNumberLiteral().has_value());
				assert(!context.getSignOperation().has_value());
				assert(!context.getSqrtOperation().has_value());
				assert(!context.getGrouping().has_value());
				assert(!context.getAbsoluteValueOperation().has_value());
				return getConvertedNumberLiteralContext(context.getNumberLiteral().value());

			case ENonGroupingMultiplicationAntlrContextKind::SignOperation:
				assert(!context.getNumberLiteral().has_value());
				assert(context.getSignOperation().has_value());
				assert(!context.getSqrtOperation().has_value());
				assert(!context.getGrouping().has_value());
				assert(!context.getAbsoluteValueOperation().has_value());
				return getConvertedSignOperationContext(context.getSignOperation().value());

			case ENonGroupingMultiplicationAntlrContextKind::SqrtOperation:
				assert(!context.getNumberLiteral().has_value());
				assert(!context.getSignOperation().has_value());
				assert(context.getSqrtOperation().has_value());
				assert(!context.getGrouping().has_value());
				assert(!context.getAbsoluteValueOperation().has_value());
				return getConvertedSqrtOperationContext(context.getSqrtOperation().value());

			case ENonGroupingMultiplicationAntlrContextKind::Grouping:
				assert(!context.getNumberLiteral().has_value());
				assert(!context.getSignOperation().has_value());
				assert(!context.getSqrtOperation().has_value());
				assert(context.getGrouping().has_value());
				assert(!context.getAbsoluteValueOperation().has_value());
				return getConvertedGroupingContext(context.getGrouping().value());

			case ENonGroupingMultiplicationAntlrContextKind::AbsoluteValueOperation:
				assert(!context.getNumberLiteral().has_value());
				assert(!context.getSignOperation().has_value());
				assert(!context.getSqrtOperation().has_value());
				assert(!context.getGrouping().has_value());
				assert(context.getAbsoluteValueOperation().has_value());
				return getConvertedAbsoluteValueOperationContext(context.getAbsoluteValueOperation().value());

			default:
				Polyfills::unreachable();
			}
		}


		std::unique_ptr<MathAst::DynamicBinaryOperatorNode<StringType>> getConvertedBinaryOperatorContextFromPartPair
			(const AntlrContextTypeDeductions::OperationPartPairType<FullExpressionAntlrContextType>& context) const
		{
			const Optional auto leadingTrivia{ context.getOperatorLeadingTrivia() };
			const OptionalValueType<decltype(leadingTrivia)>* leadingTriviaPtr
			{
				leadingTrivia.has_value()
					? &leadingTrivia.value()
					: nullptr
			};

			const Optional auto trailingTrivia{ context.getOperatorTrailingTrivia() };
			const OptionalValueType<decltype(trailingTrivia)>* trailingTriviaPtr
			{
				trailingTrivia.has_value()
					? &trailingTrivia.value()
					: nullptr
			};

			return getConvertedBinaryOperatorContext(leadingTriviaPtr, context.getOperatorValue(), trailingTriviaPtr);
		}


		std::unique_ptr<MathAst::DynamicNumberLiteralNode<StringType, WholePartT, FractionalPartType>> getConvertedWholefulNumberLiteralContext
			(const AntlrContextTypeDeductions::WholefulNumberLiteralType<FullExpressionAntlrContextType>& context) const
		{
			return std::make_unique<MathAst::DynamicNumberLiteralNode<StringType, WholePartT, FractionalPartType>>
			(
				getWholePartNumericTokenValue(context.getWholePart()),
				getOptionalFractionalPartNumericTokenValue(context.getFractionalPart()),
				getPartsConfigOfWholefulNumber(context),
				getEmptyString(),
				getEmptyString()
			);
		}


		std::unique_ptr<MathAst::DynamicNumberLiteralNode<StringType, WholePartT, FractionalPartType>> getConvertedWholelessNumberLiteralContext
			(const AntlrContextTypeDeductions::WholelessNumberLiteralType<FullExpressionAntlrContextType>& context) const
		{
			return std::make_unique<MathAst::DynamicNumberLiteralNode<StringType, WholePartT, FractionalPartType>>
			(
				static_cast<WholePartType>(0),
				getFractionalPartNumericTokenValue(context.getFractionalPart()),
				MathAst::EDynamicNumberLiteralNodePartsConfig::WholelessDecimal,
				getEmptyString(),
				getEmptyString()
			);
		}


		static bool isSignOperationPositive
			(const AntlrContextTypeDeductions::SignOperationType<FullExpressionAntlrContextType>& context)
		{
			return context.getSignOperator().getSignOperatorAntlrContextKind() == ESignOperatorAntlrContextKind::Positive;
		}


		std::unique_ptr<MathAst::DynamicExpressionNode<StringType>> getConvertedExpressionContextWithTrivia
		(
			const Optional auto leadingTrivia,
			const Optional auto trailingTrivia,
			const AntlrContextTypeDeductions::ExpressionType<FullExpressionAntlrContextType>& context
		) const
			requires AntlrToken<OptionalValueType<decltype(leadingTrivia)>>
			&& AntlrToken<OptionalValueType<decltype(trailingTrivia)>>
		{
			return std::make_unique<MathAst::DynamicExpressionNode<StringType>>
			(
				getOptionalTokenText(leadingTrivia),
				getOptionalTokenText(trailingTrivia),
				std::move(getConvertedExpressionParts(context))
			);
		}


		std::unique_ptr<MathAst::DynamicGroupingNode<StringType>> getConvertedTailMultiplicand
			(const AntlrContextTypeDeductions::GroupingTailMultiplicandType<FullExpressionAntlrContextType>& context) const
		{
			return std::make_unique<MathAst::DynamicGroupingNode<StringType>>
			(
				std::move
				(
					getConvertedExpressionContextWithTrivia
					(
						context.getGroupingValue().getInnerLeadingTrivia(),
						context.getGroupingValue().getInnerTrailingTrivia(),
						context.getGroupingValue().getInnerExpression()
					)
				),
				getOptionalTokenText(context.getInnerTrivia()),
				getEmptyString()
			);
		}


		std::ranges::forward_range auto getConvertedTailMultiplicandsView(std::ranges::forward_range auto tailMultiplicands) const
			requires std::same_as
			<
				std::remove_cv_t<std::ranges::range_value_t<decltype(tailMultiplicands)>>,
				AntlrContextTypeDeductions::GroupingTailMultiplicandType<FullExpressionAntlrContextType>
			>
		{
			return tailMultiplicands
				| std::views::transform
				(
					[&](const auto& tailMultiplicand)
					{ return std::move(getConvertedTailMultiplicand(tailMultiplicand)); }
				)
			;
		}


		auto getConvertedTailMultiplicands(std::ranges::forward_range auto tailMultiplicands) const
			requires std::same_as
			<
				std::remove_cv_t<std::ranges::range_value_t<decltype(tailMultiplicands)>>,
				AntlrContextTypeDeductions::GroupingTailMultiplicandType<FullExpressionAntlrContextType>
			>
		{
			const auto tailMultiplicandsView{ getConvertedTailMultiplicandsView(tailMultiplicands) };
			return std::ranges::owning_view<std::vector<std::unique_ptr<MathAst::DynamicGroupingNode<StringType>>>>
			{
				std::vector<std::unique_ptr<MathAst::DynamicGroupingNode<StringType>>>
				{
					std::ranges::begin(tailMultiplicandsView),
					std::ranges::end(tailMultiplicandsView)
				}
			};
		}


	public:
		
		std::unique_ptr<MathAst::DynamicExpressionNode<StringType>> getConvertedFullExpressionContext
			(const FullExpressionAntlrContextType& context) const
		{
			return std::move
			(
				getConvertedExpressionContextWithTrivia
				(
					context.getLeadingTrivia(),
					context.getTrailingTrivia(),
					context.getExpressionValue()
				)
			);
		}


		std::unique_ptr<MathAst::DynamicExpressionNode<StringType>> getConvertedExpressionContext
			(const AntlrContextTypeDeductions::ExpressionType<FullExpressionAntlrContextType>& context) const
		{
			return std::make_unique<MathAst::DynamicExpressionNode<StringType>>
			(
				getEmptyString(),
				getEmptyString(),
				std::move(getConvertedExpressionParts(context))
			);
		}


		std::unique_ptr<MathAst::DynamicOperandNode<StringType>> getConvertedOperandContext
			(const AntlrContextTypeDeductions::OperandType<FullExpressionAntlrContextType>& context) const
		{
			if (context.isGroupingMultiplication())
			{
				assert(context.getGroupingMultiplicationOperand().has_value());
				assert(!context.getNonGroupingMultiplicationOperand().has_value());
				return getConvertedGroupingMultiplicationContext(context.getGroupingMultiplicationOperand().value());
			}

			assert(context.getNonGroupingMultiplicationOperand().has_value());
			return getConvertedNonGroupingMultiplicationContext(context.getNonGroupingMultiplicationOperand().value());
		}


		std::unique_ptr<ConvertedOperation_part_pairContext<StringType>> getConvertedOperationPartPairContext
			(const AntlrContextTypeDeductions::OperationPartPairType<FullExpressionAntlrContextType>& context) const
		{
			return std::make_unique<ConvertedOperation_part_pairContext<StringType>>
			(
				ConvertedOperation_part_pairContext<StringType>
				{
					.binaryOperator{ std::move(getConvertedBinaryOperatorContextFromPartPair(context)) },
					.operand{ std::move(getConvertedOperandContext(context.getOperandValue())) }
				}
			);
		}


		std::unique_ptr<MathAst::DynamicNumberLiteralNode<StringType, WholePartT, FractionalPartType>> getConvertedNumberLiteralContext
			(const AntlrContextTypeDeductions::NumberLiteralType<FullExpressionAntlrContextType>& context) const
		{
			if (context.getNumberLiteralAntlrContextKind() == ENumberLiteralAntlrContextKind::Wholeful)
			{
				assert(context.getWholefulNumberLiteral().has_value());
				assert(!context.getWholelessNumberLiteral().has_value());
				return getConvertedWholefulNumberLiteralContext(context.getWholefulNumberLiteral().value());
			}

			assert(context.getNumberLiteralAntlrContextKind() == ENumberLiteralAntlrContextKind::Wholeless);
			assert(!context.getWholefulNumberLiteral().has_value());
			assert(context.getWholelessNumberLiteral().has_value());
			return getConvertedWholelessNumberLiteralContext(context.getWholelessNumberLiteral().value());
		}


		std::unique_ptr<MathAst::DynamicSignOperationNode<StringType>> getConvertedSignOperationContext
			(const AntlrContextTypeDeductions::SignOperationType<FullExpressionAntlrContextType>& context) const
		{
			return std::make_unique<MathAst::DynamicSignOperationNode<StringType>>
			(
				std::move(getConvertedOperandContext(context.getOperandValue())),
				isSignOperationPositive(context),
				getOptionalTokenText(context.getInnerTrivia()),
				getEmptyString(),
				getEmptyString()
			);
		}


		std::unique_ptr<MathAst::DynamicSqrtOperationNode<StringType>> getConvertedSqrtOperationContext
			(const AntlrContextTypeDeductions::SqrtOperationType<FullExpressionAntlrContextType>& context) const
		{
			return std::make_unique<MathAst::DynamicSqrtOperationNode<StringType>>
			(
				std::move(getConvertedOperandContext(context.getOperandValue())),
				getOptionalTokenText(context.getInnerTrivia()),
				getEmptyString(),
				getEmptyString()
			);
		}


		std::unique_ptr<MathAst::DynamicGroupingNode<StringType>> getConvertedGroupingContext
			(const AntlrContextTypeDeductions::GroupingType<FullExpressionAntlrContextType>& context) const
		{
			return std::make_unique<MathAst::DynamicGroupingNode<StringType>>
			(
				std::move
				(
					getConvertedExpressionContextWithTrivia
					(
						context.getInnerLeadingTrivia(),
						context.getInnerTrailingTrivia(),
						context.getInnerExpression()
					)
				),
				getEmptyString(),
				getEmptyString()
			);
		}


		std::unique_ptr<MathAst::DynamicGroupingMultiplicationNode<StringType>> getConvertedGroupingMultiplicationContext
			(const AntlrContextTypeDeductions::GroupingMultiplicationType<FullExpressionAntlrContextType>& context) const
		{
			return std::make_unique<MathAst::DynamicGroupingMultiplicationNode<StringType>>
			(
				std::move(getConvertedNonGroupingMultiplicationContext(context.getHeadMultiplicand())),
				std::move(getConvertedTailMultiplicands(context.getTailMultiplicands())),
				getEmptyString(),
				getEmptyString()
			);
		}


		std::unique_ptr<MathAst::DynamicAbsoluteValueNode<StringType>> getConvertedAbsoluteValueOperationContext
			(const AntlrContextTypeDeductions::AbsoluteValueOperationType<FullExpressionAntlrContextType>& context) const
		{
			return std::make_unique<MathAst::DynamicAbsoluteValueNode<StringType>>
			(
				std::move
				(
					getConvertedExpressionContextWithTrivia
					(
						context.getInnerLeadingTrivia(),
						context.getInnerTrailingTrivia(),
						context.getInnerExpression()
					)
				),
				getEmptyString(),
				getEmptyString()
			);
		}
	};


	template
	<
		FullExpressionAntlrContext FullExpressionAntlrContextT,
		class CharT,
		std::integral WholePartT,
		std::floating_point FractionalPartT
	>
	inline std::unique_ptr
	<
		MathAst::DynamicBinaryOperatorNode
		<
			typename AntlrContextToDynamicMathAstConverter<FullExpressionAntlrContextT, CharT, WholePartT, FractionalPartT>::StringType
		>
	>
	AntlrContextToDynamicMathAstConverter<FullExpressionAntlrContextT, CharT, WholePartT, FractionalPartT>::getConvertedBinaryOperatorContext
	(
		const AntlrContextTypeDeductions::BinaryOperatorLeadingTriviaType
		<
			typename AntlrContextToDynamicMathAstConverter<FullExpressionAntlrContextT, CharT, WholePartT, FractionalPartT>::FullExpressionAntlrContextType
		>* const leadingTrivia,
		const AntlrContextTypeDeductions::BinaryOperatorType
		<
			typename AntlrContextToDynamicMathAstConverter<FullExpressionAntlrContextT, CharT, WholePartT, FractionalPartT>::FullExpressionAntlrContextType
		>& context,
		const AntlrContextTypeDeductions::BinaryOperatorTrailingTriviaType
		<
			typename AntlrContextToDynamicMathAstConverter<FullExpressionAntlrContextT, CharT, WholePartT, FractionalPartT>::FullExpressionAntlrContextType
		>* const trailingTrivia
	) const
	{
		const auto triviaPtrToStr
		{
			[&](const AntlrContextTypeDeductions::BinaryOperatorLeadingTriviaType<FullExpressionAntlrContextType>* const trivia) constexpr
				-> StringType
			{
				return trivia
					? convertString<CharType>(trivia->getText())
					: getEmptyString()
				;
			}
		};

		return std::make_unique<MathAst::DynamicBinaryOperatorNode<StringType>>
		(
			context.getBinaryOperatorAntlrContextKind(),
			triviaPtrToStr(leadingTrivia),
			triviaPtrToStr(trailingTrivia)
		);
	}
}