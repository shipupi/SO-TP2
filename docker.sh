#!/bin/bash


docker build . --tag so_builder

docker run -v ${PWD}:/root/ so_builde	r

chown $(whoami):$(whoami) Image/x*
chmod 777 Image/x*

if [[ "$1" = "gdb" ]]; then
  ./run.sh gdb
else
  ./run.sh
fi

