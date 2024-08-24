/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#pragma once

namespace zoomdb {

class Result;

class Database {
 public:
  explicit Database(const char* path);
};

class Connection {
 public:
  explicit Connection(Database& database);

  Result Query(const char* query);

 private:
  Database& db_;
};

class Result {};

}  // namespace zoomdb
