/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#include <stdio.h>

#include "zoomdb.h"

int main() {
  zoomdb_database database;
  zoomdb_connection connection;
  zoomdb_result result;

  if (zoomdb_open(nullptr, &database) != kZoomDBSuccess) {
    fprintf(stderr, "Database startup failed!\n");
    return 1;
  }

  if (zoomdb_connect(database, &connection) != kZoomDBSuccess) {
    fprintf(stderr, "Database connect failed\n");
    return 1;
  }

  if (zoomdb_query(connection, "select 57;", &result) != kZoomDBSuccess) {
    fprintf(stderr, "Database query failed\n");
    return 1;
  }

  if (zoomdb_disconnect(connection) != kZoomDBSuccess) {
    fprintf(stderr, "Database disconnect failed\n");
    return 1;
  }

  if (zoomdb_close(database) != kZoomDBSuccess) {
    fprintf(stderr, "Database close failed\n");
    return 1;
  }

  return 0;
}
