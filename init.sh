#!/usr/bin/env bash

git submodule update --init --recursive
meson setup build --buildtype=debugoptimized --reconfigure
