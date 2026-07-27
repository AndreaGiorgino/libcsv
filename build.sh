#!/usr/bin/env bash

cmake -B build -DBUILD_TESTING=ON \
    && cmake --build build --parallel $(($(nproc) - 1)) \
    && ctest --test-dir build --output-on-failure
