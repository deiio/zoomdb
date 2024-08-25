/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#pragma once

#include <string>
#include <vector>

namespace zoomdb {

/**
 * String Utility Functions
 *
 * Note that these are not the most efficient implementations (i.e., they
 * copy memory) and therefore they should only be used for debug messages
 * and other such things.
 */
class StringUtil {
 public:
  /**
   * Returns true if the needle string exists in the haystack.
   */
  static bool Contains(const std::string& haystack, const std::string& needle);

  /**
   * Returns true if the target string starts with the given prefix.
   */
  static bool StartsWith(const std::string& str, const std::string& prefix);

  /**
   * Returns true if the target string ends with the given suffix.
   */
  static bool EndsWith(const std::string& str, const std::string& suffix);

  /**
   * Repeat a string multiple times.
   */
  static std::string Repeat(const std::string& str, std::size_t n);

  /**
   * Split the input string based on newline char.
   */
  static std::vector<std::string> Split(const std::string& str, char delimiter);

  /**
   * Split the input string into a vector of strings based on the split
   * string given us
   */
  static std::vector<std::string> Split(const std::string& input,
                                        const std::string& delimiter);
  /**
   * Join multiple strings into one string. Components are concatenated by
   * the given separator.
   */
  static std::string Join(const std::vector<std::string>& input,
                          const std::string& separator);

  /**
   * Append the prefix to the beginning of each line in str.
   */
  static std::string Prefix(const std::string& str, const std::string& prefix);

  /**
   * Return a string that formats the given number of bytes into the
   * appropriate kilobyte, megabyte, gigabyte representation.
   */
  static std::string FormatSize(long bytes);

  /**
   * Wrap the given string with the control characters to make the text
   * appear bold in the console.
   */
  static std::string Bold(const std::string& str);

  /**
   * Convert a string to its uppercase form.
   */
  static std::string Upper(const std::string& str);

  /**
   * Convert a string to its lowercase form.
   */
  static std::string Lower(const std::string& str);

  /**
   * Format a string using printf semantics.
   */
  static std::string Format(const std::string fmt_str, ...);
  static std::string VFormat(const std::string fmt_str, va_list ap);

  /**
   * Remove the whitespace char in the right end of the string.
   */
  static void RTrim(std::string& str);

  /**
   * Return a string with num_indent spaces.
   */
  static std::string Indent(int num_indent);

  /**
   * Return a new string that has stripped all occurrences of the given
   * character from the str.
   *
   * NOTE: This function copies the input string into a new string, which
   * is wasteful. Don't use this for performance critical code, please!
   */
  static std::string Strip(const std::string& str, char c);
};

}  // namespace zoomdb
