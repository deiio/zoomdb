/**
* ZoomDB is a SQL database management system.
* Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
* https://furzoom.com
* https://github.com/deiio/zoomdb
*/

#pragma once

#include <string>

namespace zoomdb {

class Printable {
 public:
  virtual ~Printable() = default;

  /**
   * @brief Get the info about the object.
   */
  virtual std::string ToString() const = 0;

  void Print();
};

}  // namespace zoomdb
