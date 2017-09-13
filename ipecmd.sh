#!/bin/bash

args=""

for arg in "$@"; do
	if [[ "${arg:0:2}" = "-F" ]]
	then
		file=${arg:2}
 
		if [[ "${file:0:1}" != "/" ]]
		then
			file="$(pwd)/$file"
		fi
		
		args+="-F$file "
	else
		args+="$arg "
	fi
done

## Edit this path to match your system if necessary
java -jar /Applications/microchip/mplabx/v4.00/mplab_ipe.app/Contents/Java/ipecmd.jar $args

