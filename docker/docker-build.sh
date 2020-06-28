#!/usr/bin/bash

docker build \
    --build-arg GITHUB_NAME=coinxu \
    --build-arg GITHUB_EMAIL=duanxian0605@gmail.com \
    -t coinxu_ubuntu:1.0 .