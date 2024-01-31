#include "DynamicNthRootOperation.h"
#include "NotImplementedException.h"


#pragma push_macro("THIS_NUMBER_TYPE")
#define THIS_NUMBER_TYPE CmdCalculator::Expressions::DynamicNthRootOperation<NumberT>::NumberType
#pragma push_macro("THIS_NUMBER_TYPENAME")
#define THIS_NUMBER_TYPENAME typename THIS_NUMBER_TYPE


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicNthRootOperation<NumberT>::DynamicNthRootOperation
(
	std::unique_ptr<DynamicExpression<NumberType>> degree,
	std::unique_ptr<DynamicExpression<NumberType>> radicand
)
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicNthRootOperation<NumberT>::~DynamicNthRootOperation() = default;


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::DynamicNthRootOperation<NumberT>::getDegree() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpression<THIS_NUMBER_TYPENAME>&
	CmdCalculator::Expressions::DynamicNthRootOperation<NumberT>::getRadicand() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline bool CmdCalculator::Expressions::DynamicNthRootOperation<NumberT>::isSimplifiable() const
{
	throw NotImplementedException{};
}


template<CmdCalculator::Arithmetic::RealNumber NumberT>
inline CmdCalculator::Expressions::DynamicExpressionBox<THIS_NUMBER_TYPENAME>
	CmdCalculator::Expressions::DynamicNthRootOperation<NumberT>::getFullSimplification() const
{
	throw NotImplementedException{};
}


#pragma pop_macro("THIS_NUMBER_TYPE")
#pragma pop_macro("THIS_NUMBER_TYPENAME")