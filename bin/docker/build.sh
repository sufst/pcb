#!/bin/sh

set -e

if ! [ -f "Dockerfile" ]; then
    echo "Error: Make sure you're running this in the same directory as the Dockerfile"
    exit 1
fi

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <username>/<package name>"
    exit 1
fi

docker build -t "$1" .
docker push "$1"