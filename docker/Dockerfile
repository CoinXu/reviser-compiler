FROM ubuntu:16.04
LABEL description="nodejs linux platform environment" version=1.0 author=coinxu

ENV WORKDIR /opt

ARG NPM_REGISTRY=https://registry.npmjs.org
ARG GITHUB_NAME=coinxu
ARG GITHUB_EMAIL=duanxian0605@gmail.com

USER root

RUN sed -i 's/security.ubuntu.com/mirrors.163.com/g' /etc/apt/sources.list         \
    && sed -i 's/archive.ubuntu.com/mirrors.163.com/g' /etc/apt/sources.list       \
    && apt-get update                                                              \    
    && apt-get install -y git                                                      \
    && git config --global user.email ${GITHUB_EMAIL}                              \
    && git config --global user.name ${GITHUB_NAME}                                \
    && apt-get install -y sudo                                                     \
    && apt-get install -y curl                                                     \
    && apt-get install -y vim                                                      \
    && apt-get install -y build-essential                                          \
    && curl -sL https://deb.nodesource.com/setup_12.x | sudo -E bash -             \
    && apt-get install -y nodejs                                                   \
    && npm install -g npm                                                          \
    && npm config set registry=${NPM_REGISTRY}                                     \        
    && apt-get install -y zsh                                                      \
    && sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" --unattended \
    && exec zsh -l                                                                  \
    && apt-get -y clean

VOLUME ${WORKDIR}

EXPOSE 8080
