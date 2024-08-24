/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#include "parser/parser.hpp"

#include <stdio.h>

#include "pg_query.h"

namespace zoomdb {

Parser::Parser() {}

void Parser::ParseQuery(const char* query) {
  auto result = pg_query_parse(query);
  if (result.error) {
    fprintf(stderr, "%s at %d\n", result.error->message,
            result.error->cursorpos);
  } else {
    fprintf(stderr, "Successfully parsed query.\n");
  }
  pg_query_free_parse_result(result);
}

}  // namespace zoomdb
