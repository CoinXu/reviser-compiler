#!/usr/bin/bash

DOCKER_CONTAINER_NAME=reviser_compiler

docker rm ${DOCKER_CONTAINER_NAME}
docker run \
    -td \
    -u root \
    -v $(dirname $(pwd)):/opt/workspace/reviser-compiler \
    --name ${DOCKER_CONTAINER_NAME} \
    -p 8080:8080 \
    coinxu_ubuntu:1.0 \
    sh -c "while true; do sleep 10; done"
    # node -e "var http = require('http'); \
        # var app = http.createServer((req, res) => res.end('node http server')); \
        # app.listen(8080, '0.0.0.0');"
