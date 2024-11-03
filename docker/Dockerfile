FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
SHELL ["/bin/bash", "-ci"]

RUN apt update &&\
    apt install git build-essential cmake libjsoncpp-dev -y

ADD . /tape_sort

WORKDIR /tape_sort

