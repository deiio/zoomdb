# ZoomDB is a SQL database management system.
# Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
# https://furzoom.com
# https://github.com/deiio/zoomdb
#

ADD_LIBRARY(zoomdb_parser OBJECT
    parser.cc
)

SET(ZOOMDB_OBJECT_FILES ${ZOOMDB_OBJECT_FILES}
    $<TARGET_OBJECTS:zoomdb_parser> PARENT_SCOPE)
