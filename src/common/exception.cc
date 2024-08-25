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

}  // namespace zoomdb
