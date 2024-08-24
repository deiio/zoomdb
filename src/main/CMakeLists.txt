# ZoomDB is a SQL database management system.
# Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
# https://furzoom.com
# https://github.com/deiio/zoomdb
#

ADD_LIBRARY(zoomdb_main OBJECT
    zoomdb.cc
    zoomdb-c.cc
)

SET(ZOOMDB_OBJECT_FILES ${ZOOMDB_OBJECT_FILES}
    $<TARGET_OBJECTS:zoomdb_main> PARENT_SCOPE)
