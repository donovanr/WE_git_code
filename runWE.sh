#!/bin/bash

# Get time as a UNIX timestamp (seconds elapsed since Jan 1, 1970 0:00 UTC)
T="$(date +%s)"

# Do some work here
nohup ./WE_main $1 2>err.log
wait

T="$(($(date +%s)-T))"
echo "Time in seconds: ${T}"

