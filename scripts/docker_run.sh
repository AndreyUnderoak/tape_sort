#!/bin/bash

./scripts/echo.sh

echo "
Привет! Запускаем...
"

docker compose -f docker/docker-compose-run.yml up