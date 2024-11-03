#!/bin/bash

./scripts/echo.sh

echo "
Привет! Запускаем...
"

docker compose -f docker/docker-compose.yml run tape-sort /bin/bash