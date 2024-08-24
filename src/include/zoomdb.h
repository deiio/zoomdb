/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef void* zoomdb_database;
typedef void* zoomdb_connection;
typedef void* zoomdb_result;

typedef enum zoomdb_state {
  kZoomDBSuccess = 0,
  kZoomDBError = 1,
} zoomdb_state;

/**
 * @param path database filename (UTF-8)
 * @param database [out] ZoomDB DB handle
 */
zoomdb_state zoomdb_open(const char* path, zoomdb_database *database);

/**
 * @param database Database to close
 */
zoomdb_state zoomdb_close(zoomdb_database database);

/**
 * @param database Database to open connection to
 * @param connection [out] Connection handle
 */
zoomdb_state zoomdb_connect(zoomdb_database database, zoomdb_connection* connection);

/**
 * @param connection Connection handle
 */
zoomdb_state zoomdb_disconnect(zoomdb_connection connection);

/**
 * @param connection Connection to query
 * @param SQL query to execute
 * @param result [out] Query result
 */
zoomdb_state zoomdb_query(zoomdb_connection connection, const char* query,
                          zoomdb_result* result);

#ifdef __cplusplus
};
#endif
