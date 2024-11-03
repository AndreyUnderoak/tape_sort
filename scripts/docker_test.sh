#!/bin/bash

./scripts/echo.sh

echo "
Привет! Запускаем тетсы...
"

docker compose -f docker/docker-compose-test.yml up