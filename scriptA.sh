#!/bin/bash

IMAGE_NAME=korniykom/alpinehttpserver2
CONTAINER1="srv1"
CONTAINER2="srv2"
CONTAINER3="srv3"

CHECK_INTERVAL=1

if ! sudo docker ps --format '{{.Names}}' | grep -q "^${CONTAINER1}\$"; then
    sudo docker run -d --name $CONTAINER1 --cpuset-cpus=0 $IMAGE_NAME
else
    echo "srv1 is already running"
fi

get_cpu_usage() {
    local cname=$1
    sudo docker stats --no-stream --format "{{.CPUPerc}}" $cname | sed 's/%//'
}

while true; do
if ! sudo docker ps --format '{{.Names}}' | grep -q "^${CONTAINER2}\$"; then
    if sudo docker ps --format '{{.Names}}' | grep -q "^${CONTAINER1}\$"; then
            srv1_cpu_usage=$(get_cpu_usage $CONTAINER1)
			echo "srv1_cpu_usage is $srv1_cpu_usage"
            if (( $(echo "$srv1_cpu_usage > 0.2" | bc -l))); then
             echo "srv2 starting"
                sudo docker run -d --name $CONTAINER2 --cpuset-cpus=1 $IMAGE_NAME
                echo "srv2 started"

            fi
            
        fi
fi

    if ! sudo docker ps --format '{{.Names}}' | grep -q "^${CONTAINER3}\$"; then
        
        if sudo docker ps --format '{{.Names}}' | grep -q "^${CONTAINER2}\$"; then
                srv2_cpu_usage=$(get_cpu_usage $CONTAINER2)
				echo "srv2_cpu_usage is $srv2_cpu_usage"
                if (( $(echo "$srv2_cpu_usage > 0.2" | bc -l))); then
                echo "srv3 starting"
                    sudo docker run -d --name $CONTAINER3 --cpuset-cpus=2 $IMAGE_NAME
                    echo "srv3 started"
                    
                fi
            fi
        fi
    

sleep 2

    if sudo docker ps --format '{{.Names}}' | grep -q "^${CONTAINER2}\$"; then
    
        srv2_cpu_usage=$(get_cpu_usage $CONTAINER2)
        if (( $(echo "$srv2_cpu_usage < 0.2" | bc -l))); then
			
            sudo docker stop --time 5 $CONTAINER2
            echo "srv2 will stop in 5 seconds"
			sleep 10
			sudo docker remove -f $CONTAINER2
			echo "srv2 was deleted"

        fi
    fi

    if sudo docker ps --format '{{.Names}}' | grep -q "^${CONTAINER3}\$"; then
        srv3_cpu_usage=$(get_cpu_usage $CONTAINER3)
		echo "srv3_cpu_usage is $srv3_cpu_usage"
        if (( $(echo "$srv3_cpu_usage < 0.2" | bc -l))); then
			
            sudo docker stop --time 5 $CONTAINER3
            echo "srv3 will stop in 5 seconds"
			sleep 10
			sudo docker remove -f $CONTAINER3
			echo "srv3 was deleted"
        fi
    fi

    

	if sudo docker pull $IMAGE_NAME | grep "Downloaded"; then
		echo "Updating image from docker hub"
		sudo docker stop $CONTAINER1
        echo "srv1 stoped"
		sudo docker rm -f $CONTAINER1
		sudo docker pull $IMAGE_NAME &&  sudo docker run -d --name $CONTAINER1 --cpuset-cpus=0 $IMAGE_NAME

    fi

    sleep $CHECK_INTERVAL
done
