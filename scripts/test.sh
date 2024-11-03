#!/bin/bash

./scripts/echo.sh

echo "
Привет! Тестируем. 
"

if [ ! -d "build" ]; then
    echo "Ранее должен быть запущен ./build.sh"
    exit 1
fi

cd build

ctest --output-on-failure  