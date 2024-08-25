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

#include "common/internal-types.hpp"

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
  Exception() = delete;

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

/**
 * Exception derived classes.
 */

class ValueOutOfRangeException : public Exception {
 public:
  ValueOutOfRangeException(int64_t value, const TypeId& orig_type,
                           const TypeId& new_type);
  ValueOutOfRangeException(double value, const TypeId& orig_type,
                           const TypeId& new_type);
  ValueOutOfRangeException(const TypeId& var_type, size_t length);
};

class CastException : public Exception {
 public:
  CastException(const TypeId& orig_type, const TypeId& new_type);
};

class ConversionException : public Exception {
 public:
  ConversionException(std::string msg, ...);
};

class UnknownTypeException : public Exception {
 public:
  UnknownTypeException(int type, std::string msg, ...);
};

class DecimalException : public Exception {
 public:
  DecimalException(std::string msg, ...);
};

class TypeMismatchException : public Exception {
 public:
  TypeMismatchException(const std::string& msg, const TypeId& t1,
                        const TypeId& t2);
};

class NumericValueOutOfRangeException : public Exception {
 public:
  NumericValueOutOfRangeException(const std::string& msg, int type);

  static const int kUnderflow = 1;
  static const int kOverflow  = 2;
};

class DivideByZeroException : public Exception {
 public:
  DivideByZeroException(std::string msg, ...);
};

class ObjectSizeException : public Exception {
 public:
  ObjectSizeException(const std::string& msg);
};

class IncompatibleTypeException : public Exception {
 public:
  IncompatibleTypeException(int type, const std::string& msg);
};

class SerializationException : public Exception {
 public:
  SerializationException(const std::string& msg);
};

class TransactionException : public Exception {
 public:
  TransactionException(const std::string& msg);
};

class NotImplementationException : public Exception {
 public:
  NotImplementationException(std::string msg, ...);
};

class ExpressionException : public Exception {
 public:
  ExpressionException(std::string msg, ...);
};

class CatalogException : public Exception {
 public:
  CatalogException(std::string msg, ...);
};

class ParserException : public Exception {
 public:
  ParserException(std::string msg, ...);
};

class PlannerException : public Exception {
 public:
  PlannerException(std::string msg, ...);
};

class SchedulerException : public Exception {
 public:
  SchedulerException(std::string msg, ...);
};

class ExecutorException : public Exception {
 public:
  ExecutorException(std::string msg, ...);
};

class SyntaxException : public Exception {
 public:
  SyntaxException(std::string msg, ...);
};

class ConstraintException : public Exception {
 public:
  ConstraintException(std::string msg, ...);
};

class IndexException : public Exception {
 public:
  IndexException(std::string msg, ...);
};

class StatException : public Exception {
 public:
  StatException(std::string msg, ...);
};

class ConnectionException : public Exception {
 public:
  ConnectionException(std::string msg, ...);
};

class NetworkProcessException : public Exception {
 public:
  NetworkProcessException(std::string msg, ...);
};

class SettingsException : public Exception {
 public:
  SettingsException(std::string msg, ...);
};

class BinderException : public Exception {
 public:
  BinderException(std::string msg, ...);
};

class OptimizerException : public Exception {
 public:
  OptimizerException(std::string msg, ...);
};

class NullPointerException : public Exception {
 public:
  NullPointerException(std::string msg, ...);
};

}  // namespace zoomdb
