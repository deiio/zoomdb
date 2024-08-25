/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#pragma once

#include <cstdio>
#include <stdexcept>
#include <string>

namespace zoomdb {

/**
 * Exception Types
 */
enum class ExceptionType {
  kInvalid          = 0,   // invalid type
  kOutOfRange       = 1,   // value out of range error
  kConversion       = 2,   // conversion/casting error
  kUnknownType      = 3,   // unknown type
  kDecimal          = 4,   // decimal related
  kMismatchType     = 5,   // type mismatch
  kDivideByZero     = 6,   // divide by 0
  kObjectSize       = 7,   // object size exceeded
  kIncompatibleType = 8,   // incompatible for operation
  kSerialization    = 9,   // serialization
  kTransaction      = 10,  // transaction management
  kNotImplemented   = 11,  // method not implemented
  kExpression       = 12,  // expression parsing
  kCatalog          = 13,  // catalog related
  kParser           = 14,  // parser related
  kPlanner          = 15,  // planner related
  kScheduler        = 16,  // scheduler related
  kExecutor         = 17,  // executor related
  kConstraint       = 18,  // constraint related
  kIndex            = 19,  // index related
  kStat             = 20,  // stat related
  kConnection       = 21,  // connection related
  kSyntax           = 22,  // syntax related
  kSettings         = 23,  // settings related
  kBinder           = 24,  // binder related
  kNetwork          = 25,  // network related
  kOptimizer        = 26,  // optimizer related
  kNullPointer      = 27,  // nullptr exception
};

class Exception : public std::runtime_error {
 public:
  explicit Exception(std::string message);
  Exception(ExceptionType type, const std::string& message);

  std::string ExceptionTypeToString(ExceptionType type) const;
  std::string GetMessage() const { return exception_message_; }

  static void PrintStackTrace(FILE* out = ::stderr, int32_t max_frames = 63);

  friend std::ostream& operator<<(std::ostream& os, const Exception& e);

 protected:
  void Format(va_list ap);

 private:
  ExceptionType type_;
  std::string exception_message_;
};

}  // namespace zoomdb
