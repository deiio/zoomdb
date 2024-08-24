# ZoomDB is a SQL database management system.
# Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
# https://furzoom.com
# https://github.com/deiio/zoomdb
#

ADD_SUBDIRECTORY(main)
ADD_SUBDIRECTORY(parser)

ADD_LIBRARY(zoomdb STATIC ${ZOOMDB_OBJECT_FILES})
TARGET_LINK_LIBRARIES(zoomdb pg_query)
