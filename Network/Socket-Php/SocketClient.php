<?php

set_time_limit(0);
error_reporting(E_ALL);

$ip = "127.0.0.1";
$port = "9503";
/*
+-------------------------------
*    @socket连接整个过程
+-------------------------------
*    @socket_create
*    @socket_connect

*    @socket_write
*    @socket_read
*    @socket_close
+--------------------------------
*/


//1
$client = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($client < 0 ) {
	echo "client create failed". socket_strerror($client) . "\n";
} else {
	echo "client create succeed \n";
}

//2
$result = socket_connect($client, $ip, $port);
if ($result < 0 ){
	echo "client connect failed" .socket_strerror($client) ."\n";
} else {
	echo "client connect succeed \n";
}




$msgToServer = "msgToServer";
if (!socket_write($client, $msgToServer, strlen($msgToServer))) {
	echo "client write failed". socket_strerror($client) ."\n";
} else {
	echo "client write socceed \n";
}

while($out = socket_read($client, 2048)){
	echo "[msg from server]" .$out ."\n";
}



socket_close($client);
?>
