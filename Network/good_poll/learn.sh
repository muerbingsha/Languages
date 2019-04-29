# Source: Internet
# https://bash.cyberciti.biz/guide/If..else..fi
# Purpose: Learning test

#!/bin/bash

#open application
#open -a "iTunes"


#define a variable
today="Monday"
echo $today


#readonly variable
myBlog="http://www.jobyme88.com"
readonly myBlog
#myBlog="http://www.boygirl88.com"

#unset a variable
unset today
echo $today

read -p "Enter a password  " pass
if test "$pass" = "jerry"
then 
	echo "Passworkd verified"
else 
	echo "Access denied"
fi
