<?php
  //确保在连接客户端时不会超时
  set_time_limit(0);
  
  $ip = '127.0.0.1';
  //$port = 1935;
  $port = 9503;
  
  /*
   +-------------------------------
  *    @socket通信整个过程
  +-------------------------------
  *    @socket_create
  *    @socket_bind
  *    @socket_listen
  
  *    @socket_accept
  *    @socket_read
  *    @socket_write
  *    @socket_close
  *	   @socket_set_option
  *    @socket_strerror()
  +--------------------------------
  */
 
 /*----------------    以下操作都是手册上的    -------------------*/
 
echo "server begin start.... \n";

//1
if (($sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP)) < 0) {
	echo "socket_create() fail:".socket_strerror($sock)."\n";
} else {
 	echo "socket_create() succeed \n";
}

//2
if (($ret = socket_bind($sock, $ip, $port)) < 0){
	echo "socket_bind() fail:".socket_strerror($ret)."\n";
} else {
	echo "socket_bind() succeed \n";
}
 
//3
if (($ret = socket_listen($sock, 4)) < 0) {
	echo "socket_listen() 失败的原因是:".socket_strerror($ret)."\n";
} else {
	echo "socket_listen() socceed \n";
}

 

$count = 0;
 
do {

	if (($msgsock = socket_accept($sock)) < 0) {
    	echo "socket_accept() failed: reason: " . socket_strerror($msgsock) . "\n";
        break;
    } else {
    	echo "socket_accept() succeed \n";
    	
    	//read msg from client
        $buf = socket_read($msgsock, 8192);
        echo "[msg from client]: $buf \n";
        
    	//send msg to client
        $msg ="[msg to client] msgFromServer \n";
        socket_write($msgsock, $msg, strlen($msg));
        
        if(++$count >= 5){
        	echo "see you";
        	break;
        };
    }

    //echo $buf;
    socket_close($msgsock);
 
} while (true);
 
 
socket_close($sock);
echo "socket_close() succeed \n";

?>
