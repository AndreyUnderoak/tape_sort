#!/bin/bash

./scripts/echo.sh

echo "
Привет! Начинаем сборку...
"

if [ ! -d "build" ]; then
    mkdir build
fi

cd build

cmake .. 

if [ $? -ne 0 ]; then
    echo "BAD CMake"
    exit 1
fi

make -j$(($(nproc)-1))

# Проверка успешности сборки
if [ $? -ne 0 ]; then
    echo "BAD make"
    exit 1
fi

echo "
Собрали!"