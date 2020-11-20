#!/usr/bash
python ./cpplint.py --filter=`cat filter_options` `ls *_src/*.cpp *_src/*.h`

#find -regextype posix-egrep -regex './(server|common|client|editor)_src*\.(h|hpp|c|cpp)'