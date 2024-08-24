/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#include "zoomdb.hpp"

#include "parser/parser.hpp"

namespace zoomdb {

Database::Database(const char* path) {
  (void)path;
}

Connection::Connection(Database& database)
  : db_(database) {
  (void)db_;
}

Result Connection::Query(const char* query) {
  Parser parser;
  parser.ParseQuery(query);

  return Result{};
}

}  // namespace zoomdb
