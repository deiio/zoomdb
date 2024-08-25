/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#include "common/internal-types.hpp"

#include "common/string_util.hpp"

namespace zoomdb {

ExpressionType StringToExpressionType(const std::string& str) {
  auto upper_str = StringUtil::Upper(str);
  if (upper_str == "INVALID") {
    return ExpressionType::kInvalid;
  } else if (upper_str == "OPERATOR_PLUS" || upper_str == "+") {
    return ExpressionType::kOperatorPlus;
  } else if (upper_str == "OPERATOR_MINUS" || upper_str == "-") {
    return ExpressionType::kOperatorMinus;
  } else if (upper_str == "OPERATOR_MULTIPLY" || upper_str == "*") {
    return ExpressionType::kOperatorMultiply;
  } else if (upper_str == "OPERATOR_DIVIDE" || upper_str == "/") {
    return ExpressionType::kOperatorDivide;
  } else if (upper_str == "OPERATOR_CONCAT" || upper_str == "||") {
    return ExpressionType::kOperatorConcat;
  } else if (upper_str == "OPERATOR_MOD" || upper_str == "%") {
    return ExpressionType::kOperatorMod;
  } else if (upper_str == "OPERATOR_CAST") {
    return ExpressionType::kOperatorCast;
  } else if (upper_str == "OPERATOR_NOT") {
    return ExpressionType::kOperatorNot;
  } else if (upper_str == "OPERATOR_IS_NULL") {
    return ExpressionType::kOperatorIsNull;
  } else if (upper_str == "OPERATOR_IS_NOT_NULL") {
    return ExpressionType::kOperatorIsNotNull;
  } else if (upper_str == "OPERATOR_EXISTS") {
    return ExpressionType::kOperatorExists;
  } else if (upper_str == "OPERATOR_UNARY_MINUS") {
    return ExpressionType::kOperatorUnaryMinus;
  } else if (upper_str == "COMPARE_EQUAL" || upper_str == "=") {
    return ExpressionType::kCompareEqual;
  } else if (upper_str == "COMPARE_NOTEQUAL" || upper_str == "!=" ||
             upper_str == "<>") {
    return ExpressionType::kCompareNotEqual;
  } else if (upper_str == "COMPARE_LESSTHAN" || upper_str == "<") {
    return ExpressionType::kCompareLessThan;
  } else if (upper_str == "COMPARE_GREATERTHAN" || upper_str == ">") {
    return ExpressionType::kCompareGreaterThan;
  } else if (upper_str == "COMPARE_LESSTHANOREQUALTO" || upper_str == "<=") {
    return ExpressionType::kCompareLessThanOrEqualTo;
  } else if (upper_str == "COMPARE_GREATERTHANOREQUALTO" || upper_str == ">=") {
    return ExpressionType::kCompareGreaterThanOrEqualTo;
  } else if (upper_str == "COMPARE_LIKE" || upper_str == "~~") {
    return ExpressionType::kCompareLike;
  } else if (upper_str == "COMPARE_NOTLIKE" || upper_str == "!~~") {
    return ExpressionType::kCompareNotLike;
  } else if (upper_str == "COMPARE_IN") {
    return ExpressionType::kCompareIn;
  } else if (upper_str == "COMPARE_DISTINCT_FROM") {
    return ExpressionType::kCompareDistinctFrom;
  } else if (upper_str == "CONJUNCTION_AND") {
    return ExpressionType::kConjunctionAnd;
  } else if (upper_str == "CONJUNCTION_OR") {
    return ExpressionType::kConjunctionOr;
  } else if (upper_str == "VALUE_CONSTANT") {
    return ExpressionType::kValueConstant;
  } else if (upper_str == "VALUE_PARAMETER") {
    return ExpressionType::kValueParameter;
  } else if (upper_str == "VALUE_TUPLE") {
    return ExpressionType::kValueTuple;
  } else if (upper_str == "VALUE_TUPLE_ADDRESS") {
    return ExpressionType::kValueTupleAddress;
  } else if (upper_str == "VALUE_NULL") {
    return ExpressionType::kValueNull;
  } else if (upper_str == "VALUE_VECTOR") {
    return ExpressionType::kValueVector;
  } else if (upper_str == "VALUE_SCALAR") {
    return ExpressionType::kValueScalar;
  } else if (upper_str == "AGGREGATE_COUNT") {
    return ExpressionType::kAggregateCount;
  } else if (upper_str == "AGGREGATE_COUNT_STAR") {
    return ExpressionType::kAggregateCountStar;
  } else if (upper_str == "AGGREGATE_SUM") {
    return ExpressionType::kAggregateSum;
  } else if (upper_str == "AGGREGATE_MIN") {
    return ExpressionType::kAggregateMin;
  } else if (upper_str == "AGGREGATE_MAX") {
    return ExpressionType::kAggregateMax;
  } else if (upper_str == "AGGREGATE_AVG") {
    return ExpressionType::kAggregateAvg;
  } else if (upper_str == "FUNCTION") {
    return ExpressionType::kFunction;
  } else if (upper_str == "HASH_RANGE") {
    return ExpressionType::kHashRange;
  } else if (upper_str == "OPERATOR_CASE_EXPR") {
    return ExpressionType::kOperatorCaseExpr;
  } else if (upper_str == "OPERATOR_NULLIF") {
    return ExpressionType::kOperatorNullIf;
  } else if (upper_str == "OPERATOR_COALESCE") {
    return ExpressionType::kOperatorCoalesce;
  } else if (upper_str == "ROW_SUBQUERY") {
    return ExpressionType::kRowSubQuery;
  } else if (upper_str == "SELECT_SUBQUERY") {
    return ExpressionType::kSelectSubQuery;
  } else if (upper_str == "STAR") {
    return ExpressionType::kStar;
  } else if (upper_str == "PLACEHOLDER") {
    return ExpressionType::kPlaceholder;
  } else if (upper_str == "COLUMN_REF") {
    return ExpressionType::kColumnRef;
  } else if (upper_str == "FUNCTION_REF") {
    return ExpressionType::kFunctionRef;
  } else if (upper_str == "CAST") {
    return ExpressionType::kCast;
  }

  return ExpressionType::kInvalid;
}

std::string TypeIdToString(TypeId type) {
  switch (type) {
    case TypeId::kInvalid:
      return "INVALID";
    case TypeId::kParameterOffset:
      return "PARAMETER_OFFSET";
    case TypeId::kBoolean:
      return "BOOLEAN";
    case TypeId::kTinyInt:
      return "TINYINT";
    case TypeId::kSmallInt:
      return "SMALLINT";
    case TypeId::kInteger:
      return "INTEGER";
    case TypeId::kBigInt:
      return "BIGINT";
    case TypeId::kDecimal:
      return "DECIMAL";
    case TypeId::kTimestamp:
      return "TIMESTAMP";
    case TypeId::kDate:
      return "DATE";
    case TypeId::kVarChar:
      return "VARCHAR";
    case TypeId::kVarBinary:
      return "VARBINARY";
    case TypeId::kArray:
      return "ARRAY";
    case TypeId::kUndefinedType:
      return "UDT";
  }
  return "INVALID";
}

TypeId StringToTypeId(const std::string& str) {
  auto upper_str = StringUtil::Upper(str);
  if (upper_str == "INVALID") {
    return TypeId::kInvalid;
  } else if (upper_str == "PARAMETER_OFFSET") {
    return TypeId::kParameterOffset;
  } else if (upper_str == "BOOLEAN") {
    return TypeId::kBoolean;
  } else if (upper_str == "TINYINT") {
    return TypeId::kTinyInt;
  } else if (upper_str == "SMALLINT") {
    return TypeId::kSmallInt;
  } else if (upper_str == "INTEGER") {
    return TypeId::kInteger;
  } else if (upper_str == "BIGINT") {
    return TypeId::kBigInt;
  } else if (upper_str == "DECIMAL") {
    return TypeId::kDecimal;
  } else if (upper_str == "TIMESTAMP") {
    return TypeId::kTimestamp;
  } else if (upper_str == "DATE") {
    return TypeId::kDate;
  } else if (upper_str == "VARCHAR") {
    return TypeId::kVarChar;
  } else if (upper_str == "ARRAY") {
    return TypeId::kArray;
  } else if (upper_str == "UDT") {
    return TypeId::kUndefinedType;
  }
  return TypeId::kInvalid;
}

}  // namespace zoomdb
