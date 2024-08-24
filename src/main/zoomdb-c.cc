/*
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#include "zoomdb.h"

#include "zoomdb.hpp"

using namespace zoomdb;

zoomdb_state zoomdb_open(const char* path, zoomdb_database *database) {
  auto* db = new Database(path);
  *database = db;
  return kZoomDBSuccess;
}

zoomdb_state zoomdb_close(zoomdb_database database) {
  if (database) {
    auto* db = static_cast<Database*>(database);
    delete db;
  }
  return kZoomDBSuccess;
}

zoomdb_state zoomdb_connect(zoomdb_database database, zoomdb_connection* connection) {
  auto* db = static_cast<Database*>(database);
  auto* conn = new Connection(*db);
  *connection = conn;
  return kZoomDBSuccess;
}

zoomdb_state zoomdb_disconnect(zoomdb_connection connection) {
  if (connection) {
    auto* conn = static_cast<Connection*>(connection);
    delete conn;
  }
  return kZoomDBSuccess;
}

zoomdb_state zoomdb_query(zoomdb_connection connection, const char* query,
                          zoomdb_result* result) {
  auto* conn = static_cast<Connection*>(connection);
  auto res = conn->Query(query);
  (void)res;
  *result = nullptr;
  return kZoomDBSuccess;
}
