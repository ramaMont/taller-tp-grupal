#!/bin/sh
mkdir build
cd build
cmake ..
make
cd ..
mkdir -m 777 -p /etc/Wolfenstein
mkdir -m 777 -p /var/Wolfenstein
install -m 777 ./build/client_src/Wolfenstein_client_run /usr/bin
install -m 777 ./build/server_src/Wolfenstein_server_run /usr/bin
install -m 777 ./build/editor_src/Wolfenstein_editor_run /usr/bin
cp -r data /var/Wolfenstein