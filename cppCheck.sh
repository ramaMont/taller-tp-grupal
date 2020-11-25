#!/bin/bash
cppcheck --enable=all ./server_src/*.cpp ./client_src/*.cpp ./common_src/*.cpp ./editor_src/*.cpp
