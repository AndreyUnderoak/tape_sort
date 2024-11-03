#!/bin/bash

./scripts/echo.sh

echo "
Привет! Начинаем сборку docker образа...
"

if [ -d "build" ]; then
    rm -r build
fi

docker build -t tape_sort -f docker/Dockerfile .

echo "
Собрали!
"