# Author: Shark
# Reference: https://stackoverflow.com/questions/989349/running-a-command-in-a-new-mac-os-x-terminal-window

#!/bin/bash

for i in $(seq 1 2); do
#	echo "tood"
	osascript -e 'tell application "Terminal" to do script "cd ~/documents/stTests/game && ./c"'
done
