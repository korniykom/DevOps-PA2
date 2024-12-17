#!/bin/bash

while true; do

    delay=$((1 + RANDOM % 6))
    curl -i -X GET 127.0.0.1/compute
    sleep $delay
done
