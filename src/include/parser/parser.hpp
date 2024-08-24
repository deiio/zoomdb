/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#pragma once

namespace zoomdb {

class Parser {
 public:
  Parser();

  void ParseQuery(const char* query);
};

}  // namespace zoomdb
