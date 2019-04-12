#!/bin/bash


docker build . --tag so_builder

docker run -v ${PWD}:/sources/ so_builder

sudo chown $(whoami):$(whoami) Image/x*
sudo chmod 777 Image/x*

./run.sh
