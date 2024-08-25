/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#include "common/exception.hpp"

#include <cxxabi.h>
#include <execinfo.h>

#include <cstdio>
#include <memory>

#include "common/string_util.hpp"

namespace zoomdb {

#define FormatConstruct(msg) \
  va_list ap;                \
  va_start(ap, msg);         \
  Format(ap);                \
  va_end(ap);

Exception::Exception(std::string message)
    : std::runtime_error(message),
      type_(ExceptionType::kInvalid),
      exception_message_(std::move(message)) {}

Exception::Exception(ExceptionType type, const std::string& message)
    : std::runtime_error(message),
      type_(type),
      exception_message_(ExceptionTypeToString(type) + ": " + message) {}

std::string Exception::ExceptionTypeToString(ExceptionType type) const {
  switch (type) {
    case ExceptionType::kInvalid:
      return "Invalid";
    case ExceptionType::kOutOfRange:
      return "Out of Range";
    case ExceptionType::kConversion:
      return "Conversion";
    case ExceptionType::kUnknownType:
      return "Unknown Type";
    case ExceptionType::kDecimal:
      return "Decimal";
    case ExceptionType::kMismatchType:
      return "Mismatch Type";
    case ExceptionType::kDivideByZero:
      return "Divide by Zero";
    case ExceptionType::kObjectSize:
      return "Object Size";
    case ExceptionType::kIncompatibleType:
      return "Incompatible Type";
    case ExceptionType::kSerialization:
      return "Serialization";
    case ExceptionType::kTransaction:
      return "Transaction Context";
    case ExceptionType::kNotImplemented:
      return "Not Implemented";
    case ExceptionType::kExpression:
      return "Expression";
    case ExceptionType::kCatalog:
      return "Catalog";
    case ExceptionType::kParser:
      return "Parser";
    case ExceptionType::kPlanner:
      return "Planner";
    case ExceptionType::kScheduler:
      return "Scheduler";
    case ExceptionType::kExecutor:
      return "Executor";
    case ExceptionType::kConstraint:
      return "Constraint";
    case ExceptionType::kIndex:
      return "Index";
    case ExceptionType::kStat:
      return "Stat";
    case ExceptionType::kConnection:
      return "Connection";
    case ExceptionType::kSyntax:
      return "Syntax";
    case ExceptionType::kSettings:
      return "Settings";
    case ExceptionType::kBinder:
      return "Optimizer";
    case ExceptionType::kNetwork:
      return "Network";
    case ExceptionType::kOptimizer:
      return "Optimizer";
    case ExceptionType::kNullPointer:
      return "Null Pointer";
    default:
      return "Unknown";
  }
}

void Exception::PrintStackTrace(FILE* out, int32_t max_frames) {
  // Based on: http://panthema.net/2008/0901-stacktrace-demangled/
  ::fprintf(out, "Stack Trace:\n");
  // Storage array for stack trace address data
  void* addr_list[max_frames + 1];
  // Retrieve current stack addresses
  int addr_len = backtrace(addr_list, max_frames + 1);
  if (addr_len == 0) {
    ::fprintf(out, "  <empty, possibly corrupt>\n");
    return;
  }

  // resolve addresses into strings containing "filename(function+address)"
  char** symbol_list    = backtrace_symbols(addr_list, addr_len);

  // allocate string which will be filled with the demangled function name
  size_t func_name_size = 1024;
  std::unique_ptr<char> func_name(new char[func_name_size]);

  // iterate over the returned symbol lines. Skip the first, it is the address
  // of this function.
  for (int i = 1; i < addr_len; i++) {
    char* begin_name   = nullptr;
    char* begin_offset = nullptr;
    char* end_offset   = nullptr;

    // find parentheses and +address offset surrounding the mangled name:
    // ./module(function+0x12c) [0x8048568]
    for (char* p = symbol_list[i]; *p; p++) {
      if (*p == '(') {
        begin_name = p;
      } else if (*p == '+') {
        begin_offset = p;
      } else if (*p == ')' && begin_offset) {
        end_offset = p;
        break;
      }
    }

    if (begin_name && begin_offset && end_offset && begin_name < begin_offset) {
      *begin_name++   = '\0';
      *begin_offset++ = '\0';
      *end_offset     = '\0';

      // mangled name is now in [begin_name, begin_offset) and caller
      // offset in [begin_offset, end_offset), now apply __cxa_demangle():
      int status;
      char* ret = abi::__cxa_demangle(begin_name, func_name.get(),
                                      &func_name_size, &status);
      if (status == 0) {
        // use possibly realloc()-ed string
        func_name.reset(ret);
        ::fprintf(out, "  %s : %s+%s\n", symbol_list[i], func_name.get(),
                  begin_offset);
      } else {
        // demangle failed. Output function name as a C function with
        // no arguments.
        ::fprintf(out, "  %s: %s()+%s\n", symbol_list[i], begin_name,
                  begin_offset);
      }
    } else {
      // couldn't parse the line? print the whole line.
      ::fprintf(out, "  %s\n", symbol_list[i]);
    }
  }
}

void Exception::Format(va_list ap) {
  exception_message_ = StringUtil::VFormat(exception_message_, ap);
}

/**
 * class ValueOutOfRangeException
 */

ValueOutOfRangeException::ValueOutOfRangeException(int64_t value,
                                                   const TypeId& orig_type,
                                                   const TypeId& new_type)
    : Exception(
          ExceptionType::kConversion,
          "Type " + TypeIdToString(orig_type) + " with value " +
              std::to_string(value) + " can't be cast as " +
              TypeIdToString(new_type) +
              " because the value is out of range for the destination type") {}

ValueOutOfRangeException::ValueOutOfRangeException(double value,
                                                   const TypeId& orig_type,
                                                   const TypeId& new_type)
    : Exception(
          ExceptionType::kConversion,
          "Type " + TypeIdToString(orig_type) + " with value " +
              std::to_string(value) + " can't be cast as " +
              TypeIdToString(new_type) +
              " because the value is out of range for the destination type") {}

ValueOutOfRangeException::ValueOutOfRangeException(const TypeId& var_type,
                                                   size_t length)
    : Exception(ExceptionType::kOutOfRange,
                "The value is too long to fit into type " +
                    TypeIdToString(var_type) + "(" + std::to_string(length) +
                    ")") {}

/**
 * Class CastException
 */

CastException::CastException(const TypeId& orig_type, const TypeId& new_type)
    : Exception(ExceptionType::kConversion,
                "Type " + TypeIdToString(orig_type) + " can't be cast as " +
                    TypeIdToString(new_type)) {}

/**
 * Class ConversionException
 */

ConversionException::ConversionException(std::string msg, ...)
    : Exception(ExceptionType::kConversion, msg) {
  FormatConstruct(msg);
}

/**
 * Class UnknownTypeException
 */

UnknownTypeException::UnknownTypeException(int type, std::string msg, ...)
    : Exception(ExceptionType::kUnknownType,
                "Unknown type " + std::to_string(type) + msg) {
  FormatConstruct(msg);
}

/**
 * Class DecimalException
 */

DecimalException::DecimalException(std::string msg, ...)
    : Exception(ExceptionType::kDecimal, msg) {
  FormatConstruct(msg);
}

/**
 * Class TypeMismatchException
 */

TypeMismatchException::TypeMismatchException(const std::string& msg,
                                             const TypeId& t1, const TypeId& t2)
    : Exception(ExceptionType::kMismatchType,
                "Type " + TypeIdToString(t1) + " does not match with " +
                    TypeIdToString(t2) + " " + msg) {}

/**
 * Class NumericValueOutOfRangeException
 */

NumericValueOutOfRangeException::NumericValueOutOfRangeException(
    const std::string& msg, int type)
    : Exception(ExceptionType::kOutOfRange, msg + " " + std::to_string(type)) {}

/**
 * Class DivideByZeroException
 */

DivideByZeroException::DivideByZeroException(std::string msg, ...)
    : Exception(ExceptionType::kDivideByZero, msg) {
  FormatConstruct(msg);
}

/**
 * Class ObjectSizeException
 */

ObjectSizeException::ObjectSizeException(const std::string& msg)
    : Exception(ExceptionType::kObjectSize, msg) {}

/**
 * Class IncompatibleTypeException
 */

IncompatibleTypeException::IncompatibleTypeException(int type,
                                                     const std::string& msg)
    : Exception(ExceptionType::kIncompatibleType,
                "Incompatible type " +
                    TypeIdToString(static_cast<TypeId>(type)) + " " + msg) {}

/**
 * Class SerializationException
 */

SerializationException::SerializationException(const std::string& msg)
    : Exception(ExceptionType::kSerialization, msg) {}

/**
 * Class TransactionException
 */

TransactionException::TransactionException(const std::string& msg)
    : Exception(ExceptionType::kTransaction, msg) {}

/**
 * Class NotImplementationException
 */

NotImplementationException::NotImplementationException(std::string msg, ...)
    : Exception(ExceptionType::kNotImplemented, msg) {
  FormatConstruct(msg);
}

/**
 * Class ExpressionException
 */

ExpressionException::ExpressionException(std::string msg, ...)
    : Exception(ExceptionType::kExpression, msg) {
  FormatConstruct(msg);
}

/**
 * Class CatalogException
 */

CatalogException::CatalogException(std::string msg, ...)
    : Exception(ExceptionType::kCatalog, msg) {
  FormatConstruct(msg);
}

/**
 * Class ParserException
 */

ParserException::ParserException(std::string msg, ...)
    : Exception(ExceptionType::kParser, msg) {
  FormatConstruct(msg);
}

/**
 * Class PlannerException
 */

PlannerException::PlannerException(std::string msg, ...)
    : Exception(ExceptionType::kPlanner, msg) {
  FormatConstruct(msg);
}

/**
 * Class SchedulerException
 */

SchedulerException::SchedulerException(std::string msg, ...)
    : Exception(ExceptionType::kScheduler, msg) {
  FormatConstruct(msg);
}

/**
 * Class ExecutorException
 */

ExecutorException::ExecutorException(std::string msg, ...)
    : Exception(ExceptionType::kExecutor, msg) {
  FormatConstruct(msg);
}

/**
 * Class SyntaxException
 */

SyntaxException::SyntaxException(std::string msg, ...)
    : Exception(ExceptionType::kSyntax, msg) {
  FormatConstruct(msg);
}

/**
 * Class ConstraintException
 */

ConstraintException::ConstraintException(std::string msg, ...)
    : Exception(ExceptionType::kConstraint, msg) {
  FormatConstruct(msg);
}

/**
 * Class IndexException
 */

IndexException::IndexException(std::string msg, ...)
    : Exception(ExceptionType::kIndex, msg) {
  FormatConstruct(msg);
}

/**
 * Class StatException
 */

StatException::StatException(std::string msg, ...)
    : Exception(ExceptionType::kStat, msg) {
  FormatConstruct(msg);
}

/**
 * Class ConnectionException
 */

ConnectionException::ConnectionException(std::string msg, ...)
    : Exception(ExceptionType::kConnection, msg) {
  FormatConstruct(msg);
}

/**
 * Class NetworkProcessException
 */

NetworkProcessException::NetworkProcessException(std::string msg, ...)
    : Exception(ExceptionType::kNetwork, msg) {
  FormatConstruct(msg);
}

/**
 * Class SettingsException
 */

SettingsException::SettingsException(std::string msg, ...)
    : Exception(ExceptionType::kSettings, msg) {
  FormatConstruct(msg);
}

/**
 * Class BinderException
 */
BinderException::BinderException(std::string msg, ...)
    : Exception(ExceptionType::kBinder, msg) {
  FormatConstruct(msg);
}

/**
 * Class OptimizerException
 */

OptimizerException::OptimizerException(std::string msg, ...)
    : Exception(ExceptionType::kOptimizer, msg) {
  FormatConstruct(msg);
}

/**
 * Class NullPointerException
 */

NullPointerException::NullPointerException(std::string msg, ...)
    : Exception(ExceptionType::kNullPointer, msg) {
  FormatConstruct(msg);
}

}  // namespace zoomdb
