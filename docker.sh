#!/bin/bash

docker build . --tag ${whoami}/so_builder

docker run -v ${PWD}:/sources/ ${whoami}/so_builder

./run.sh
