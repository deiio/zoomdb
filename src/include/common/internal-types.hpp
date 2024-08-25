/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#pragma once

#include <string>

namespace zoomdb {

/**
 * SQL Value Types.
 */
enum class TypeId {
  kInvalid = 0,
  kParameterOffset,
  kBoolean,
  kTinyInt,
  kSmallInt,
  kInteger,
  kBigInt,
  kDecimal,
  kTimestamp,
  kDate,
  kVarChar,
  kVarBinary,
  kArray,
  kUndefinedType,
};

/**
 * Statement Types.
 */
enum class StatementType {
  kInvalid     = 0,   // invalid statement type
  kSelect      = 1,   // select statement type
  kInsert      = 3,   // insert statement type
  kUpdate      = 4,   // update statement type
  kDelete      = 5,   // delete statement type
  kCreate      = 6,   // create statement type
  kDrop        = 7,   // drop statement type
  kPrepare     = 8,   // prepare statement type
  kExecute     = 9,   // execute statement type
  kRename      = 11,  // rename statement type
  kAlter       = 12,  // alter statement type
  kTransaction = 13,  // transaction state type
  kCopy        = 14,  // copy type
  kAnalyze     = 15,  // analyze type
  kVariableSet = 16,  // variable set statement type
  kCreateFunc  = 17,  // create func statement type
  kExplain     = 18,  // explain statement type
};

/**
 * Predicate Expression Operation Types.
 */
enum class ExpressionType {
  kInvalid                     = 0,

  /*
   * Arithmetic Operators
   * Implicit Numeric Casting: Trying to implement SQL-92.
   * Implicit Character Casting: Trying to implement SQL-92, but not easy...
   * Anyway, use explicit OPERATOR_CAST if you could.
   */

  // left + right (both must be number. implicitly cast)
  kOperatorPlus                = 1,
  // left - right (both must be number, implicitly cast)
  kOperatorMinus               = 2,
  // left * right (both must be number, implicitly cast)
  kOperatorMultiply            = 3,
  // left / right (both must be number, implicitly cast)
  kOperatorDivide              = 4,
  // left || right (both must be char/varchar)
  kOperatorConcat              = 5,
  // left % right (both must be integer)
  kOperatorMod                 = 6,
  // explicitly cast left as right (right is integer in ValueType enum)
  kOperatorCast                = 7,
  // logical not operator
  kOperatorNot                 = 8,
  // exists test operator
  kOperatorExists              = 18,
  // is null operator
  kOperatorIsNull              = 21,
  // is not null operator
  kOperatorIsNotNull           = 22,
  // unary minus operator
  kOperatorUnaryMinus          = 60,

  /**
   * Comparison Operators
   */
  // equal operator between left and right
  kCompareEqual                = 10,
  // not equal operator between left and right
  kCompareNotEqual             = 11,
  // less than operator between left and right
  kCompareLessThan             = 12,
  // greater than operator between left and right
  kCompareGreaterThan          = 13,
  // less than equal operator between left and right
  kCompareLessThanOrEqualTo    = 14,
  // greater than equal operator between left and right
  kCompareGreaterThanOrEqualTo = 15,
  // like operator (left LIKE right). Both children must be string
  kCompareLike                 = 16,
  // not like operator (left LIKE right). Both children must be string
  kCompareNotLike              = 17,
  // in operator [left IN (right1, right2, ...)]
  kCompareIn                   = 19,
  // is distinct from operator
  kCompareDistinctFrom         = 20,

  /**
   * Conjunction Operators
   */
  kConjunctionAnd              = 30,
  kConjunctionOr               = 31,

  /**
   * Values
   */
  kValueConstant               = 40,
  kValueParameter              = 41,
  kValueTuple                  = 42,
  kValueTupleAddress           = 43,
  kValueNull                   = 44,
  kValueVector                 = 45,
  kValueScalar                 = 46,

  /**
   * Aggregates
   */
  kAggregateCount              = 50,
  kAggregateCountStar          = 51,
  kAggregateSum                = 52,
  kAggregateMin                = 53,
  kAggregateMax                = 54,
  kAggregateAvg                = 55,

  /**
   * Functions
   */
  kFunction                    = 100,

  /**
   * Internals added for Elastic
   */
  kHashRange                   = 200,

  /**
   * Operators
   */
  kOperatorCaseExpr            = 302,
  kOperatorNullIf              = 304,
  kOperatorCoalesce            = 305,

  /**
   * Subquery IN/EXISTS
   */
  kRowSubQuery                 = 400,
  kSelectSubQuery              = 401,

  /**
   * Parser
   */
  kStar                        = 500,
  kPlaceholder                 = 501,
  kColumnRef                   = 502,
  kFunctionRef                 = 503,
  kTableRef                    = 504,

  /**
   * Miscellaneous
   */
  kCast                        = 600,

};

ExpressionType StringToExpressionType(const std::string& str);
std::string TypeIdToString(TypeId type);
TypeId StringToTypeId(const std::string& str);

}  // namespace zoomdb
