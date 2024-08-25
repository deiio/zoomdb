/**
 * ZoomDB is a SQL database management system.
 * Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
 * https://furzoom.com
 * https://github.com/deiio/zoomdb
 */

#include "common/printable.hpp"

#include <stdio.h>

namespace zoomdb {

void Printable::Print() { fprintf(stderr, "%s\n", ToString().c_str()); }

}  // namespace zoomdb
