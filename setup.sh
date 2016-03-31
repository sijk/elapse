#!/bin/sh

set -e

apt-get update

# PPA for GStreamer 0.10 ffmpeg elements
if [ -z "`apt-cache pkgnames gstreamer0.10-ffmpeg`" ]
then
    apt-get install -y software-properties-common
    add-apt-repository -y ppa:mc3man/trusty-media
    apt-get update
fi

apt-get install -y \
    git \
    subversion \
    build-essential \
    cmake \
    doxygen \
    graphviz \
    openjdk-7-jre-headless \
    qtcreator \
    qttools5-dev \
    qttools5-dev-tools \
    qtdeclarative5-dev \
    libqt5opengl5-dev \
    qt5-default \
    gstreamer0.10-plugins-base \
    gstreamer0.10-plugins-good \
    gstreamer0.10-plugins-bad \
    gstreamer0.10-plugins-ugly \
    gstreamer0.10-tools \
    gstreamer0.10-ffmpeg \
    libgstreamer0.10-dev \
    libgstreamer-plugins-base0.10-dev \
    python2.7-dev \
    python-pip \
    libboost-dev \
    libboost-python-dev \
    libeigen3-dev \
    libopencv-dev

pip install \
    Sphinx \
    sphinxcontrib-doxylink \
    flexmock

# git clone --recursive pontos:/home/shared/git/elapse/elapse-client.git
# cd elapse-client/
# mkdir build
# cd build
# cmake ..
# make
# make rebuild_cache
# make
