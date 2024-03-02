#!/usr/bin/env bash

ninja -C build clang-tidy
ninja -C build clang-format
