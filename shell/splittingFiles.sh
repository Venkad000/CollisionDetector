#!/bin/bash

no_of_bytes="$(wc -c < $1)"
by=10
result=$(((no_of_bytes)/by))
echo $result

split -b $result $1 segment
mv segment* ../temp
echo "$no_of_bytes"
