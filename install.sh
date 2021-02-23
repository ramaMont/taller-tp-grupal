#!/bin/sh
mkdir build
cd build
cmake ..
make
cd ..
mkdir -m 777 -p ~/.Wolfenstein
sudo install -m 777 ./build/client_src/Wolfenstein_client_run /usr/bin
sudo install -m 777 ./build/server_src/Wolfenstein_server_run /usr/bin
sudo install -m 777 ./build/editor_src/Wolfenstein_editor_run /usr/bin
cp -r data ~/.Wolfenstein/
sudo chmod 777 ~/.Wolfenstein/data/maps/*