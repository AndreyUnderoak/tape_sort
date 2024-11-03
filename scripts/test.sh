#!/bin/bash

./scripts/echo.sh

echo "
Привет! Тестируем. 
"

if [ ! -d "build" ]; then
    sh scripts/build.sh
fi

cd build

ctest --output-on-failure  