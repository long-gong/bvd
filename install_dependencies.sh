#!/usr/bin/env bash

set -e

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
# the following two lines are added for travis-ci
sudo add-apt-repository -y universe
sudo apt-get -q update
sudo apt-get install -y libboost-graph-dev libeigen3-dev
elif [[ "$OSTYPE" == "darwin"* ]]; then
    brew list boost || brew install boost
    brew list eigen || brew install eigen
fi