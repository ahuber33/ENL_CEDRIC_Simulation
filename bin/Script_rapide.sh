 #!/bin/bash


for (( i=1 ; i<=10 ; i++ ))
do
    while [[ $(pgrep -x ENLCEDRICSim | wc -l) -gt 4 ]]
    do
	sleep 10
    done
    ./ENLCEDRICSim a_${i} 10000000 vrml.mac &
    sleep 5
    done
