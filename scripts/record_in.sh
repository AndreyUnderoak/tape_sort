#!/bin/bash

./scripts/echo.sh

echo "
Привет! Запускаем. 
"

if [ ! -d "build" ]; then
    sh scripts/build.sh
fi

./build/tape_recorder files/in.bin