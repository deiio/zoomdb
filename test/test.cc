/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#include <stdio.h>

#include "zoomdb.h"
#include "common/exception.hpp"
#include "common/internal-types.hpp"

int main() {
  zoomdb_database database;
  zoomdb_connection connection;
  zoomdb_result result;
  const char* query;

  if (zoomdb_open(nullptr, &database) != kZoomDBSuccess) {
    fprintf(stderr, "Database startup failed!\n");
    return 1;
  }

  if (zoomdb_connect(database, &connection) != kZoomDBSuccess) {
    fprintf(stderr, "Database connect failed\n");
    return 1;
  }

  query = "select 57;";
  if (zoomdb_query(connection, query, &result) != kZoomDBSuccess) {
    fprintf(stderr, "Database query failed\n");
    return 1;
  }
/*
  query = "SELECT id FROM tbl;";
  if (zoomdb_query(connection, query, &result) != kZoomDBSuccess) {
    fprintf(stderr, "Database query failed\n");
    return 1;
  }

  query = "SELECT id, id + 1 FROM tbl;";
  if (zoomdb_query(connection, query, &result) != kZoomDBSuccess) {
    fprintf(stderr, "Database query failed\n");
    return 1;
  }

  query = "SELECT "
      "l_returnflag, "
      "l_linestatus, "
      "sum(l_quantity) as sum_qty,"
      "sum(l_extendedprice) as sum_base_price, "
      "sum(l_extendedprice * (1 - l_discount)) as sum_disc_price, "
      "sum(l_extendedprice * (1 - l_discount) * (1 + l_tax)) as sum_charge, "
      "avg(l_quantity) as avg_qty, "
      "avg(l_extendedprice) as avg_price, "
      "avg(l_discount) as avg_disc, "
      "count(*) as count_order "
      "FROM lineitem "
      "WHERE l_shipdate <= '1998-09-02' "
      "GROUP BY l_returnflag, l_linestatus "
      "ORDER BY l_returnfalg, l_linestatus;";
  if (zoomdb_query(connection, query, &result) != kZoomDBSuccess) {
    fprintf(stderr, "Database query failed\n");
    return 1;
  }
*/
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
