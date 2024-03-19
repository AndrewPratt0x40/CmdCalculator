#pragma once

// TODO: A lot of the accessor methods in these objects return raw pointers that are never null,
//	they should return references instead.
#include "EBinaryOperator.h"
#include "DynamicMathAstNode.h"
#include "DynamicExpressionNode.h"
#include "DynamicExpressionPartNode.h"
#include "DynamicOperandNode.h"
#include "DynamicUnaryOperationNode.h"
#include "DynamicAbsoluteValueNode.h"
#include "DynamicBinaryOperatorNode.h"
#include "DynamicGroupingNode.h"
#include "DynamicGroupingMultiplicationNode.h"
#include "DynamicNumberLiteralNode.h"
#include "DynamicSignOperationNode.h"
#include "DynamicSqrtOperationNode.h"