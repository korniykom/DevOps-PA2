#!/bin/bash

server_number=1  # Initialize the server number

# Function to increment server number
increase_server_number() {
    server_number=$((server_number-1))  # Increment the actual server_number
}

# Function to get the server name
get_server_name() {
	echo $server_number
    increase_server_number  # Increment the server number
    echo "Server$server_number"  # Return the server name
}

# Get and print the first server name
first_server=$(get_server_name)
echo "$first_server"  # Should print Server2

# Get and print the second server name
second_server=$(get_server_name)
echo "$second_server"  # Should print Server3
sudo docker run --name srv2 -ti --rm --cpuset-cpus 1 test-image