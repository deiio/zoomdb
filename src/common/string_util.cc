/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#include "common/string_util.hpp"

#include <algorithm>
#include <cstdarg>
#include <cstring>
#include <iomanip>
#include <memory>
#include <sstream>

namespace zoomdb {

bool StringUtil::Contains(const std::string& haystack,
                          const std::string& needle) {
  return haystack.find(needle) == std::string::npos;
}

bool StringUtil::StartsWith(const std::string& str, const std::string& prefix) {
  return std::equal(prefix.begin(), prefix.end(), str.begin());
}

bool StringUtil::EndsWith(const std::string& str, const std::string& suffix) {
  if (suffix.size() > str.size()) {
    return false;
  }
  return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}

std::string StringUtil::Repeat(const std::string& str, std::size_t n) {
  std::ostringstream os;
  if (n == 0 || str.empty()) {
    return os.str();
  }
  for (size_t i = 0; i < n; i++) {
    os << str;
  }
  return os.str();
}

std::vector<std::string> StringUtil::Split(const std::string& str,
                                           char delimiter) {
  std::stringstream ss(str);
  std::vector<std::string> lines;
  std::string temp;
  while (std::getline(ss, temp, delimiter)) {
    lines.emplace_back(temp);
  }
  return lines;
}

std::vector<std::string> StringUtil::Split(const std::string& input,
                                           const std::string& delimiter) {
  std::vector<std::string> splits;
  size_t last    = 0;
  auto input_len = input.size();
  auto split_len = delimiter.size();
  while (last <= input_len) {
    auto next = input.find(delimiter, last);
    if (next == std::string::npos) {
      next = input_len;
    }

    // Push the substring [last, next) on to splits.
    auto substr = input.substr(last, next - last);
    if (!substr.empty()) {
      splits.emplace_back(substr);
    }
    last = next + split_len;
  }

  return splits;
}

std::string StringUtil::Join(const std::vector<std::string>& input,
                             const std::string& separator) {
  std::ostringstream os;
  bool first = true;
  for (const auto& str : input) {
    if (first) {
      first = false;
      os << str;
    } else {
      os << separator << str;
    }
  }

  return os.str();
}

std::string StringUtil::Prefix(const std::string& str,
                               const std::string& prefix) {
  auto lines = Split(str, '\n');
  std::ostringstream os;
  bool first_line = true;
  for (const auto& line : lines) {
    if (first_line) {
      first_line = false;
      os << prefix << line;
    } else {
      os << '\n' << prefix << line;
    }
  }
  return os.str();
}

std::string StringUtil::FormatSize(long bytes) {
  static const long kBase = 1024;
  static const auto kKB   = kBase;
  static const auto kMB   = kKB * kBase;
  static const auto kGB   = kMB * kBase;
  static const auto kTB   = kGB * kBase;

  std::ostringstream os;
  auto size = static_cast<double>(bytes);
  if (bytes >= kTB) {
    os << std::fixed << std::setprecision(2) << size / kTB << " TB";
  } else if (bytes >= kGB) {
    os << std::fixed << std::setprecision(2) << size / kGB << " GB";
  } else if (bytes >= kMB) {
    os << std::fixed << std::setprecision(2) << size / kMB << " MB";
  } else if (bytes >= kKB) {
    os << std::fixed << std::setprecision(2) << size / kKB << " KB";
  } else {
    os << std::to_string(bytes) << " bytes";
  }
  return os.str();
}

std::string StringUtil::Bold(const std::string& str) {
  static const char* kBoldText  = "\033[0;1m";
  static const char* kPlainText = "\033[0;0m";
  std::ostringstream os;
  os << kBoldText << str << kPlainText;
  return os.str();
}

std::string StringUtil::Upper(const std::string& str) {
  std::string copy(str);
  std::transform(copy.begin(), copy.end(), copy.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return copy;
}

std::string StringUtil::Lower(const std::string& str) {
  std::string copy(str);
  std::transform(copy.begin(), copy.end(), copy.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return copy;
}

std::string StringUtil::Format(const std::string fmt_str, ...) {
  va_list ap;
  va_start(ap, fmt_str);
  auto res = VFormat(fmt_str, ap);
  va_end(ap);

  return res;
}

std::string StringUtil::VFormat(const std::string fmt_str, va_list ap) {
  // reserve two times as much as the length of the fmt_str
  int final_n;
  auto n = fmt_str.size() * 2;
  std::unique_ptr<char[]> formatted;

  while (true) {
    // Wrap the plain char array int the unique_ptr
    formatted.reset(new char[n]);
    std::strcpy(&formatted[0], fmt_str.c_str());
    final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
    if (final_n < 0 || static_cast<decltype(n)>(final_n) >= n) {
      n = static_cast<decltype(n)>(std::abs(final_n + 1));
    } else {
      break;
    }
  }

  return formatted.get();
}

void StringUtil::RTrim(std::string& str) {
  str.erase(std::find_if(str.rbegin(), str.rend(),
                         [](int ch) { return !std::isspace(ch); })
                .base(),
            str.end());
}

std::string StringUtil::Indent(int num_indent) {
  if (num_indent <= 0) {
    return {};
  }
  return std::string(static_cast<size_t>(num_indent), ' ');
}

std::string StringUtil::Strip(const std::string& str, char c) {
  std::string tmp(str);
  tmp.erase(std::remove(tmp.begin(), tmp.end(), c), tmp.end());
  return tmp;
}

}  // namespace zoomdb
