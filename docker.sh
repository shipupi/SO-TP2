#!/bin/bash


docker build . --tag $(whoami)/so_builder

docker run -v ${PWD}:/sources/ $(whoami)/so_builder

sudo chown $(whoami):$(whoami) Image/x*
sudo chmod 777 Image/x*

./run.sh
