# ZoomDB is a SQL database management system.
# Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
# https://furzoom.com
# https://github.com/deiio/zoomdb
#

ADD_EXECUTABLE(test test.cc)
TARGET_LINK_LIBRARIES(test zoomdb pthread)
