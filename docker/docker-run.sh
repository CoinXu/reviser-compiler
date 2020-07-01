#!/usr/bin/bash

DOCKER_CONTAINER_NAME=reviser_compiler

docker rm ${DOCKER_CONTAINER_NAME}
docker run \
    -td \
    -u root \
    -v /Users/apple/workspace:/opt/workspace \
    --name ${DOCKER_CONTAINER_NAME} \
    -p 8080:8080 \
    coinxu_ubuntu:1.0 \
    sh -c "while true; do sleep 10; done"
